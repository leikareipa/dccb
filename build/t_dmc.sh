#!/bin/bash

# Digital Mars C 8.

EXE_NAME="t_dmc.exe"
DMC_PATH=~/compi/dmc
BUILD_OPTIONS="-w- -mld -a2 -5 -f -o $EXE_NAME -o+speed"

cd ../src
wine "$DMC_PATH/bin/dmc.exe" *.c $BUILD_OPTIONS -I$DMC_PATH\\include &&
mv $EXE_NAME ../bin/$EXE_NAME
rm *.obj
