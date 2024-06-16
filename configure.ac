AC_PREREQ([2.63])

define([gucxt_ver_major], 0)  # Major version. Usually does not change.
define([gucxt_ver_minor], 1) # Minor version. Increased for each release.
define([gucxt_ver_patch], 0)  # Patch version. Increased for a bugfix release.
define([gucxt_ver_extra], )   # Extra version string. Empty for a general release.

define([libgucxt_so_version], 0:0:0)

AC_INIT([gucxt], [gucxt_ver_major.gucxt_ver_minor])
AM_INIT_AUTOMAKE([foreign subdir-objects])

# 如果这些变量在脚本执行之前没有被设置，那么它们将被初始化为空字符串。允许脚本的调用者通过环境变量来影响脚本的行为，
# 同时确保即使这些环境变量没有被设置，脚本也能正常运行。
: ${CPPFLAGS=""}
: ${CFLAGS=""}
: ${CXXFLAGS=""}
config_flags="$*"

AC_USE_SYSTEM_EXTENSIONS
AC_CONFIG_HEADERS([config.h])
AH_TOP([
#ifndef GUCXT_CONFIG_H
#define GUCXT_CONFIG_H
])
AH_BOTTOM([
#endif /* GUCXT_CONFIG_H */
])

AC_CONFIG_MACRO_DIR([config/m4])

define([gucxt_prefix], [./install])
AC_PREFIX_DEFAULT([gucxt_prefix])

top_top_srcdir=$srcdir
AC_SUBST(top_top_srcdir)

MAJOR_VERSION=gucxt_ver_major
MINOR_VERSION=gucxt_ver_minor
PATCH_VERSION=gucxt_ver_patch
EXTRA_VERSION=gucxt_ver_extra
VERSION=$MAJOR_VERSION.$MINOR_VERSION.$PATCH_VERSION$EXTRA_VERSION
SOVERSION=libgucxt_so_version
AC_SUBST(MAJOR_VERSION)
AC_SUBST(MINOR_VERSION)
AC_SUBST(PATCH_VERSION)
AC_SUBST(EXTRA_VERSION)
AC_SUBST(SCM_VERSION)
AC_SUBST(SOVERSION)

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_SED
AC_PROG_INSTALL
LT_INIT
LT_LIB_M
AC_C_RESTRICT
AC_FUNC_STRERROR_R


#
# Define SHARED_LIB preprocessor macro when building a shared library
#
lt_prog_compiler_pic="$lt_prog_compiler_pic -DGUCXT_SHARED_LIB"

#
# Force link_all_deplibs=yes for libtool, otherwise it will not
# link against dependency libs
#
link_all_deplibs=yes

#
# Save config flags for version dump tool
#
AC_DEFINE_UNQUOTED([GUCXT_CONFIGURE_FLAGS], ["$config_flags"], [GUCXT configure flags])

#
# Define path of gucxt.conf configuration file
#
AC_SUBST([gucxt_config_dir], [${sysconfdir}/gucxt])

#
# Provide the functionality of AS_VAR_APPEND if Autoconf does not have it.
#
m4_ifdef([AS_VAR_APPEND],
[m4_copy([AS_VAR_APPEND], [ucx_AS_VAR_APPEND])],
[m4_define([ucx_AS_VAR_APPEND],
[AS_VAR_SET([$1], [AS_VAR_GET([$1])$2])])])

#
# Paths for loadable modules
#
AC_SUBST([modulesubdir],   [${PACKAGE_NAME}])               # module directory names
AC_SUBST([moduledir],      [${libdir}/${modulesubdir}])     # module installation directory
AC_SUBST([localmoduledir], ['$(abs_top_builddir)/modules']) # local directory for module symlinks
AC_SUBST([objdir],         [${objdir}])                     # libtool objects dir, usually .libs
AC_SUBST([shrext],         [${shrext_cmds}])                # libtool shared library extension
AC_DEFINE_UNQUOTED([GUCXT_MODULE_SUBDIR], ["${modulesubdir}"], [GUCXT module sub-directory])


#
# Additional m4 files
#
m4_include([config/m4/init.m4])

AS_IF([test "x$with_docs_only" = xyes],
    [
        AM_CONDITIONAL([DOCS_ONLY], [true])
        AM_CONDITIONAL([HAVE_CUDA], [false])
        AM_CONDITIONAL([HAVE_CNCL], [false])
        AM_CONDITIONAL([HAVE_ROCM], [false])
    ],
    [
        AM_CONDITIONAL([DOCS_ONLY], [false])
        m4_include([config/m4/cuda.m4])
        m4_include([config/m4/cncl.m4])
        m4_include([config/m4/rocm.m4])
        m4_include([src/gmem/configure.m4])


    ])

#
# Print which transports are built
#
build_modules="${gmem_modules}"
build_modules="${build_modules}${gmem_rocm_modules}"
build_modules="${build_modules}${gmem_cncl_modules}"
build_modules="${build_modules}${gmem_cuda_modules}"
AC_SUBST([build_modules], [${build_modules}])

#
# Final output
#
AC_CONFIG_FILES([
    Makefile
    src/tools/info/Makefile
    config/Makefile
    ])

AC_OUTPUT

#
# Print build configuration
#
AC_MSG_NOTICE([=========================================================])
AS_IF([test "x$with_docs_only" = xyes],
[
    AC_MSG_NOTICE([Building documents only])
],
[
    AC_MSG_NOTICE([GUCX build configuration:])
    AC_MSG_NOTICE([        Build prefix:   ${prefix}])
    AC_MSG_NOTICE([  Preprocessor flags:   ${BASE_CPPFLAGS}])
    AC_MSG_NOTICE([          C compiler:   ${CC} ${BASE_CFLAGS}])
    AC_MSG_NOTICE([        C++ compiler:   ${CXX} ${BASE_CXXFLAGS}])
    AC_MSG_NOTICE([        GMEM modules:   <$(echo ${gmem_modules}|tr ':' ' ') >])
    AC_MSG_NOTICE([        Info modules:   <$(echo ${tools_info_modules}|tr ':' ' ') >])
    AC_MSG_NOTICE([=========================================================])
])