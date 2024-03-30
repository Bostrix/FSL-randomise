/*  fdr.cc

    Mark Jenkinson, Anderson Winkler and Tom Nichols, FMRIB Image Analysis Group

    Copyright (C) 2004-2012 University of Oxford  */

/*  CCOPYRIGHT  */

// Calculates the FDR threshold and the FDR-adjusted image from an
//  input 3D probability image (values of 0 for p are ignored)

#include <algorithm>
#include <limits>
#include <vector>
#include "utils/options.h"
#include "armawrap/newmat.h"
#include "miscmaths/miscmaths.h"
#include "newimage/newimageall.h"

using namespace std;
using namespace Utilities;
using namespace NEWMAT;
using namespace MISCMATHS;
using namespace NEWIMAGE;

string title="fdr \nCopyright(c) 2004-2012, University of Oxford (Mark Jenkinson)";
string examples="fdr -i <pvalimage> [options]\ne.g.  fdr -i <pvalimage> -m <maskimage> -q 0.05\n      fdr -i <pvalimage> -a <adjustedimage>\nNote: if a mask is not specified, voxels where p>.9999 are ignored.";

Option<bool> verbose(string("-v,--verbose"), false,
		     string("switch on diagnostic messages"),
		     false, no_argument);
Option<bool> help(string("-h,--help"), false,
		  string("display this message"),
		  false, no_argument);
Option<bool> debug(string("--debug"), false,
		     string("switch on debugging output"),
		     false, no_argument);
Option<bool> conservativetest(string("--conservative"), false,
			      string("use conservative FDR correction factor (allows for any correlation)"),
			      false, no_argument);
Option<bool> positivecorrtest(string("--positivecorr"), false,
			      string("use FDR correction factor that assumes positive correlation (default)"),
			      false, no_argument);
Option<bool> independenttest(string("--independent"), false,
			      string("use FDR correction factor that assumes independence"),
			      false, no_argument);
Option<bool> invertp(string("--oneminusp"), false,
			      string("treat input as 1-p (also save output like this)"),
			      false, no_argument);
Option<float>  qthresh(string("-q"),0,
		  string("q-value (FDR) threshold"),
		  false, requires_argument);
Option<string> ordername(string("--order"), string(""),
		      string("~\toutput image of order values"),
		      false, requires_argument);
Option<string> inname(string("-i,--in"), string(""),
		      string("input p-value filename"),
		      true, requires_argument);
Option<string> mask(string("-m"), string(""),
		      string("mask filename"),
		      false, requires_argument);
Option<string> adjname(string("-a"), string(""),
		       string("output image with FDR-adjusted p-values"),
		       false, requires_argument);
Option<string> othresh(string("--othresh"), string(""),
		       string("output a thresholded p-value image"),
		       false, requires_argument);
int nonoptarg;

template<class T>
int save_as_image(const string& filename, const volume<T>& mask,
		  const Matrix& valmat)
{
    // put values back into volume format
    if (verbose.value()) { cerr << "Saving results to " << filename << endl; }
    volume4D<T> outvals(mask);
    outvals.setmatrix(valmat.t(),mask);
    return save_volume4D(outvals,filename);
}


