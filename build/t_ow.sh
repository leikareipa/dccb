#!/bin/bash

# Open Watcom C.

EXE_NAME=t_ow.exe
OW_PATH=~/compi/watcom
BUILD_OPTIONS="-bcl=dos -ml -oneatx -oh -ei -zp2 -5 -fpi87 -fp5 -sg -k16384 -fe=$EXE_NAME"

cd ../src
export WATCOM=$OW_PATH
export INCLUDE=$WATCOM/h
PATH=$PATH:~/compi/watcom/binl
wcl $BUILD_OPTIONS *.c
mv t_ow.exe ../bin/$EXE_NAME

rm *.o
