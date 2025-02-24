@echo OFF

:: VERSIONING
set version= -std=c99

:: DEBUG OPTIONS
set debug= -Wall -Werror

:: SOURCE FILES
set source= src/main.c

:: LIBRARY OPTIONS
set headers= -Isrc/head

:: OUTPUT OPTIONS
set output= -o build/main.exe

:: MISC OPTIONS
set misc= -fsanitize=address

:: WORKING DIRECTORY
::pushd C:\msys64\usr\bin
::popd

:: FINAL COMPILER COMMAND
gcc %version% %debug% %source% %headers% %output%


cmd /k