int do_work(int argc, char* argv[], int nonoptarg)
{
  volume4D<double> pimg; // reading in 4D in order to be able to use the newimage<->newmat functions - only actually use first timepoint
  read_volume(pimg,inname.value());
  if ( invertp.value() )
    pimg = 1.0 - pimg;
  if (verbose.value()) print_volume_info(pimg,"p-value image");

  volume<double> vmask;
  if (mask.set()) {
    read_volume(vmask,mask.value());
    vmask.binarise();
  } else {
    vmask = pimg[0];
    vmask.binarise(1,std::numeric_limits<double>::max(),inclusive,true);
  }

  Matrix pmat;
  pmat = pimg.matrix(vmask);
  pmat = pmat.t();
  int Ntot = pmat.Nrows();

  // calculate FDR threshold required to make each voxel significant
  // FDR formula is: p = n*q / (N * C)
  //   where n=order index, N=total number of p values,
  //         C=1 for the simple case (including positive correlations), and
  //         C=1/1 + 1/2 + 1/3 + ... + 1/N for the most general correlation
  // We use the inverse formula: q_{min} = N*C*p / n

  if (verbose.value()) { cerr << "Calculating FDR values" << endl; }
  bool conservativecorrection=false;  // the default
  if (conservativetest.set()) conservativecorrection=true;  // this is overridden by any of the other options
  if (independenttest.set())  conservativecorrection=false;
  if (positivecorrtest.set()) conservativecorrection=false;
  float C=1.0;
  if (conservativecorrection) {
    for (int n=2; n<=Ntot; n++) { C+=1.0/((double) n); }
  }

  // Sort the p-values
  if (debug.value()) {
    cout << "Number of voxels (p-values): " << Ntot << endl;
    cout << "Smallest p-value: " << pmat.Minimum() << endl;
    cout << "Largest p-value:  " << pmat.Maximum() << endl;
  }
  vector<pair<double, int> > sortlist(Ntot);
  for (int n=0; n<Ntot; n++) {
    sortlist[n] = pair<double, int> ((double) pmat(n+1,1), n+1);
  }
  sort(sortlist.begin(), sortlist.end());

  // Compute the ranks, in the same order as the original p-values
  vector<int> norder(Ntot);
  for (int n=0; n<Ntot; n++) {
    norder[sortlist[n].second-1] = n+1;
  }

  // output the appropriate p-threshold, if requested
  float pthresh = 0.0;
  float qthr = qthresh.value();
  float qfac = qthr / ( C * (float) Ntot );
  for (int j=1; j<=Ntot; j++) {
    if ( (pmat(j,1) > pthresh) &&
	 ( pmat(j,1) <= qfac * (float) norder[j-1] ) ) // note an important change here, from '<' to '<='
      {
	if (verbose.value()) { cout << "p = " << pmat(j,1) << " , n = "
				    << norder[j-1] << " , qfac = " << qfac << endl; }
	pthresh = pmat(j,1);
      }
  }
  cout << "Probability Threshold is: " << endl << pthresh << endl;


  // output the adjusted image, if requested
  if (adjname.set()) {
    Matrix amat = pmat;
    vector<int> reverse(Ntot); // reverse of norder
    for (int j=0; j<Ntot; j++) {
      reverse[norder[j]-1] = j+1;
    }
    double prev = 1.0;
    for (int j=Ntot; j>=1; j--) {
      amat(reverse[j-1],1) = sortlist[j-1].first * C * Ntot / j;
      amat(reverse[j-1],1) = Min(prev,amat(reverse[j-1],1));
      prev = amat(reverse[j-1],1);
    }

    // save the FDR (q_min) results
    if ( invertp.value() ) amat=1.0-amat;
    save_as_image(adjname.value(),vmask,amat);
  }


  // save the order values, if requested
  if (ordername.set()) {
    Matrix ordermat(Ntot,1);
    for (int j=1; j<=Ntot; j++) { ordermat(j,1) = norder[j-1]; }
    save_as_image(ordername.value(),vmask,ordermat);
  }

  // save the thresholded p-values, if requested
  if (othresh.set()) {
    pimg.threshold(0,pthresh,inclusive);
    volume<double> significantMask(pimg);
    significantMask.binarise();
    if ( invertp.value() ) // convert back to p unless 1-p was the input
      pimg=1.0-pimg;
    pimg=pimg*vmask*significantMask;
    save_volume4D(pimg,othresh.value());
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////

int main(int argc,char *argv[])
{

  Tracer tr("main");
  OptionParser options(title, examples);

  try {
    options.add(inname);
    options.add(mask);
    options.add(qthresh);
    options.add(adjname);
    options.add(othresh);
    options.add(ordername);
    options.add(invertp);
    options.add(positivecorrtest);
    options.add(independenttest);
    options.add(conservativetest);
    options.add(debug);
    options.add(verbose);
    options.add(help);

    nonoptarg = options.parse_command_line(argc, argv);

    if ( (help.value()) || (!options.check_compulsory_arguments(true)) )
      {
	options.usage();
	exit(EXIT_FAILURE);
      }

  }  catch(X_OptionError& e) {
    options.usage();
    cerr << endl << e.what() << endl;
    exit(EXIT_FAILURE);
  } catch(std::exception &e) {
    cerr << e.what() << endl;
  }

  // Call the local functions

  return do_work(argc,argv,nonoptarg);
}
