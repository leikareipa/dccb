:: Microsoft C/C++ 8.

cd ..\src

set COMPILER_NAME="Microsoft C/C++ 8"
set EXE_NAME="..\bin\t_vc15.exe"
set PATH=%PATH%;C:\VC15\BIN\
cl /f- /AL /Ox /G3 /Fe%EXE_NAME% /Ic:\vc15\include *.c /link c:\vc15\lib\
@if ERRORLEVEL 1 goto fail
del *.obj
goto done

:fail
@echo Build failed.
:done
