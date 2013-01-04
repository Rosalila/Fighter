#include "Painter/Painter.h"

LTexture gLoadedTexture;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

bool initGL()
{
    //Set the viewport
    glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Enable texturing
    glEnable( GL_TEXTURE_2D );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    //Initialize DevIL
    ilInit();
    ilClearColour( 255, 255, 255, 000 );

    //Check for error
    ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
//        printf( "Error initializing DevIL! %s\n", iluErrorString( ilError ) );
        return false;
    }

    return true;
}

bool loadMedia()
{
    //Load texture
    if( !gLoadedTexture.loadTextureFromFile( "06_loading_a_texture/texture.png" ) )
    {
        printf( "Unable to load file texture!\n" );
        return false;
    }

    return true;
}

void update()
{

}

void render()
{
    //glClear( GL_COLOR_BUFFER_BIT );

    //Update screen
    glutSwapBuffers();
}

void runMainLoop( int val )
{
    //Frame logic
    update();
    render();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


Painter::Painter(int *argcp, char **argv)
{
    renderQuad = true;
    screen_width = 640;
    screen_height = 480;
    screen_bpp = 32;
    camera_x=camera_y=0;
    //Initialize FreeGLUT
    glutInit( argcp, argv );

    //Create OpenGL 2.1 context
    glutInitContextVersion( 2, 1 );

    //Create Double Buffered Window
    glutInitDisplayMode( GLUT_DOUBLE );
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    glutCreateWindow( "OpenGL" );

    //Do post window/context creation initialization
    if( !initGL() )
    {
        printf( "Unable to initialize graphics library!\n" );
        return;
    }

    //Load media
    if( !loadMedia() )
    {
        printf( "Unable to load media!\n" );
        return;
    }

    //Set rendering function
    glutDisplayFunc( render );

    //Set main loop
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

    //Start GLUT main loop
    //glutMainLoop();

    return;
}

Painter::~Painter()
{
    //Free the surface
//    SDL_FreeSurface( screen );

    //Quit SDL
    SDL_Quit();
}


LTexture* Painter::getTexture(std::string filename)
{
    //Load texture
    LTexture *gLoadedTexture=new LTexture();
    if( !gLoadedTexture->loadTextureFromFile( filename ) )
    {
        std::cout<<"Error: Unable to load file texture!"<<std::endl;std::cout.flush();
        return NULL;
    }

    return gLoadedTexture;
}

void Painter::draw2DImage	(
             LTexture* texture,
             int size_x,int size_y,
             int position_x,int position_y,
             int scale,
             bool flipHorizontally)
{
    texture->render( position_x, position_y );
}

void Painter::draw2DImageCameraAlign	(
             LTexture* texture,
             int size_x,int size_y,
             int position_x,int position_y,
             int scale,
             bool flipHorizontally)
{
    texture->render( position_x+camera_x, position_y+camera_y );
}

void Painter::updateScreen()
{
    render();
}
