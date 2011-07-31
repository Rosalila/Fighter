#include "../include/Stage.h"

Stage::Stage(video::ITexture* imagen_fondo,video::ITexture* imagen_barra,Grafico* grafico)
{
    this->imagen_fondo=imagen_fondo;
    this->imagen_barra=imagen_barra;
    this->grafico=grafico;
}
void Stage::dibujar()
{
    //Fondo
    int dimension_x=1024,dimension_y=600;
    grafico->draw2DImage
    (   imagen_fondo,
        irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
        irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
        irr::core::position2d<irr::f32>(0,0),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (0,0),
        true,
        irr::video::SColor(255,255,255,255),
        false,
        false);
    //Barra
    grafico->draw2DImage
    (   imagen_barra,
        irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
        irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
        irr::core::position2d<irr::f32>(0,0),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (0,0),
        true,
        irr::video::SColor(255,255,255,255),
        false,
        false);
}
