:: Borland Turbo C 2.

cd ..\src

set COMPILER_NAME="Borland Turbo C 2"
set EXE_NAME=t_tcc.exe
set PATH=C:\TC\;%PATH%
tcc -a -1 -f87 -ml -Z -G -O -e%EXE_NAME% *.c
@if ERRORLEVEL 1 goto fail
copy %EXE_NAME% ..\bin\%EXE_NAME% /y
del %EXE_NAME%
del *.OBJ
goto done

:fail
@echo Build failed.
:done
