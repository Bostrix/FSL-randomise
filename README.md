# Instructions for Compiling and Running Randomise
## Introduction
Welcome to Randomise, a versatile tool for nonparametric permutation testing in neuroimaging analysis. This guide will provide instructions on compiling Randomise and utilizing its functionalities for robust statistical inference on brain imaging data.


For more information about randomise and related tools, visit the FMRIB Software Library (FSL) website:[FSL Git Repository](https://git.fmrib.ox.ac.uk/fsl) and you can also find additional resources and documentation on randomise on the FSL wiki page: [randomise Documentation](https://fsl.fmrib.ox.ac.uk/fsl/fslwiki/Randomise).
## Clone the Repository

Begin by cloning the project repository from GitHub onto your local machine. You can do this by running the following command in your terminal or command prompt:

```bash
git clone https://github.com/Bostrix/FSL-randomise.git
```
This command will create a local copy of the project in a directory named "FSL-randomise".

## Navigate to Project Directory
Change your current directory to the newly cloned project directory using the following command:
```bash
cd FSL-randomise
```
## Installing Dependencies
To install the necessary dependencies for compiling and building the project, follow these steps:
```bash
sudo apt-get update
sudo apt install g++
sudo apt install make
sudo apt-get install libboost-all-dev
sudo apt-get install libblas-dev libblas3
sudo apt-get install liblapack-dev liblapack3
sudo apt-get install zlib1g zlib1g-dev
```
## Compilation
To compile randomise, follow these steps:

- Ensure correct path in Makefile:
After installing the necessary tools, verify correct path in the makefile to include additional LDFLAGS for the required libraries. For instance, if utilizing the znzlib library, ensure that the correct path is present in the makefile.
Make sure `$(ZNZLIB_LDFLAGS)` are included in the compile step of the makefile.

- Compiling: 
Execute the appropriate compile command to build the randomise tool.
```bash
make clean
make
```
- Resolving Shared Library Errors
When running an executable on Linux, you may encounter errors related to missing shared libraries.This typically manifests as messages like:
```bash
./randomise: error while loading shared libraries: libexample.so: cannot open shared object file:No such file or directory
```
To resolve these errors,Pay attention to the names of the missing libraries mentioned in the error message.Locate the missing libraries on your system. If they are not present, you may need to install the corresponding packages.If the libraries are installed in custom directories, you need to specify those directories using the `LD_LIBRARY_PATH` environment variable. For example:
```bash
export LD_LIBRARY_PATH=/path/to/custom/libraries:$LD_LIBRARY_PATH
```
Replace `/path/to/custom/libraries` with the actual path to the directory containing the missing libraries.Once the `LD_LIBRARY_PATH` is set, attempt to run the executable again.If you encounter additional missing library errors, repeat steps until all dependencies are resolved.

- Resolving "The environment variable FSLOUTPUTTYPE is not defined" errors
If you encounter an error related to the FSLOUTPUTTYPE environment variable not being set.Setting it to `NIFTI_GZ` is a correct solution, as it defines the output format for FSL tools to NIFTI compressed with gzip.Here's how you can resolve:
```bash
export FSLOUTPUTTYPE=NIFTI_GZ
```
By running this command, you've set the `FSLOUTPUTTYPE` environment variable to `NIFTI_GZ`,which should resolve the error you encountered.
## Running randomise

After successfully compiling, you can run randomise by executing:
```bash
./randomise -i <input> -o <output> -d <design.mat> -t <design.con> [options]
```

This command will execute the randomise tool.
