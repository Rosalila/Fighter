#include "Stage/Stage.h"

Stage::Stage(vector<video::ITexture*> back,vector<video::ITexture*> front,Grafico* grafico)
{
    this->back=back;
    this->front=front;
    this->grafico=grafico;
}
void Stage::dibujarBack()
{
    //Fondo
    for(int i=0;i<(int)back.size();i++)
    {
        int dimension_x=back[i]->getOriginalSize().Width;
        int dimension_y=back[i]->getOriginalSize().Height;
        grafico->draw2DImage
        (   back[i],
            irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
            irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1.30,1.40),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
}

void Stage::dibujarFront()
{
    //Barra
    for(int i=0;i<(int)front.size();i++)
    {
        int dimension_x=front[i]->getOriginalSize().Width;
        int dimension_y=front[i]->getOriginalSize().Height;
        grafico->draw2DImage
        (   front[i],
            irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
            irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
            irr::core::position2d<irr::f32>(grafico->ventana_x/2-dimension_x/2,0),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (0,0),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
}

void Stage::cargarDesdeXML(Grafico* grafico,char* archivo)
{
    this->grafico=grafico;

    TiXmlDocument doc_t( archivo );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode *nodo_back=doc->FirstChild("Back");
    for(TiXmlNode* layer=nodo_back->FirstChild("layer");
            layer!=NULL;
            layer=layer->NextSibling("layer"))
    {
        back.push_back(grafico->getTexture(layer->ToElement()->Attribute("imagen")));
    }

    TiXmlNode *nodo_front=doc->FirstChild("Front");
    for(TiXmlNode* layer=nodo_front->FirstChild("layer");
            layer!=NULL;
            layer=layer->NextSibling("layer"))
    {
        front.push_back(grafico->getTexture(layer->ToElement()->Attribute("imagen")));
    }
}
