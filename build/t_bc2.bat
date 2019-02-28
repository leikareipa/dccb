:: Borland C++ 2.

cd ..\src

set COMPILER_NAME="Borland C++ 2"
set EXE_NAME=t_bc2.exe
set PATH=C:\BORLANDC\BIN\;%PATH%
bcc -a -1 -f87 -ml -Z -G -O -e%EXE_NAME% *.c
@if ERRORLEVEL 1 goto fail
copy %EXE_NAME% ..\bin\%EXE_NAME% /y
del %EXE_NAME%
del *.OBJ
goto done

:fail
@echo Build failed.
:done
