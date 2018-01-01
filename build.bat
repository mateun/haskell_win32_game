@echo off
echo Compiling C sources

g++ src\c\mycfuncs.c src\c\winstuff.c -c
move *.o build

echo.
echo Compiling Haskell source
ghc src\hs\funcs1.hs -c
move src\hs\*.o build

echo.
echo Linking everything
ghc build\funcs1.o build\winstuff.o build\mycfuncs.o -lgdi32 -lopenGL32 -lxinput -o build\game.exe









