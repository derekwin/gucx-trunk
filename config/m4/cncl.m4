#
# Copyright (c) NVIDIA CORPORATION & AFFILIATES, 2001-2017. ALL RIGHTS RESERVED.
# See file LICENSE for terms.
#

AC_DEFUN([UCX_CHECK_CNCL],[

AS_IF([test "x$cncl_checked" != "xyes"],
   [
    AC_ARG_WITH([cncl],
                [AS_HELP_STRING([--with-cncl=(DIR)], [Enable the use of CNCL (default is guess).])],
                [], [with_cncl=guess])

    AS_IF([test "x$with_cncl" = "xno"],
        [
         cncl_happy=no
         have_cncl_static=no
        ],
        [
         save_CPPFLAGS="$CPPFLAGS"
         save_LDFLAGS="$LDFLAGS"
         save_LIBS="$LIBS"

         CNCL_CPPFLAGS=""
         CNCL_LDFLAGS=""
         CNCL_LIBS=""

         AS_IF([test ! -z "$with_cncl" -a "x$with_cncl" != "xyes" -a "x$with_cncl" != "xguess"],
               [ucx_check_cncl_dir="$with_cncl"
                CNCL_CPPFLAGS="-I$with_cncl/include"
                CNCL_LDFLAGS="-L$with_cncl/lib64 -L$with_cncl/lib"])

         CPPFLAGS="$CPPFLAGS $CNCL_CPPFLAGS"
         LDFLAGS="$LDFLAGS $CNCL_LDFLAGS"

         # Check cncl header files
         AC_CHECK_HEADERS([cncl.h cnrt.h cn_api.h],
                          [cncl_happy="yes"], [cncl_happy="no"])

      #    # Check cncl libraries
      #    AS_IF([test "x$cncl_happy" = "xyes"],
      #          [AC_CHECK_LIB([cnrt], [cnrtGetDevice],
      #                        [CNCL_LIBS="$CNCL_LIBS -lcndrv"], [cncl_happy="no"])])

      CNCL_LIBS="$CNCL_LIBS -lcnrt -lcndrv -lmluops -lrt -ldl -lpthread"

      CPPFLAGS="$save_CPPFLAGS"
      LDFLAGS="$save_LDFLAGS"
      LIBS="$save_LIBS"

      AS_IF([test "x$cncl_happy" = "xyes"],
            [AC_SUBST([CNCL_CPPFLAGS], ["$CNCL_CPPFLAGS"])
               AC_SUBST([CNCL_LDFLAGS], ["$CNCL_LDFLAGS"])
               AC_SUBST([CNCL_LIBS], ["$CNCL_LIBS"])
               AC_DEFINE([HAVE_CNCL], 1, [Enable CNCL support])],
            [AS_IF([test "x$with_cncl" != "xguess"],
                     [AC_MSG_ERROR([CNCL support is requested but cncl packages cannot be found])],
                     [AC_MSG_WARN([CNCL not found])])])

      ]) # "x$with_cncl" = "xno"

      cncl_checked=yes
      AM_CONDITIONAL([HAVE_CNCL], [test "x$cncl_happy" != xno])

   ]) # "x$cncl_checked" != "xyes"

]) # UCX_CHECK_CNCL
