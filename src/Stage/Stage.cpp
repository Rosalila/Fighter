#include "Stage/Stage.h"

Stage::Stage(Painter* painter,Sonido* sonido)
{
    this->painter=painter;
    this->sonido=sonido;

    //efecto
    bool efecto_camara=true;
    bool moviendo_derecha=true;
    int movimiento=0;
    int borde_efecto=30;
}

void Stage::drawLayer(Layer* layer)
{
    //Animation speed
    if(layer->time_elapsed>layer->frame_duration)
    {
        layer->current_frame++;
        layer->time_elapsed=0;
    }

    //Loop animation
    layer->time_elapsed++;
    if(layer->current_frame>=layer->textures.size())
        layer->current_frame=0;

    //Get current image
    Image* texture=layer->textures[layer->current_frame];

    //Paint
    int size_x=layer->textures_size_x[layer->current_frame];
    int size_y=layer->textures_size_y[layer->current_frame];

    int dimension_x=texture->getWidth();
    int dimension_y=texture->getHeight();

    int pos_x=-size_x/2+painter->screen_width/2+layer->alignment_x;
    int pos_y=painter->screen_height-size_y-layer->alignment_y;

//    painter->draw2DImageCameraAlignDepthEffect//!!DEPTH EFFECT
//    (   texture,
//        size_x,size_y,
//        pos_x,pos_y,
//        0,
//        false,
//        false,
//        layer->depth_effect_x,
//        layer->depth_effect_y);
}

void Stage::dibujarBack()
{
    for(int i=0;i<back.size();i++)
    {
        Layer* layer=&back[i];
        drawLayer(layer);
    }
}

void Stage::dibujarFront()
{
    for(int i=0;i<front.size();i++)
    {
        Layer* layer=&front[i];
        drawLayer(layer);
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

    TiXmlNode *stage_file=doc->FirstChild("StageFile");

    //Load settings
    char *music=new char[255];
    strcpy(music,"stages/");
    strcat(music,path);
    strcat(music,"/music.ogg");
    music_path=(std::string)music;

    TiXmlNode *nodo_ss=stage_file->FirstChild("StageSize");
    this->size=atoi(nodo_ss->ToElement()->Attribute("x"));

    TiXmlNode *nodo_floor=stage_file->FirstChild("Floor");
    this->pos_piso=atoi(nodo_floor->ToElement()->Attribute("position"));

    //Load back layer
    for(TiXmlNode *nodo_back=stage_file->FirstChild("BackLayer");
            nodo_back!=NULL;
            nodo_back=nodo_back->NextSibling("BackLayer"))
    {
        int frame_duration=atoi(nodo_back->ToElement()->Attribute("frame_duration"));
        int depth_effect_x=atoi(nodo_back->ToElement()->Attribute("depth_effect_x"));
        int depth_effect_y=atoi(nodo_back->ToElement()->Attribute("depth_effect_y"));
        int alignment_x=atoi(nodo_back->ToElement()->Attribute("alignment_x"));
        int alignment_y=atoi(nodo_back->ToElement()->Attribute("alignment_y"));

        std::vector <Image*> textures;
        std::vector <int> textures_size_x;
        std::vector <int> textures_size_y;

        for(TiXmlNode* layer=nodo_back->FirstChild("frame");
                layer!=NULL;
                layer=layer->NextSibling("frame"))
        {
            char *image=new char[255];
            strcpy(image,"stages/");
            strcat(image,path);
            strcat(image,"/images/");
            strcat(image,layer->ToElement()->Attribute("image_path"));
            int size_x=atoi(layer->ToElement()->Attribute("size_x"));
            int size_y=atoi(layer->ToElement()->Attribute("size_y"));

            textures.push_back(painter->getTexture(image));
            textures_size_x.push_back(size_x);
            textures_size_y.push_back(size_y);
        }

        back.push_back(Layer(textures,textures_size_x,textures_size_y,frame_duration,depth_effect_x,depth_effect_y,alignment_x,alignment_y));
    }

    //Load front layer
    for(TiXmlNode *nodo_back=stage_file->FirstChild("FrontLayer");
            nodo_back!=NULL;
            nodo_back=nodo_back->NextSibling("FrontLayer"))
    {
        int frame_duration=atoi(nodo_back->ToElement()->Attribute("frame_duration"));
        int depth_effect_x=atoi(nodo_back->ToElement()->Attribute("depth_effect_x"));
        int depth_effect_y=atoi(nodo_back->ToElement()->Attribute("depth_effect_y"));
        int alignment_x=atoi(nodo_back->ToElement()->Attribute("alignment_x"));
        int alignment_y=atoi(nodo_back->ToElement()->Attribute("alignment_y"));

        std::vector <Image*> textures;
        std::vector <int> textures_size_x;
        std::vector <int> textures_size_y;

        for(TiXmlNode* layer=nodo_back->FirstChild("frame");
                layer!=NULL;
                layer=layer->NextSibling("frame"))
        {
            char *image=new char[255];
            strcpy(image,"stages/");
            strcat(image,path);
            strcat(image,"/images/");
            strcat(image,layer->ToElement()->Attribute("image_path"));
            int size_x=atoi(layer->ToElement()->Attribute("size_x"));
            int size_y=atoi(layer->ToElement()->Attribute("size_y"));

            textures.push_back(painter->getTexture(image));
            textures_size_x.push_back(size_x);
            textures_size_y.push_back(size_y);
        }

        front.push_back(Layer(textures,textures_size_x,textures_size_y,frame_duration,depth_effect_x,depth_effect_y,alignment_x,alignment_y));
    }
}

Stage::~Stage()
{
}
