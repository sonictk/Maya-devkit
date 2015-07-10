#-
# ==========================================================================
# Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
#
# Use of this software is subject to the terms of the Autodesk
# license agreement provided at the time of installation or download,
# or which otherwise accompanies this software in either electronic
# or hard copy form.
# ==========================================================================
#+

# NOTE: MAYA_LOCATION on Mac OS X points to Maya.app/Contents

# Change location if you have a non standard install.
DEVKIT_LOCATION = $(MAYA_LOCATION)/../../devkit

# Make sure this is in your path.
CXX			= clang++

# By default, we will try to build a universal binary to match the same
# architectures as the installed Maya binary. If you only want one specific
# architecture (e.g i386 or x86_64) then set it below.
PREFERRED_ARCHITECTURE	=

# Determine the architectures to build.
MAYABIN = ${MAYA_LOCATION}/bin/maya
MAYA_ARCHES = $(shell lipo -info $(MAYABIN) | sed 's/^.*://')

ifneq ($(PREFERRED_ARCHITECTURE),)
	MAYA_ARCHES = $(filter $(PREFERRED_ARCHITECTURE),$(MAYA_ARCHES))

	ifeq ($(MAYA_ARCHES),)
		$(error $(MAYABIN) does not support the '$(PREFERRED_ARCHITECTURE)' architecture.)
	endif
endif

ARCH_FLAGS = $(patsubst %,-arch %,$(MAYA_ARCHES))
CFLAGS	= -stdlib=libstdc++ -DCC_GNU_ -DOSMac_ -DOSMacOSX_ \
		-DOSMac_MachO_ -fno-gnu-keywords -fpascal-strings -O3 \
		$(ARCH_FLAGS) -D_LANGUAGE_C_PLUS_PLUS -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk
C++FLAGS	= $(CFLAGS)
INCLUDES	= -I. -I$(DEVKIT_LOCATION)/include
LD		= $(DEVKIT_LOCATION)/bin/mayald MAYA_ARCHES="$(MAYA_ARCHES)" MAYA_LOCATION="$(MAYA_LOCATION)"
TARGETS		= helloWorld surfaceCreate surfaceTwist readAndWrite asciiToBinary

.SUFFIXES: .cpp .cc .o .c

.cc.o:
	$(CXX) -c $(C++FLAGS) $(INCLUDES) $<

.cpp.o:
	$(CXX) -c $(C++FLAGS) $(INCLUDES) $<

all: $(TARGETS)

helloWorld: helloWorld.o
	$(LD) -o $@ $@.o

surfaceCreate: surfaceCreate.o
	$(LD) -o $@ $@.o

surfaceTwist: surfaceTwist.o
	$(LD) -o $@ $@.o

readAndWrite: readAndWrite.o
	$(LD) -o $@ $@.o

asciiToBinary: asciiToBinary.o
	$(LD) -o $@ $@.o

clean:
	rm -f *.o

Clean:
	rm -f $(TARGETS) *.o *.bak
