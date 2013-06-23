#ifndef STAGE_H
#define STAGE_H

#include "TinyXml/tinyxml.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"
#include "Layer.h"

class Stage
{
    public:
    std::vector<Layer*> back,front;
    std::string music_path;
    RosalilaGraphics* painter;
    Sound* sonido;
    int size;
    int pos_piso;
    //efecto terremoto
    bool efecto_camara;
    bool moviendo_derecha;
    int movimiento;
    int borde_efecto;
    Stage(RosalilaGraphics* painter,Sound* sonido);
    void dibujarBack(bool time_stopped);
    void dibujarFront(bool time_stopped);
    void drawLayer(Layer*layer, bool time_stopped);
    void loadFromXML(std::string archivo);
    ~Stage();
};

#endif
