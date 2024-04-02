# Instructions for Compiling and Running Randomise
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

Before compiling, make sure you have the following dependencies installed:

- Blas
- Lapack
- zlib

You can install these dependencies on Ubuntu using the following commands:

```bash
sudo apt-get install libblas-dev libblas3
sudo apt-get install liblapack-dev liblapack3
sudo apt-get install zlib1g zlib1g-dev
```
## Modify Makefile

Modify the makefile to set the path for `ZNZLIB_LDFFLAGS`.
Open the makefile and find the ZNZLIB_LDFLAGS line. Modify it to set the path to your znzlib. 
```bash
ZNZLIB_LDFLAGS = -L/path/to/your/znzlib -lfsl-znz
```
Replace `/path/to/your/znzlib` with the actual path to your znzlib directory.

## Compiling

Once the dependencies are installed and the makefile is modified, you can proceed with compilation by running:
```bash
make
```

- Resolving Shared Library Errors:
When running an executable, you may encounter errors related to missing shared libraries.This typically shows up as messages such as:
```bash
./randomise: error while loading shared libraries: libexample.so: cannot open shared object file:No such file or directory
```
To resolve these errors, identify missing libraries mentioned in the error, then locate and install them or specify custom directories using the LD_LIBRARY_PATH environment variable.
```bash
export LD_LIBRARY_PATH=/path/to/custom/libraries:$LD_LIBRARY_PATH
```
Replace `/path/to/custom/libraries` with the actual path to the directory containing the missing libraries.Once the `LD_LIBRARY_PATH` is set, attempt to run the executable again.If you encounter additional missing library errors, repeat steps until all dependencies are resolved.

- Resolving "The environment variable FSLOUTPUTTYPE is not defined" errors:
To fix this error, set `FSLOUTPUTTYPE` to `NIFTI_GZ`. This defines the output format for FSL tools as NIFTI compressed with gzip.

Here's how you can resolve it:
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
