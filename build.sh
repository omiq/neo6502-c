#!/bin/sh

# Neo6502 build script
# requires 'cc65' compiler suite


# cc65 search paths
readonly _CC65_HOME="${CC65_HOME:-$HOMEBREW_CELLAR/cc65/2.19/share/cc65}"


# environment checks
for prog in ar65 ca65 cl65
do  which $prog > /dev/null || ! echo "could not find '$prog' program" || exit 1
done
for inc in "$_CC65_HOME"/{include/{stdio.h,stdint.h},asminc/zeropage.inc}
do  dir=$(dirname "$inc")
    test -d "$dir" || ! echo "CC65 include directory '$dir' does not exist" || exit 1
    test -f "$inc" || ! echo "CC65 include file '$inc' does not exist"      || exit 1
done

# delete
rm -f $1.neo

# compile
export CC65_HOME="$_CC65_HOME"
ca65 crt0.s
ar65 a neo6502.lib crt0.o
cl65 --static-locals -t none -C neo6502.cfg -O --cpu 65c02 -m $1.map \
     -o $1.neo $1.c neo6502.lib

# launch emulator
test -f $1.neo && neo $1.neo@800 cold
