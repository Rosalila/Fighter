#include "../include/Grafico.h"

class Stage
{
    public:
    vector<video::ITexture*> back,front;
    Grafico* grafico;
    Stage(vector<video::ITexture*> back,vector<video::ITexture*> front,Grafico* grafico);
    Stage(){};
    void dibujarBack();
    void dibujarFront();
};
