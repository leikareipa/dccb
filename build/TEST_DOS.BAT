:: Runs all DOS-based builds to see whether any of them fail.

set COMPILER_NAME="(unspecified compiler)"

call t_vc15.bat
@if ERRORLEVEL 1 goto err
cd build

call t_mc.bat
@if ERRORLEVEL 1 goto err
cd build

call t_pacc.bat
@if ERRORLEVEL 1 goto err
cd build

call t_tcc.bat
@if ERRORLEVEL 1 goto err
cd build

cls
@echo All DOS builds succeeded.
@goto done

:err
cd build
@echo BUILD FAILED on %COMPILER_NAME%

:done
