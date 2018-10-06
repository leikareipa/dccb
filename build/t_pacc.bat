:: Pacific C 7.

cd..

setlocal
set EXE_NAME=t_pacc.exe
set PATH=%PATH%;C:\PACC\BIN\
pacc -2 -7 -Epacc.err -AL16,16,4 -Bl -Zg -O%EXE_NAME% -IC:\PACC\INCLUDE *.c

copy %EXE_NAME% bin\%EXE_NAME% /y
del %EXE_NAME%
del *.obj

