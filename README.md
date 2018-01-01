# Win32 Haskell Game Programming

This is a small skeleton for writing Win32 games with OpenGL graphics in Haskell. 

The basic architecture is as follows: 

* The main program is written in Haskell
* In the C part, a Win32 window with an OpenGL context is setup 
  (this is mainly boilerplate code and I found it is not very useful to 
  do this in Haskell)
* The game loop is also written in the C part and does a callback to the 
  Haskell "gameUpdate" function every frame. 
* The game logic itself is meant to be programmed in Haskell. 
* To draw something on the screen, the C interface provides a number of 
  functions to call from Haskell for drawing 2D sprites, 3D meshes, clearing the screen etc. 
  
### How to build
##### Prerequisites
* Haskell compiler (ghc) in the PATH; tested with version 8.0.2
* MinGW compiler (g++) in the PATH; testwed with 7.2.0

create a folder called "build": 
```
$ mkdir build
```

##### Building
Just invoke 
``` Haskell
$ build.bat
```

The binary of the game will be put into the "build" directory and can be invoked via 

```
.\game.exe
```
  
### How to write your own game
For the time being, just open funcs1.hs and modify the code in "gameUpdate" accordingly


### Callable C functions
-- TODO
  
### Version history
* 0.0.1 - basic interaction between Haskell and C; Win32 window with OpenGL context up and running; Haskell gameUpdate called each frame;
  
  
### >> WORK IN PROGRESS <<
