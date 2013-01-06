#ifndef GRAFICO_H
#define GRAFICO_H

#include <iostream>
#include "SDL/SDL_image.h"

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

#include <irrlicht/irrlicht.h>

#include "Painter/Image.h"
using namespace irr;

class Painter
{
    public:
    SDL_Surface* screen = NULL;
    int screen_width;
    int screen_height;
    int screen_bpp;
    int camera_x,camera_y;
    Painter();
    ~Painter();
    Image* getTexture(std::string filename);
    void draw2DImage	(
	             Image* texture,
				 int size_x,int size_y,
				 int position_x,int position_y,
				 int scale,
				 bool flipHorizontally,
				 int depth_effect_x,
				 int depth_effect_y,
				 bool camera_align);
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
