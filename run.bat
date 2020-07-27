@echo off
call:clean
call:build
call:invoke
goto done
:clean
call make clean
goto:eof
:build
call make main
goto:eof
:invoke
bin\main
goto:eof
:done
pause
