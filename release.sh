#!/bin/sh

# This script automates the necessary steps for releasing the SSR. 

run_command()
{
  # show message; run command; if unsuccessful, show error message and exit
  echo $0: Running \"$@\" ...
  "$@" || { status=$?; echo $0: Error in \"$@\"!; exit $status; }
}

# change to the directory where the script is located
# (in case it was started from somewhere else)
cd $(dirname $0)

if [ "$(git symbolic-ref --short HEAD)" != master ]
then
  echo \"$0\" should be called on the master branch!; exit 42;
fi

# first of all, make "tabula rasa"
run_command ./cleanse.sh

# prepare the build system
run_command ./autogen.sh

# create the user manual
(cd doc/manual && run_command latexmk) || exit

# prepare Makefiles
run_command ./configure

# enable parallel make if CONCURRENCY_LEVEL is defined
if test ! -z $CONCURRENCY_LEVEL; then
  MAKE_OPTIONS=-j$CONCURRENCY_LEVEL
fi

# create tarball and run some basic tests
run_command make distcheck $MAKE_OPTIONS

echo $0: Done!

# Settings for Vim (http://www.vim.org/), please do not remove:
# vim:softtabstop=2:shiftwidth=2:expandtab:textwidth=80
