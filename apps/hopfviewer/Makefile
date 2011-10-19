
TARGET = hopfviewer

CXX_SRC = \
	UI.cxx \
	Viewer.cxx \
	Torus.cxx \
	Torus_Mod.cxx \
	Torus_Controller.cxx \
	main.cxx \
	help/help_text.cxx \
	../../platform/fltk/hopfviewer/UI.cxx \

EXTRA_INC_DIRS = \
	-I. \
	-I../.. \
	-I../../platform/fltk \
	-I../../platform/fltk/hopfviewer \

EXTRA_OBJS = \
	../../esve/$(LIB_PREFIX)esve$(LIB_SUFFIX) \
	../../platform/fltk/esve/$(LIB_PREFIX)esve_fltk$(LIB_SUFFIX) \

include ../../Makefile.defs
include ../../make/Makefile.rules
include ../../make/Makefile.exec
sinclude Makefile.dep

