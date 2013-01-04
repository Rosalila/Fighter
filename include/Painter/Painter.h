#ifndef GRAFICO_H
#define GRAFICO_H

#include <iostream>
#include "SDL/SDL_image.h"
#include "SDL/SDL_opengl.h"

#include <irrlicht/irrlicht.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

#include "Painter/LTexture.h"


using namespace irr;

class Painter
{

    public:
    bool renderQuad;
    LTexture* screen = NULL;
    int screen_width;
    int screen_height;
    int screen_bpp;
    int camera_x,camera_y;
    Painter(int *argcp, char **argv);
    ~Painter();
    LTexture* getTexture(std::string filename);
    void draw2DImage	(
	             LTexture* texture,
				 int size_x,int size_y,
				 int position_x,int position_y,
				 int scale,
				 bool flipHorizontally);
    void draw2DImageCameraAlign	(
	             LTexture* texture,
				 int size_x,int size_y,
				 int position_x,int position_y,
				 int scale,
				 bool flipHorizontally);
    void updateScreen();




std::string convertInt(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}
};
#endif
