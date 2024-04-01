# Specify the default compiler
CXX = g++

# Specify the -fpic flag
CXXFLAGS += -fpic

# Define source files
SRCS = fdr.cc randomise.cc ranopts.cc unconfound.cc

# Additional LDFLAGS for znzlib library
ZNZLIB_LDFLAGS = -L/path/to/your/znzlib -lfsl-znz

# Define object files
OBJS = $(SRCS:.cc=.o)

# Define library source files and directories
LIB_DIRS = newimage miscmaths NewNifti cprob znzlib utils 
LIB_SRCS = $(foreach dir,$(LIB_DIRS),$(wildcard $(dir)/*.cc))
LIB_OBJS = $(LIB_SRCS:.cc=.o)

# Define targets
all: randomise fdr unconfound

# Compile the final executables
randomise: libraries randomise.o ranopts.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ randomise.o ranopts.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS) -lblas -llapack -lz

unconfound: libraries unconfound.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ unconfound.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS) -lblas -llapack -lz

fdr: libraries fdr.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ fdr.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS) -lblas -llapack -lz


# Rule to build object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Phony target to build all libraries
.PHONY: libraries
libraries:
	@for dir in $(LIB_DIRS); do \
	$(MAKE) -C $$dir CXX=$(CXX) CXXFLAGS='$(CXXFLAGS)' LDFLAGS='$(LDFLAGS)'; \
	done

# Clean rule
clean:
# Clean rule
clean:
# Clean rule
clean:
	rm -f randomise $(OBJS) $(LIB_OBJS) $(shell find . -type f \( -name "*.o" -o -name "*.so" \))
