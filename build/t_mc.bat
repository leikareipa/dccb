:: Microsoft C 5.

cd..

setlocal
set EXE_NAME=t_mc.exe
set PATH=%PATH%;C:\MC\BIN\;C:\MC\LIB\
cl /AL /FPi87 /O /G2 /Fe%EXE_NAME% /IC:\MC\INCLUDE *.c /link C:\MC\LIB\

del *.OBJ
copy %EXE_NAME% bin\%EXE_NAME%
del %EXE_NAME%
