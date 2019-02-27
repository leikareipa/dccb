:: Pacific C 7.

cd ..\src

set COMPILER_NAME="Pacific C 7"
set EXE_NAME="..\bin\t_pacc.exe"
set PATH=C:\PACC\BIN\;%PATH%
pacc -2 -7 -Epacc.err -AL16,16,4 -Bl -Zg -O%EXE_NAME% -IC:\PACC\INCLUDE *.c
@if ERRORLEVEL 1 goto fail
del *.obj
goto done

:fail
@echo Build failed.
:done
