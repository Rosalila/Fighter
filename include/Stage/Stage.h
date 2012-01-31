#include "Grafico/Grafico.h"
#include "Sonido/Sonido.h"

class Layer
{
public:
    video::ITexture* imagen;
    int size_x,size_y;
    Layer(video::ITexture* imagen,int size_x,int size_y)
    {
        this->imagen=imagen;
        this->size_x=size_x;
        this->size_y=size_y;
    }
};

class Stage
{
    public:
    Layer* background;
    vector<Layer> back,front;
    Grafico* grafico;
    Sonido* sonido;
    int size;
    Stage(Grafico* grafico,Sonido* sonido);
    void dibujarBackground();
    void dibujarBack(int pos);
    void dibujarFront(int pos);
    void cargarDesdeXML(char* archivo);
};
