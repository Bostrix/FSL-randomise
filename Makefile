include ${FSLCONFDIR}/default.mk

PROJNAME = randomise
XFILES   = randomise fdr unconfound
SCRIPTS  = design_ttest2 randomise_parallel tfce_support \
           randomise_combine setup_masks
LIBS     = -lfsl-newimage -lfsl-miscmaths -lfsl-utils \
           -lfsl-NewNifti -lfsl-znz -lfsl-cprob

all: ${XFILES}

randomise: randomise.o ranopts.o
	${CXX}  ${CXXFLAGS} -o $@ $^ ${LDFLAGS}

unconfound: unconfound.o
	${CXX}  ${CXXFLAGS} -o $@ $^ ${LDFLAGS}

fdr: fdr.o
	${CXX}  ${CXXFLAGS} -o $@ $^ ${LDFLAGS}
