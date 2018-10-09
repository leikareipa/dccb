:: Microsoft C 5.

:: Assumes the directory above this contains the source code.
cd..

set COMPILER_NAME="Microsoft C 5"
set EXE_NAME=t_mc.exe
set PATH=%PATH%;C:\MC\BIN\;C:\MC\LIB\
cl /AL /FPi87 /O /G2 /Fe%EXE_NAME% /IC:\MC\INCLUDE *.c /link C:\MC\LIB\
@if ERRORLEVEL 1 goto fail
del *.OBJ
copy %EXE_NAME% bin\%EXE_NAME%
del %EXE_NAME%
goto done

:fail
:done
