#ifndef STAGE_H
#define STAGE_H

#include "Painter/Painter.h"
#include "Sonido/Sonido.h"

class Layer
{
public:
    vector <video::ITexture*> textures;
    vector <int> textures_size_x;
    vector <int> textures_size_y;

    //External logic
    int frame_duration,depth_effect_x,depth_effect_y,alignment_x,alignment_y;
    //Internal logic
    int current_frame,time_elapsed;
    Layer(vector<video::ITexture*> textures,vector <int> textures_size_x,vector <int> textures_size_y,int frame_duration,int depth_effect_x,int depth_effect_y,int alignment_x,int alignment_y)
    {
        this->textures=textures;
        this->textures_size_x=textures_size_x;
        this->textures_size_y=textures_size_y;
        this->frame_duration=frame_duration;
        this->depth_effect_x=depth_effect_x;
        this->depth_effect_y=depth_effect_y;
        this->current_frame=0;
        this->time_elapsed=0;
        this->alignment_x=alignment_x;
        this->alignment_y=alignment_y;
    }
};

class Stage
{
    public:
    vector<Layer> back,front;
    std::string music_path;
    Painter* painter;
    Sonido* sonido;
    int size;
    int pos_piso;
    //efecto terremoto
    bool efecto_camara;
    bool moviendo_derecha;
    int movimiento;
    int borde_efecto;
    Stage(Painter* painter,Sonido* sonido);
    void dibujarBack();
    void dibujarFront();
    void drawLayer(Layer*layer);
    void cargarDesdeXML(char* archivo);
    ~Stage();
};

#endif
