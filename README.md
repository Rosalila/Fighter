Rosalila Fighter Engine
=======================
rosalilastudio.com
github.com/rosalila/fighter


Build instructions using Code::Blocks:

1. Install the dependencies
---------------------------
* apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
or
* yum install SDL-devel SDL_mixer-devel SDL_image-devel SDL_ttf-devel freeglut-devel 

2. In Code::Blocks: "Linker settings" -> "Other linker options"
---------------------------------------------------------------
*   lGL
*   lglut
*   lGLU
*   lSDL
*   lSDL_image
*   lSDL_ttf
*   lSDL_mixer
*   lsmpeg

4. Create a folder named Rosalila/ and clone the Rosalila Engine (https://github.com/Rosalila/engine) code inside.
-----------------------------------------------------------------------------
 
5. In Code::Blocks: "Search directories" -> "Compiler"
------------------------------------------------------
*   Rosalila

6. Add a exiting game assests so you can test the engine
--------------------------------------------------------

7. Celebrate
------------
