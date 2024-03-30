/*  ranopts.h

    Matthew Webster, Tim Behrens & Steve Smith (FMRIB) & Tom Nichols (UMich)

    Copyright (C) 2008-2010 University of Oxford  */

/*  CCOPYRIGHT  */

#if !defined(ranopts_h)
#define ranopts_h

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "utils/options.h"
#include "utils/log.h"

namespace RANDOMISE {

class ranopts {
 public:
  static ranopts& getInstance();
  ~ranopts() { delete gopt; }

  Utilities::Option<bool> demean_data;
  Utilities::Option<bool> one_samp;
  Utilities::Option<std::string> in_fileroot;
  Utilities::Option<std::string> maskname;
  Utilities::Option<std::string> out_fileroot;
  Utilities::Option<std::string> dm_file;
  Utilities::Option<std::string> tc_file;
  Utilities::Option<std::string> fc_file;
  Utilities::Option<std::string> gp_file;
  Utilities::Option<std::string> effectiveDesignFile;
  Utilities::Option<bool> how_many_perms;
  Utilities::Option<bool> parallelData;
  Utilities::Option<int> n_perm;
  Utilities::Option<bool> voxelwiseOutput;
  Utilities::Option<bool> doFOnly;
  Utilities::Option<bool> tfce;
  Utilities::Option<bool> tfce2D;
  Utilities::Option<float> cluster_thresh;
  Utilities::Option<float> clustermass_thresh;
  Utilities::Option<float> f_thresh;
  Utilities::Option<float> fmass_thresh;
  Utilities::Option<float> tfce_height;
  Utilities::Option<float> tfce_delta;
  Utilities::Option<float> tfce_size;
  Utilities::Option<int> tfce_connectivity;
  Utilities::Option<float> var_sm_sig;
  Utilities::Option<bool> help;
  Utilities::Option<bool> verbose;
  Utilities::Option<bool> cluster_norm;
  Utilities::Option<bool> outputRaw;
  Utilities::Option<bool> outputUncorr;
  Utilities::Option<bool> outputTextPerm;
  Utilities::Option<bool> outputTextNull;
  Utilities::Option<bool> output_permstat;
  Utilities::Option<bool> disableNonConstantMask;
  Utilities::Option<int> randomSeed;
  Utilities::Option<std::vector<int> > voxelwise_ev_numbers;
  Utilities::Option<std::vector<std::string> > voxelwise_ev_filenames;
  Utilities::Option<int> nMultiVariate;
  Utilities::Option<bool> isDebugging;
  Utilities::Option<int> confoundMethod;
  Utilities::Option<bool> detectNullSubjects;
  Utilities::Option<bool> permuteBlocks;
  Utilities::Option<bool> verbose_old;
  Utilities::Option<int>  skipTo;
  Utilities::Option<bool> outputGlm;
  Utilities::Option<bool> featMode;

  void parse_command_line(int argc, char** argv,Utilities::Log& logger);

 private:
  ranopts();
  const ranopts& operator=(ranopts&);
  ranopts(ranopts&);

  Utilities::OptionParser options;

  static ranopts* gopt;

};

 inline ranopts& ranopts::getInstance(){
   if(gopt == NULL)
     gopt = new ranopts();

   return *gopt;
 }

