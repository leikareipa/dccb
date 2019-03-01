:: Microsoft QuickC 1.

cd ..\src

set COMPILER_NAME="Microsoft QuickC 1"
set EXE_NAME=..\bin\t_qc1.exe
set PATH=C:\QUICKC\;%PATH%
qcl /W0 /AL /FPi87 /O /G2 /Gs /Fe%EXE_NAME% /IC:\QUICKC\INCLUDE *.c /link C:\QUICKC\
@if ERRORLEVEL 1 goto fail
del *.OBJ
goto done

:fail
@echo Build failed.
:done
