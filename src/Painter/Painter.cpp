#include "Painter/Painter.h"

Painter::Painter()
{
    screen_width = 640;
    screen_height = 480;
    screen_bpp = 32;
    camera_x=camera_y=0;

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        std::cout<<"Error: Could not initialize SDL.";
        return;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( screen_width, screen_height, screen_bpp, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        std::cout<<"Error: Could not initialize SDL screen.";
        return;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Rosalila fighter engine", NULL );

    //If everything initialized fine
    std::cout<<"Success! SDL initialized.";
    return;
}

Painter::~Painter()
{
    //Free the surface
    SDL_FreeSurface( screen );

    //Quit SDL
    SDL_Quit();
}


SDL_Surface* Painter::getTexture(std::string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

void Painter::draw2DImage	(
             SDL_Surface* texture,
             int size_x,int size_y,
             int position_x,int position_y,
             int scale,
             bool flipHorizontally)
{
    //Rectangle to hold the offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = position_x;
    offset.y = position_y;

    //Blit the surface
    SDL_BlitSurface( texture, NULL, screen, &offset );
}

void Painter::draw2DImageCameraAlign	(
             SDL_Surface* texture,
             int size_x,int size_y,
             int position_x,int position_y,
             int scale,
             bool flipHorizontally)
{
    //Rectangle to hold the offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = position_x+camera_x;
    offset.y = position_y+camera_y;

    //Blit the surface
    SDL_BlitSurface( texture, NULL, screen, &offset );
}

void Painter::updateScreen()
{
    if( SDL_Flip( screen ) == -1 )
    {
        std::cout<<"Error: Could not update screen.";
    }
}
