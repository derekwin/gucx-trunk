#!/bin/sh

# 删除生成的文件
rm -f configure
rm -f config.h.in
rm -f aclocal.m4
rm -f install-sh
rm -f missing
rm -f depcomp
rm -f ltmain.sh
rm -f config.guess
rm -f config.sub
rm -f compile
rm -f config.h
rm -f config.h.in~
rm -f config.log
rm -f config.status
rm -f **Makefile
rm -f Makefile.in
rm -f stamp-h1
rm -f libtool
rm -f configure~
rm -rf src/gmem/*/.deps
rm -rf src/gmem/*/Makefile
rm -rf src/gmem/*/*.pc
rm -rf src/gmem/*.pc
rm -rf src/gmem/*libgmem.la
rm -rf src/gmem/Makefile
rm -rf src/gmem/*/.libs
rm -rf src/gmem/*/.dirstamp
rm -rf src/gmem/.libs
rm -rf src/gmem/*/*.lo
rm -rf src/gmem/*/*.o
rm -rf src/tools/*/.deps
rm -rf src/tools/*/*.o
rm -rf src/tools/*/Makefile
rm -f config/Makefile

# 删除生成的目录
rm -rf autom4te.cache

# 删除所有的 Makefile.in 文件
find . -name 'Makefile.in' -delete
