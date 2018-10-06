:: Microsoft Visual C++ 1.5 (Microsoft C 8).

cd..

setlocal
set EXE_NAME=t_vc15.exe
set PATH=%PATH%;C:\VC15\BIN\
cl /f- /AL /Ox /G3 /Fe%EXE_NAME% /Ic:\vc15\include *.c /link c:\vc15\lib\

copy %EXE_NAME% bin\%EXE_NAME% /y
del %EXE_NAME%
del *.obj

