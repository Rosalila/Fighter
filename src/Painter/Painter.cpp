#include "Painter/Painter.h"

Painter::Painter()
{
    screen_width = 1024;
    screen_height = 600;
    screen_bpp = 16;
    camera_x=camera_y=0;

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        std::cout<<"Error: Could not initialize SDL.";
        return;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

    //Set up the screen
    screen = SDL_SetVideoMode( screen_width, screen_height, screen_bpp, SDL_OPENGL /*| SDL_FULLSCREEN */);

    //Set the openGL state?
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glViewport( 0, 0, screen_width, screen_height );

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

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


Image* Painter::getTexture(std::string filename)
{
    SDL_Surface *surface;
    GLenum texture_format;
    GLint  nOfColors;
    GLuint texture;

    if ( (surface = IMG_Load(filename.c_str())) ) {

            // get the number of channels in the SDL surface
            nOfColors = surface->format->BytesPerPixel;
            if (nOfColors == 4)     // contains an alpha channel
            {
                    if (surface->format->Rmask == 0x000000ff)
                            texture_format = GL_RGBA;
                    //else
                            //texture_format = GL_BGRA;
            } else if (nOfColors == 3)     // no alpha channel
            {
                    if (surface->format->Rmask == 0x000000ff)
                            texture_format = GL_RGB;
                    //else
                            //texture_format = GL_BGR;
            } else {
                    printf("warning: the image is not truecolor..  this will probably break\n");
                    // this error should not go unhandled
            }

        // Have OpenGL generate a texture object handle for us
        glGenTextures( 1, &texture );

        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, texture );

        // Set the texture's stretching properties
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                          texture_format, GL_UNSIGNED_BYTE, surface->pixels );
    }
    else {
        printf("SDL could not load bag.png: %s\n", SDL_GetError());
        SDL_Quit();
        //return 1;
    }


    Image*image=new Image();
    image->setTexture(texture);
    image->setWidth(surface->w);
    image->setHeight(surface->h);

    // Free the SDL_Surface only if it was successfully created
    if ( surface ) {
        SDL_FreeSurface( surface );
    }

    return image;
}

void Painter::draw2DImage	(
             Image* texture,
             int size_x,int size_y,
             int position_x,int position_y,
             int scale,
             bool flipHorizontally)
{
//   // Clear the screen before drawing
//	glClear( GL_COLOR_BUFFER_BIT );
//
//    // Bind the texture to which subsequent calls refer to
//    glBindTexture( GL_TEXTURE_2D, texture->getTexture() );
//
//    glBegin( GL_QUADS );
//        // Top-left vertex (corner)
//        glTexCoord2i( 0, 0 );
//        glVertex3f( position_x, position_y, 0 );
//
//        // Bottom-left vertex (corner)
//        glTexCoord2i( 1, 0 );
//        glVertex3f( position_x, position_y+size_y, 0 );
//
//        // Bottom-right vertex (corner)
//        glTexCoord2i( 1, 1 );
//        glVertex3f( position_x+size_x, position_y+size_y, 0 );
//
//        // Top-right vertex (corner)
//        glTexCoord2i( 0, 1 );
//        glVertex3f( position_x+size_x, position_y, 0 );
//    glEnd();


  // Clear the screen before drawing
//	glClear( GL_COLOR_BUFFER_BIT );

    // Bind the texture to which subsequent calls refer to


    glBindTexture( GL_TEXTURE_2D, texture->getTexture() );

    glBegin( GL_QUADS );
        //Bottom-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f( 0.f+position_x, 0.f+position_y, 0.0f );

        //Bottom-right vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f( 0.f+position_x+size_x, 0.f+position_y, 0.f );

        //Top-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f( 0.f+position_x+size_x, 0.f+position_y+size_y, 0.f );

        //Top-left vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f( 0.f+position_x, 0.f+position_y+size_y, 0.f );
    glEnd();

//    glutSwapBuffers();
}

void Painter::draw2DImageCameraAlign	(
             Image* texture,
             int size_x,int size_y,
             int position_x,int position_y,
             int scale,
             bool flipHorizontally)
{
   // Clear the screen before drawing
//	glClear( GL_COLOR_BUFFER_BIT );

    // Bind the texture to which subsequent calls refer to
    glBindTexture( GL_TEXTURE_2D, texture->getTexture() );

    glBegin( GL_QUADS );
        // Top-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f( 100, 100, 0 );

        // Bottom-left vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f( 228, 100, 0 );

        // Bottom-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f( 228, 228, 0 );

        // Top-right vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f( 100, 228, 0 );
    glEnd();
}

void Painter::updateScreen()
{
    SDL_GL_SwapBuffers();
}
