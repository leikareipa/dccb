:: Borland C++ 2.

cd ..\src

set COMPILER_NAME="Borland C++ 2"
set EXE_NAME=..\bin\t_bc2.exe
set PATH=C:\BORLANDC\BIN\;%PATH%
bcc -a -1 -f87 -ml -Z -G -O -e%EXE_NAME% *.c
@if ERRORLEVEL 1 goto fail
del *.OBJ
goto done

:fail
@echo Build failed.
:done
