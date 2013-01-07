#include "Painter/Painter.h"

Painter::Painter()
{
    screen=NULL;

    screen_width = 1280;
    screen_height = 800;

    int screen_resized_width=1024;
    int screen_resized_height=600;

    screen_bpp = 16;
    camera_x=camera_y=0;

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        writeLogLine(SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

    //Set up the screen
    screen = SDL_SetVideoMode( screen_resized_width, screen_resized_height, screen_bpp, SDL_OPENGL /*| SDL_FULLSCREEN */);

    //Set the openGL state?
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glViewport( 0, 0, screen_resized_width, screen_resized_height );

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(0.0f, 1280, 800, 0.0f, -1.0f, 1.0f);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        writeLogLine("Error: Could not initialize SDL screen.");
        return;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Rosalila fighter engine", NULL );

    //If everything initialized fine
    writeLogLine("Success! SDL initialized.");
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
                writeLogLine("Warning: the image is not truecolor. This will probably break.");
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
        std::string sdl_error=SDL_GetError();
        writeLogLine("SDL could not load bag.png: "+sdl_error);
        SDL_Quit();
        return NULL;
    }


    Image*image=new Image();
    image->setTexture(texture);
    image->setWidth(surface->w);
    image->setHeight(surface->h);

    // Free the SDL_Surface only if it was successfully created
    if ( surface ) {
        SDL_FreeSurface( surface );
    }

    writeLogLine(filename+" loaded");

    return image;
}

void Painter::draw2DImage	(
             Image* texture,
             int size_x,int size_y,
             int position_x,int position_y,
             int scale,
             bool flipHorizontally,
             int depth_effect_x,
             int depth_effect_y,
             bool camera_align)
{
    glEnable( GL_TEXTURE_2D );

    GLfloat x1=0.f+position_x;
    GLfloat y1=0.f+position_y;
    GLfloat x2=0.f+position_x+size_x;
    GLfloat y2=0.f+position_y+size_y;

    if(flipHorizontally)
    {
        GLfloat temp=x1;
        x1=x2;
        x2=temp;
    }

    if(camera_align)
    {
        x1-=camera_x;
        y1+=camera_y;
        x2-=camera_x;
        y2+=camera_y;
    }

    glBindTexture( GL_TEXTURE_2D, texture->getTexture() );
    glColor3ub(255, 255, 255);
    glBegin( GL_QUADS );
        //Bottom-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f( x1, y1, 0.0f );

        //Bottom-right vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f( x2, y1, 0.f );

        //Top-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f( x2, y2, 0.f );

        //Top-left vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f( x1, y2, 0.f );

    glEnd();
}

void Painter::drawRectangle(int x,int y,int width,int height,int red,int green,int blue,int alpha,bool camera_align)
{
    glDisable(GL_TEXTURE_2D);
    GLubyte r=red;
    GLubyte g=green;
    GLubyte b=blue;
    GLubyte a=alpha;
    glColor4ub(r, g, b,a);
    if(camera_align)
        glRecti(x-camera_x, y+camera_y, width+x-camera_x, height+y+camera_y);
    else
        glRecti(x, y, width+x, height+y);
    glFlush();
}

void Painter::updateScreen()
{
    SDL_GL_SwapBuffers();
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
