#-
# ==========================================================================
# Copyright (c) 2011 Autodesk, Inc.
# All rights reserved.
# 
# These coded instructions, statements, and computer programs contain
# unpublished proprietary information written by Autodesk, Inc., and are
# protected by Federal copyright law. They may not be disclosed to third
# parties or copied or duplicated in any form, in whole or in part, without
# the prior written consent of Autodesk, Inc.
# ==========================================================================
#+

ifndef INCL_BUILDRULES

#
# Include platform specific build settings
#
TOP := ..
include $(TOP)/buildrules


#
# Always build the local plug-in when make is invoked from the
# directory.
#
all : plugins

endif

#
# Variable definitions
#

SRCDIR := $(TOP)/jlcVcrDevice
DSTDIR := $(TOP)/jlcVcrDevice

jlcVcrDevice_SOURCES  := $(TOP)/jlcVcrDevice/jlcVcrDevice.cpp
jlcVcrDevice_OBJECTS  := $(TOP)/jlcVcrDevice/jlcVcrDevice.o
jlcVcrDevice_PLUGIN   := $(DSTDIR)/jlcVcrDevice.$(EXT)
jlcVcrDevice_MAKEFILE := $(DSTDIR)/Makefile

#
# Include the optional per-plugin Makefile.inc
#
#    The file can contain macro definitions such as:
#       {pluginName}_EXTRA_CFLAGS
#       {pluginName}_EXTRA_C++FLAGS
#       {pluginName}_EXTRA_INCLUDES
#       {pluginName}_EXTRA_LIBS
-include $(SRCDIR)/Makefile.inc


#
# Set target specific flags.
#

$(jlcVcrDevice_OBJECTS): CFLAGS   := $(CFLAGS)   $(jlcVcrDevice_EXTRA_CFLAGS)
$(jlcVcrDevice_OBJECTS): C++FLAGS := $(C++FLAGS) $(jlcVcrDevice_EXTRA_C++FLAGS)
$(jlcVcrDevice_OBJECTS): INCLUDES := $(INCLUDES) $(jlcVcrDevice_EXTRA_INCLUDES)

depend_jlcVcrDevice:     INCLUDES := $(INCLUDES) $(jlcVcrDevice_EXTRA_INCLUDES)

$(jlcVcrDevice_PLUGIN):  LFLAGS   := $(LFLAGS) $(jlcVcrDevice_EXTRA_LFLAGS) 
$(jlcVcrDevice_PLUGIN):  LIBS     := $(LIBS)   -lOpenMaya -lOpenMayaUI -lFoundation $(jlcVcrDevice_EXTRA_LIBS) 

#
# Rules definitions
#

.PHONY: depend_jlcVcrDevice clean_jlcVcrDevice Clean_jlcVcrDevice


$(jlcVcrDevice_PLUGIN): $(jlcVcrDevice_OBJECTS) 
	-rm -f $@
	$(LD) -o $@ $(LFLAGS) $^ $(LIBS)

depend_jlcVcrDevice :
	makedepend $(INCLUDES) $(MDFLAGS) -f$(DSTDIR)/Makefile $(jlcVcrDevice_SOURCES)

clean_jlcVcrDevice:
	-rm -f $(jlcVcrDevice_OBJECTS)

Clean_jlcVcrDevice:
	-rm -f $(jlcVcrDevice_MAKEFILE).bak $(jlcVcrDevice_OBJECTS) $(jlcVcrDevice_PLUGIN)


plugins: $(jlcVcrDevice_PLUGIN)
depend:	 depend_jlcVcrDevice
clean:	 clean_jlcVcrDevice
Clean:	 Clean_jlcVcrDevice

