/*  ranopts.cc

    Matthew Webster, Tim Behrens & Steve Smith (FMRIB) & Tom Nichols (UMich)

    Copyright (C) 2008 University of Oxford  */

/*  CCOPYRIGHT  */

#define WANT_STREAM
#define WANT_MATH

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "utils/log.h"
#include "ranopts.h"

using namespace std;
using namespace Utilities;

namespace RANDOMISE {

ranopts* ranopts::gopt = NULL;

  void ranopts::parse_command_line(int argc, char** argv,Log& logger)
  {

    //Do the parsing;
    try{
      for(int a = options.parse_command_line(argc, argv); a < argc; a++);

      if(help.value() || ! options.check_compulsory_arguments())
	{
	  options.usage();
	  exit(2);
	}
    }
    catch(X_OptionError& e){
      cerr<<e.what()<<endl;
      cerr<<"try: randomise --help"<<endl;
      exit(1);
    }



  }


}
