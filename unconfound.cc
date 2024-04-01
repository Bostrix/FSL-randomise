/*  unconfound.cc

    Steve Smith

    Copyright (C) 2006 University of Oxford  */

/*  CCOPYRIGHT  */

#include <iostream>

#include "armawrap/newmat.h"
#include "miscmaths/miscmaths.h"
#include "newimage/newimageall.h"

using namespace std;
using namespace NEWMAT;
using namespace MISCMATHS;
using namespace NEWIMAGE;

int main(int argc,char *argv[]){

  if (argc<4) {
    cout << "Usage:   unconfound <in4d> <out4d> <confound.mat>" << endl;
    exit(1);
  }

  Matrix confound=read_vest(argv[3]);

  volume4D<float> data;
  read_volume4D(data,argv[1]);

  ColumnVector datam(data.tsize());

  for(int z=0; z<data.zsize(); z++) for(int y=0; y<data.ysize(); y++) for(int x=0; x<data.xsize(); x++)
    {
      for(int t=0; t<data.tsize(); t++)
	datam(t+1)=data(x,y,z,t);
      datam=(IdentityMatrix(confound.Nrows())-confound*pinv(confound))*datam;
      for(int t=0; t<data.tsize(); t++)
	data(x,y,z,t)=datam(t+1);
    }

  save_volume4D(data,argv[2]);

  return 0;
}
