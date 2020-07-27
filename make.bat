@echo off

path | findstr /C:"Microsoft Visual Studio" > nul || (
    call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
)

set INCLUDE_ORIGINAL=%INCLUDE%
set INCLUDE=%INCLUDE%;%ProgramFiles%\boost\boost_1_73_0

if [%1] == [] (
    call:bin\Main.exe
) else if [%1] == [main] (
    call:bin\Main.exe
) else if [%1] == [clean] (
    call:clean
) else (
    call:error
)

set INCLUDE=%INCLUDE_ORIGINAL%
set INCLUDE_ORIGINAL=
goto done


::Build
:bin\Main.exe
call:bin
if not exist bin\Main.exe (
    call:Main_exe_objs
    link /machine:x64 /out:bin\Main.exe obj\*
)
goto:eof
:Main_exe_objs
call:obj
for %%i in (src\Sources\*) do (
    if not exist obj\%%~ni.obj (
        cl /c /EHsc /I"%cd%\src\Headers" /Foobj\%%~ni.obj %%i
    )
)
goto:eof

::Directories
:bin
if not exist bin (
    md bin
)
goto:eof

:obj
if not exist obj (
    md obj
)
goto:eof


::Utilies
:clean
set del_list=bin obj
for %%i in (%del_list%) do (
    if exist %%i (
        del /q %%i\*
    )
)
set del_list=
goto:eof


:error
echo Invalid arguments
goto:eof


:done