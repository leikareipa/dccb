:: Microsoft C 5.

cd ..\src

set COMPILER_NAME="Microsoft C 5"
set EXE_NAME="..\bin\t_mc.exe"
set PATH=%PATH%;C:\MC\BIN\;C:\MC\LIB\
cl /AL /FPi87 /O /G2 /Fe%EXE_NAME% /IC:\MC\INCLUDE *.c /link C:\MC\LIB\
@if ERRORLEVEL 1 goto fail
del *.OBJ
goto done

:fail
@echo Build failed.
:done
