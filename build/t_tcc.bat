:: Borland Turbo C 2.

cd ..\src

set COMPILER_NAME="Borland Turbo C 2"
set EXE_NAME="..\bin\t_tcc.exe"
set PATH=C:\TC\;%PATH%
tcc -a -1 -f87 -ml -Z -G -O -e%EXE_NAME% *.c
@if ERRORLEVEL 1 goto fail
del *.OBJ
goto done

:fail
@echo Build failed.
:done
