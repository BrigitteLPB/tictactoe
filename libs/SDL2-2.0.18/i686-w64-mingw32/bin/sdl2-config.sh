#!/bin/sh

prefix=C:/Users/BrigitteLPB/OneDrive/CODE/C/pongSDL/libs/SDL2-2.0.18/i686-w64-mingw32
exec_prefix=${prefix}
exec_prefix_set=no
libdir=${exec_prefix}/lib

#usage="\
#Usage: $0 [--prefix[=DIR]] [--exec-prefix[=DIR]] [--version] [--cflags] [--libs]"
usage="\
Usage: $0 [--prefix[=DIR]] [--exec-prefix[=DIR]] [--version] [--cflags] [--libs] [--static-libs]"

if test $# -eq 0; then
      echo "${usage}" 1>&2

      read
      exit 1
fi

while test $# -gt 0; do
  case "$1" in
  -*=*) optarg=`echo "$1" | sed 's/[-_a-zA-Z0-9]*=//'` ;;
  *) optarg= ;;
  esac

  case $1 in
    --prefix=*)
      prefix=$optarg
      if test $exec_prefix_set = no ; then
        exec_prefix=$optarg
      fi
      ;;
    --prefix)
      echo $prefix
      ;;
    --exec-prefix=*)
      exec_prefix=$optarg
      exec_prefix_set=yes
      ;;
    --exec-prefix)
      echo $exec_prefix
      ;;
    --version)
      echo 2.0.18
      ;;
    --cflags)
      echo -I${prefix}/include/SDL2  -Dmain=SDL_main
      ;;
    --libs)
      echo -L${exec_prefix}/lib  -lmingw32 -lSDL2main -lSDL2 -mwindows
      ;;
    --static-libs)
#    --libs|--static-libs)
      echo -L${exec_prefix}/lib -lmingw32 -lSDL2main -lSDL2 -mwindows  -Wl,--dynamicbase -Wl,--nxcompat -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
      ;;
    *)
      echo "${usage}" 1>&2

      read
      exit 1
      ;;
  esac
  shift
done

read