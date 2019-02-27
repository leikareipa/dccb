#!/bin/bash

# Open Watcom C.

EXE_NAME="t_ow.exe"
OW_PATH=~/compi/watcom
BUILD_OPTIONS="-bcl=dos -ml -oneatx -oh -ei -zp2 -5 -fpi87 -fp5 -sg -k16384 -fe=$EXE_NAME"

cd ../src
export WATCOM=$OW_PATH
export INCLUDE=$WATCOM/h
PATH=$PATH:~/compi/watcom/binl
wcl $BUILD_OPTIONS *.c

rm *.o
mv $EXE_NAME ../bin/$EXE_NAME

