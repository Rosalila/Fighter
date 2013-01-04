#include <string>
#include <GL/glu.h>
#include <IL/IL.h>

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool loadTextureFromFile( std::string path );
        bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height );
        void freeTexture();
        void render( GLfloat x, GLfloat y );
        GLuint getTextureID();
        GLuint width();
        GLuint height();

    private:
        //Texture name
        GLuint mTextureID;
        //Texture dimensions
        GLuint mTextureWidth;
        GLuint mTextureHeight;
};