 inline ranopts::ranopts() :
   demean_data(std::string("-D"), false,
	std::string("\tdemean data temporally before model fitting ( demean model as well if required )"),
	false, Utilities::no_argument),
   one_samp(std::string("-1"), false,
	    std::string("\tperform 1-sample group-mean test instead of generic permutation test"),
	    false, Utilities::no_argument),
   in_fileroot(std::string("-i"), "",
       std::string("~<input>\t4D input image"),
       true, Utilities::requires_argument),
   maskname(std::string("-m"), "",
       std::string("~<mask>\tmask image"),
       false, Utilities::requires_argument),
   out_fileroot(std::string("-o"), std::string(""),
	    std::string("~<out_root>\toutput file-rootname"),
	    true, Utilities::requires_argument),
   dm_file(std::string("-d"), std::string(""),
	    std::string("~<design.mat>\tdesign matrix file"),
	    false, Utilities::requires_argument),
   tc_file(std::string("-t"), std::string(""),
	    std::string("~<design.con>\tt contrasts file"),
	    false, Utilities::requires_argument),
   fc_file(std::string("-f"), std::string(""),
            std::string("~<design.fts>\tf contrasts file"),
	   false, Utilities::requires_argument),
   gp_file(std::string("-e"), std::string(""),
            std::string("~<design.grp>\texchangeability block labels file"),
	   false, Utilities::requires_argument),
   effectiveDesignFile(std::string("--effective_design"), std::string(""),
            std::string("~<design2.mat>\talternative design for determining valid permutations"),
	   false, Utilities::requires_argument),
   how_many_perms(std::string("-q"), false,
	    std::string("\tprint out how many unique permutations would be generated and exit"),
	    false, Utilities::no_argument),
   parallelData(std::string("-Q"), false,
	    std::string("\tprint out information required for parallel mode and exit"),
	    false, Utilities::no_argument),
   n_perm(std::string("-n"), 5000,
	    std::string("~<n_perm>\tnumber of permutations (default 5000, set to 0 for exhaustive)"),
	    false, Utilities::requires_argument),
   voxelwiseOutput(std::string("-x"),false,
	    std::string("\toutput voxelwise corrected p-value images"),
		 false, Utilities::no_argument),
   doFOnly(std::string("--fonly"), false,
	   std::string("\tcalculate f-statistics only"),
	   false, Utilities::no_argument),
   tfce(std::string("-T"), false,
	   std::string("\tcarry out Threshold-Free Cluster Enhancement"),
	   false, Utilities::no_argument),
   tfce2D(std::string("--T2"), false,
	   std::string("\tcarry out Threshold-Free Cluster Enhancement with 2D optimisation (e.g. for TBSS data); H=2, E=1, C=26"),
	   false, Utilities::no_argument),
   cluster_thresh(std::string("-c"), -1,
	  std::string("~<thresh>\tcarry out cluster-based thresholding"),
	  false, Utilities::requires_argument),
   clustermass_thresh(std::string("-C"), -1,
	  std::string("~<thresh>\tcarry out cluster-mass-based thresholding"),
	  false, Utilities::requires_argument),
   f_thresh(std::string("-F"), -1,
	  std::string("~<thresh>\tcarry out f cluster thresholding"),
	  false, Utilities::requires_argument),
   fmass_thresh(std::string("-S"), -1,
	  std::string("~<thresh>\tcarry out f cluster-mass thresholding"),
	  false, Utilities::requires_argument),
   tfce_height(std::string("--tfce_H"), 2, std::string("~<H>\tTFCE height parameter (default=2)"), false, Utilities::requires_argument),
   tfce_delta(std::string("--tfce_D"), 1, std::string("~<H>\tTFCE delta parameter overide"), false, Utilities::requires_argument),
   tfce_size(std::string("--tfce_E"), 0.5, std::string("~<E>\tTFCE extent parameter (default=0.5)"), false, Utilities::requires_argument),
   tfce_connectivity(std::string("--tfce_C"), 6, std::string("~<C>\tTFCE connectivity (6 or 26; default=6)"), false, Utilities::requires_argument),
   var_sm_sig(std::string("-v"), 0,
	    std::string("~<std>\tuse variance smoothing for t-stats (std is in mm)"),
	     false, Utilities::requires_argument),
   help(std::string("-h,--help"), false,
	std::string("display this message"),
	false, Utilities::no_argument),
   verbose(std::string("--quiet"), true,
	   std::string("\tswitch off diagnostic messages"),
	   false, Utilities::no_argument),
   cluster_norm(std::string("--twopass"), false,
	   std::string("carry out cluster normalisation thresholding"),
		false, Utilities::no_argument),
   outputRaw(std::string("-R"), false,
	   std::string("\toutput raw ( unpermuted ) statistic images"),
		false, Utilities::no_argument),
   outputUncorr(std::string("--uncorrp"), false,
	   std::string("output uncorrected p-value images"),
		false, Utilities::no_argument),
   outputTextPerm(std::string("-P"), false,
	   std::string("\toutput permutation vector text file"),
		false, Utilities::no_argument),
   outputTextNull(std::string("-N"), false,
	   std::string("\toutput null distribution text files"),
		false, Utilities::no_argument),
   output_permstat(std::string("--permout"), false,
	   std::string("\toutput permuted tstat"),
		false, Utilities::no_argument,false),
   disableNonConstantMask(std::string("--norcmask"), false,
	   std::string("don't remove constant voxels from mask"),
		false, Utilities::no_argument),
   randomSeed(std::string("--seed"),0,
	    std::string("~<seed>\tspecific integer seed for random number generator"),
		 false, Utilities::requires_argument),
   voxelwise_ev_numbers(std::string("--vxl"), std::vector<int>(),
         std::string("\tlist of numbers indicating voxelwise EVs position in the design matrix (list order corresponds to files in vxf option)."),
         false, Utilities::requires_argument),
   voxelwise_ev_filenames(std::string("--vxf"), std::vector<std::string>(),
         std::string("\tlist of 4D images containing voxelwise EVs (list order corresponds to numbers in vxl option)."),
         false, Utilities::requires_argument),
   nMultiVariate(std::string("--multi"),1,
	    std::string("~<dim>\tmultivariate dimension (default 1). caution BETA option."),
		 false, Utilities::requires_argument, false),
   isDebugging(std::string("--debug"), false,
	   std::string("\tOutput debug information"),
	       false, Utilities::no_argument,false),
   confoundMethod(std::string("-U"),1,
	    std::string("~<mode>\tconfound mode. 0: Kennedy Y_a on X_a (old) 1: Freedman-Lane Y_a on X|Z (default) 2: Y on X|Z. 3: ter Braak Y_aFull on X|Z Caution BETA option."),
		  false, Utilities::requires_argument, false),
   detectNullSubjects(std::string("--detectNull"), false,
	   std::string("attempt to detect uninformative rows in the effective regressor and not permute them"),
		      false, Utilities::no_argument, false),
   permuteBlocks(std::string("--permuteBlocks"), false,
	   std::string("permute exchangeability blocks. Caution BETA option"),
		 false, Utilities::no_argument),
   verbose_old(std::string("-V"), false,
	   std::string("\tswitch on diagnostic messages (deprecated: now always on unless quiet)"),
	       false, Utilities::no_argument, false),
   skipTo(std::string("--skipTo"),0,
	    std::string("~<number>\tdo only contrast<number>. A setting of 0 will do all contrasts, numbering starts with f- and then t-contrasts"),
		false, Utilities::requires_argument, false),
   outputGlm(std::string("--glm_output"), false,
	   std::string("output glm information for t-statistics ( unpermuted case only )"),
		false, Utilities::no_argument),
   featMode(std::string("--film"), false,
	   std::string("output stats to simulate the output of film"),
		false, Utilities::no_argument),

