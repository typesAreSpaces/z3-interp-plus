LDIR=./../build
CC=g++
OS=$(shell uname)
IS_SAME="$(shell diff -q original_output.txt current_output.txt)"
ifeq ($(OS), Darwin)
	SO_EXT=dylib
	DYLD_LIBRARY_PATH=$(LDIR)
	export DYLD_LIBRARY_PATH
	NUM_PROCS=$(shell sysctl -n hw.logicalcpu)
else
	SO_EXT=so
	NUM_PROCS=$(shell nproc)
endif

FLAGS=-I$(SDIR) -I$(IDIR) -std=c++11 -Wall

all: test

# -----------------------------
#  Testing z3-interp-plus-changes
test:
	@$(CC) ./test.cpp \
		$(LDIR)/libz3.$(SO_EXT) -o $@
	@./$@ 
	@rm $@
	# -----------------------------

# ------------------------------
#  Cleaning
.PHONY: clean
clean:
	@echo "Cleaned"
	# ------------------------------
