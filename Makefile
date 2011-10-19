
DIRS = \
	esve \
	platform \
	apps \
	examples \

include make/Makefile.node

distclean : 
	(test -e Makefile.defs && $(MAKE) depclean clean) || true
	(test -e Makefile.defs && cd test && $(MAKE) depclean clean) || true
	find . \( -name "*.o" -or -name Makefile.dep \) -exec rm \{} \;
	rm -f Makefile.defs
	rm -f config.* configure
	rm -rf autom4te.cache
	rm -f warnings warnings-compile
	rm -rf documentation/esve
	rm -rf documentation/code
	rm -rf documentation/topeviewer-data

doc : 
	rm -rf documentation/code
	mkdir documentation/code
	cp ./examples/waves/waves.cxx documentation/code
	cp ./examples/monomial/monomial.cxx documentation/code
	cp ./examples/poles/poles.cxx documentation/code
	cp ./examples/simple3d/simple3d.cxx documentation/code
	cp ./examples/simple4d/simple4d.cxx documentation/code
	rm -rf documentation/topeviewer-data
	cp -R ./apps/topeviewer/data documentation/topeviewer-data
	rm -rf documentation/topeviewer-data/.svn
	ruby make/topeviewer-data.rb
	doxygen ./make/Doxyfile

RUN_TRIPWIRE = ruby tripwire/tripwire.rb . --prefix tripwire --sysinclude --exclude 'template.cxx|tripwire'

tripwire : 
	$(RUN_TRIPWIRE)

tripwire-undo : 
	$(RUN_TRIPWIRE) --undo

warnings-compile :
	$(MAKE) all WARNINGS="`cat make/warnings`" 2>&1 | tee warnings-compile

warnings :
	cat warnings-compile | $(SHELL) make/warnings-filter.sh > warnings

debug-compile :
	$(MAKE) all OPTIMIZE="-g -O -D_GLIBCXX_DEBUG"

sync :
	ruby make/message.rb
	ruby make/frames.rb
	ruby make/viewers.rb
	ruby make/specs.rb
	cd apps/topeviewer/help && ruby ../../../make/help-text.rb
	cd apps/hopfviewer/help && ruby ../../../make/help-text.rb
	cd apps/polynomialviewer/help && ruby ../../../make/help-text.rb

.PHONY : all distclean doc warnings-compile warnings tripwire tripwire-undo debug-modify debug-undo debug-compile sync


