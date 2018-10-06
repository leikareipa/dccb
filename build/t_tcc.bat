:: Borland Turbo C 2.

cd..

setlocal
set EXE_NAME=t_tcc.exe
set PATH=%PATH%;C:\TC\
tcc -a -1 -f87 -ml -Z -G -O -e%EXE_NAME% *.c

copy %EXE_NAME% bin\%EXE_NAME%
del %EXE_NAME%
del *.OBJ

