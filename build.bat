REM build with mingw, set the system path to mingw/bin 
gcc -o encode encode.c fastlz.c
gcc -o decode decode.c fastlz.c