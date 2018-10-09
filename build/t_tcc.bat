:: Borland Turbo C 2.

:: Assumes the directory above this contains the source code.
cd..

set COMPILER_NAME="Borland Turbo C 2"
set EXE_NAME=t_tcc.exe
set PATH=%PATH%;C:\TC\
tcc -a -1 -f87 -ml -Z -G -O -e%EXE_NAME% *.c
@if ERRORLEVEL 1 goto fail
copy %EXE_NAME% bin\%EXE_NAME%
del %EXE_NAME%
del *.OBJ
goto done

:fail
:done
