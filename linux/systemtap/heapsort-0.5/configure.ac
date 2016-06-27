AC_INIT([heapsort], [0.4], [wcohen@redhat.com])


AM_INIT_AUTOMAKE
AC_PROG_CC
AC_PROG_CXX

#
# SystemTap support
#
AC_MSG_CHECKING([whether to include systemtap tracing support])
AC_ARG_ENABLE([systemtap],
	      [AS_HELP_STRING([--enable-systemtap],
	      		      [Enable inclusion of systemtap trace support])],
	      [ENABLE_SYSTEMTAP="${enableval}"], [ENABLE_SYSTEMTAP='no'])
AM_CONDITIONAL([ENABLE_SYSTEMTAP], [test x$ENABLE_SYSTEMTAP = xyes])
AC_MSG_RESULT(${ENABLE_SYSTEMTAP})

if test "x${ENABLE_SYSTEMTAP}" = xyes; then
  # Additional configuration for --enable-systemtap is HERE
  AC_CHECK_PROGS(DTRACE, dtrace)
  if test -z "$DTRACE"; then
    AC_MSG_ERROR([dtrace not found])
  fi
  AC_CHECK_HEADER([sys/sdt.h], [SDT_H_FOUND='yes'],
                [SDT_H_FOUND='no';
                   AC_MSG_ERROR([systemtap support needs sys/sdt.h header])])
  AC_DEFINE([HAVE_SYSTEMTAP], [1], [Define to 1 if using SystemTap probes.])
  AC_ARG_WITH([tapset-install-dir],
	      [AS_HELP_STRING([--with-tapset-install-dir], 
	         [The absolute path where the tapset dir will be installed])],
	      [if test "x${withval}" = x; then
		 ABS_TAPSET_DIR="\$(datadir)/systemtap/tapset"
	       else
		 ABS_TAPSET_DIR="${withval}"
	       fi], [ABS_TAPSET_DIR="\$(datadir)/systemtap/tapset"])
  AC_SUBST(ABS_TAPSET_DIR)
fi

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES(Makefile tapset/Makefile)

AC_OUTPUT

