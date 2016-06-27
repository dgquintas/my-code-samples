# Makefile.am for heapsort
# W. E. Cohen

#
DEBUG= -g
OPTIMIZE=
CCFLAGS=-Wall $(DEBUG) $(OPTIMIZE)
DTRACE=@DTRACE@

bin_PROGRAMS = heapsort
heapsort_SOURCES = heapsort.cxx probes.d trace.h
BUILT_SOURCES = probes.h
EXTRA_DIST = heapsort.spec \
	heap_tap_all.stp heap_time_phases.stp


SUBDIRS = tapset
DIST_SUBDIRS = $(SUBDIRS)

heapsort_LDADD =

clean-local:
	rm -f *.gcov *.gcno *.gcda ${PACKAGE_TARNAME}-*.tar.gz
	rm -rf ${PACKAGE_TARNAME}-${PACKAGE_VERSION}
	rm -rf $(TEST_COV_DIR)

.PHONY:

if ENABLE_SYSTEMTAP
probes.h: probes.d
	$(DTRACE) -C -h -s $< -o $@

probes.o: probes.d
	$(DTRACE) -C -G -s $< -o $@

heapsort_LDADD += probes.o
endif

rpm: dist
	mkdir -p `rpm --eval %_specdir`
	mkdir -p `rpm --eval %_srcrpmdir`
	mkdir -p `rpm --eval %_rpmdir`
	mkdir -p `rpm --eval %_builddir`
	mkdir -p `rpm --eval %_buildroot`
	rpmbuild --define "_sourcedir $(PWD)/" -ta \
		${PACKAGE_TARNAME}-${PACKAGE_VERSION}.tar.gz $(RPMBUILDFLAGS)
