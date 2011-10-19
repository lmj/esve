
TARGET = polynomialviewer

CXX_SRC = \
	UI.cxx \
	Polynomial_Surface.cxx \
	Plane.cxx \
	Viewer.cxx \
	main.cxx \
	help/help_text.cxx \
	../../platform/fltk/polynomialviewer/UI.cxx \

EXTRA_INC_DIRS = \
	-I. \
	-I../.. \
	-I../../platform/fltk \
	-I../../platform/fltk/polynomialviewer \

EXTRA_OBJS = \
	../../esve/$(LIB_PREFIX)esve$(LIB_SUFFIX) \
	../../platform/fltk/esve/$(LIB_PREFIX)esve_fltk$(LIB_SUFFIX) \

include ../../Makefile.defs
include ../../make/Makefile.rules
include ../../make/Makefile.exec
sinclude Makefile.dep

