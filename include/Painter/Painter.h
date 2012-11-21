#ifndef GRAFICO_H
#define GRAFICO_H

#include <stdlib.h>	// for itoa() call
#include <irrlicht/irrlicht.h>
using namespace irr;
#include "Input/Input.h"


class Painter
{
    gui::IGUIFont* font;
    public:
    int camera_x,camera_y;
    video::IVideoDriver* driver;
    int ventana_x,ventana_y;
    IrrlichtDevice *device;
    scene::ISceneManager* smgr;
    ICameraSceneNode* camera;
    Painter(Receiver* receiver);
    bool isWindowActive();
    void beginScene();
    void endScene();
    bool run();
    irr::video::ITexture* getTexture(irr::core::stringw archivo);
    irr::video::ITexture* getTexture(irr::core::stringw archivo,video::SColor color_a_ignorar);
    void drawText(core::stringw texto,core::rect<s32> posicion,video::SColor color);
    void draw2DRectangle(irr::video::SColor color,core::rect<s32> posicion);
    void draw2DRectangleCameraAlign(irr::video::SColor color,core::rect<s32> posicion);
    void draw2DImage	(
	             irr::video::ITexture* texture,
				 irr::core::dimension2d<irr::f32> size,
				 irr::core::rect<irr::f32> sourceRect,
				 irr::core::position2d<irr::f32> position,
				 irr::core::position2d<irr::f32> rotationPoint,
				 irr::f32 rotation,
				 irr::core::vector2df scale,
				 bool useAlphaChannel,
				 irr::video::SColor color,
				 bool flipHorizontally,
				 bool flipVertically);
    void draw2DImageCameraAlign	(
	             irr::video::ITexture* texture,
				 irr::core::dimension2d<irr::f32> size,
				 irr::core::rect<irr::f32> sourceRect,
				 irr::core::position2d<irr::f32> position,
				 irr::core::position2d<irr::f32> rotationPoint,
				 irr::f32 rotation,
				 irr::core::vector2df scale,
				 bool useAlphaChannel,
				 irr::video::SColor color,
				 bool flipHorizontally,
				 bool flipVertically);
    void draw2DImageCameraAlignDepthEffect
                (
	             irr::video::ITexture* texture,
				 irr::core::dimension2d<irr::f32> size,
				 irr::core::rect<irr::f32> sourceRect,
				 irr::core::position2d<irr::f32> position,
				 irr::core::position2d<irr::f32> rotationPoint,
				 irr::f32 rotation , irr::core::vector2df scale,
				 bool useAlphaChannel,
				 irr::video::SColor color ,
				 bool flipHorizontally,
				 bool flipVertically,
				 int depth_effect_x,
				 int depth_effect_y 	);

//! Convert a texture to an image. Remember to drop the returned pointer
video::IImage* TextureImage(video::ITexture* texture);

//! Convert an image to a texture. Remember to drop the returned pointer
video::ITexture* ImageTexture(video::IImage* image, core::stringc name=core::stringc(""));
};

#endif
