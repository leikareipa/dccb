:: Mix Power C 2.2

cd ..\src

set COMPILER_NAME="Mix Power C 2.2"
set EXE_NAME=t_pc.exe
set PATH=C:\POWERC\;%PATH%
pc /2 /a /e /f87 /ml *.c
@if ERRORLEVEL 1 goto fail
copy D_MAIN.EXE ..\bin\%EXE_NAME% /y
del D_MAIN.EXE
del *.MIX
del *.$$$
goto done

:fail
@echo Build failed.
:done
