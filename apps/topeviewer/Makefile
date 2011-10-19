
TARGET = topeviewer

CXX_SRC = \
	Tope.cxx \
	Tope_Mod.cxx \
	Tope_File.cxx \
	Tope_Geom.cxx \
	Tube.cxx \
	UI.cxx \
	Viewer.cxx \
	main.cxx \
	help/help_text.cxx \
	readers/Tope_Reader.cxx \
	readers/Default_Reader.cxx \
	readers/Line_Oriented_Reader.cxx \
	readers/V_Reader.cxx \
	readers/Evolver_Reader.cxx \
	readers/Universal_Reader.cxx \

EXTRA_INC_DIRS = \
	-I. \
	-I../.. \

EXTRA_OBJS = \
	../../esve/$(LIB_PREFIX)esve$(LIB_SUFFIX) \
	../../platform/fltk/esve/$(LIB_PREFIX)esve_fltk$(LIB_SUFFIX) \

include ../../Makefile.defs
include ../../make/Makefile.rules
include ../../make/Makefile.exec
sinclude Makefile.dep