   options("randomise v2.9", "randomise -i <input> -o <output> -d <design.mat> -t <design.con> [options]")
     {

     try {
       options.add(demean_data);
       options.add(one_samp);
       options.add(in_fileroot);
       options.add(maskname);
       options.add(out_fileroot);
       options.add(dm_file);
       options.add(tc_file);
       options.add(fc_file);
       options.add(gp_file);
       options.add(effectiveDesignFile);
       options.add(how_many_perms);
       options.add(parallelData);
       options.add(n_perm);
       options.add(voxelwiseOutput);
       options.add(doFOnly);
       options.add(tfce);
       options.add(tfce2D);
       options.add(cluster_thresh);
       options.add(clustermass_thresh);
       options.add(f_thresh);
       options.add(fmass_thresh);
       options.add(var_sm_sig);
       options.add(help);
       options.add(verbose);
       options.add(cluster_norm);
       options.add(outputRaw);
       options.add(outputUncorr);
       options.add(outputTextPerm);
       options.add(outputTextNull);
       options.add(output_permstat);
       options.add(disableNonConstantMask);
       options.add(randomSeed);
       options.add(tfce_height);
       options.add(tfce_delta);
       options.add(tfce_size);
       options.add(tfce_connectivity);
       options.add(voxelwise_ev_numbers);
       options.add(voxelwise_ev_filenames);
       options.add(nMultiVariate);
       options.add(isDebugging);
       options.add(confoundMethod);
       options.add(detectNullSubjects);
       options.add(permuteBlocks);
       options.add(verbose_old);
       options.add(skipTo);
       options.add(outputGlm);
       options.add(featMode);
     }
     catch(Utilities::X_OptionError& e) {
       options.usage();
       std::cerr << std::endl << e.what() << std::endl;
     }
     catch(std::exception &e) {
       std::cerr << e.what() << std::endl;
     }

   }
}

#endif
