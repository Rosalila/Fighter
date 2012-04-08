#include "Stage/Stage.h"

Stage::Stage(Grafico* grafico,Sonido* sonido)
{
    this->grafico=grafico;
    this->sonido=sonido;
}

void Stage::dibujarBackground()
{
    int dimension_x=background->imagen->getOriginalSize().Width;
    int dimension_y=background->imagen->getOriginalSize().Height;
    grafico->draw2DImage
    (   background->imagen,
        irr::core::dimension2d<irr::f32> (background->size_x,background->size_y),
        irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
        irr::core::position2d<irr::f32>(0,0),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (0,0),
        true,
        irr::video::SColor(255,255,255,255),
        false,
        false);
}

void Stage::dibujarBack(int pos)
{
    dibujarBackground();
    for(int i=0;i<(int)back.size();i++)
    {
        int dimension_x=back[i].imagen->getOriginalSize().Width;
        int dimension_y=back[i].imagen->getOriginalSize().Height;
        grafico->draw2DImageCameraAlign
        (   back[i].imagen,
            irr::core::dimension2d<irr::f32> (back[i].size_x,back[i].size_y),
            irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
            irr::core::position2d<irr::f32>(pos-back[i].size_x/2+grafico->ventana_x/2,grafico->ventana_y-back[i].size_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (0,0),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
}

void Stage::dibujarFront(int pos)
{
    //Barra
    for(int i=0;i<(int)front.size();i++)
    {
        int dimension_x=front[i].imagen->getOriginalSize().Width;
        int dimension_y=front[i].imagen->getOriginalSize().Height;
        grafico->draw2DImageCameraAlign
        (   front[i].imagen,
            irr::core::dimension2d<irr::f32> (front[i].size_x,front[i].size_y),
            irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
            irr::core::position2d<irr::f32>(pos-front[i].size_x/2+grafico->ventana_x/2,grafico->ventana_y-front[i].size_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (0,0),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
}

void Stage::cargarDesdeXML(char* path)
{
    char *archivo=new char[255];
    strcpy(archivo,"stages/");
    strcat(archivo,path);
    strcat(archivo,"/main.xml");
    TiXmlDocument doc_t( archivo );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    char *music=new char[255];
    strcpy(music,"stages/");
    strcat(music,path);
    strcat(music,"/music.ogg");
    sonido->agregarSonido(stringw("Stage.music"),music);

    TiXmlNode *nodo_ss=doc->FirstChild("StageSize");
    this->size=atoi(nodo_ss->ToElement()->Attribute("x"));

    TiXmlNode *nodo_floor=doc->FirstChild("Floor");
    this->pos_piso=atoi(nodo_floor->ToElement()->Attribute("position"));

    TiXmlNode *nodo_bg=doc->FirstChild("Background");
    char *bg=new char[255];
    strcpy(bg,"stages/");
    strcat(bg,path);
    strcat(bg,"/images/");
    strcat(bg,nodo_bg->ToElement()->Attribute("image"));
    int size_x=atoi(nodo_bg->ToElement()->Attribute("size_x"));
    int size_y=atoi(nodo_bg->ToElement()->Attribute("size_y"));
    background=new Layer(grafico->getTexture(bg),size_x,size_y);

    TiXmlNode *nodo_back=doc->FirstChild("Back");
    for(TiXmlNode* layer=nodo_back->FirstChild("layer");
            layer!=NULL;
            layer=layer->NextSibling("layer"))
    {
        char *image=new char[255];
        strcpy(image,"stages/");
        strcat(image,path);
        strcat(image,"/images/");
        strcat(image,layer->ToElement()->Attribute("image"));
        int size_x=atoi(layer->ToElement()->Attribute("size_x"));
        int size_y=atoi(layer->ToElement()->Attribute("size_y"));
        back.push_back(Layer(grafico->getTexture(image),size_x,size_y));
    }

    TiXmlNode *nodo_front=doc->FirstChild("Front");
    for(TiXmlNode* layer=nodo_front->FirstChild("layer");
            layer!=NULL;
            layer=layer->NextSibling("layer"))
    {
        char *image=new char[255];
        strcpy(image,"stages/");
        strcat(image,path);
        strcat(image,"/images/");
        strcat(image,layer->ToElement()->Attribute("image"));
        int size_x=atoi(layer->ToElement()->Attribute("size_x"));
        int size_y=atoi(layer->ToElement()->Attribute("size_y"));
        front.push_back(Layer(grafico->getTexture(image),size_x,size_y));
    }
}
