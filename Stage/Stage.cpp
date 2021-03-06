#include "Stage.h"

Stage::Stage(RosalilaGraphics* painter,Sound* sonido)
{
    this->painter=painter;
    this->sonido=sonido;
}

void Stage::drawLayer(Layer* layer,bool time_stopped)
{
    if(!time_stopped)
    {
        //Animation speed
        if(layer->time_elapsed>layer->frame_duration)
        {
            layer->current_frame++;
            layer->time_elapsed=0;
        }

        //Loop animation
        layer->time_elapsed++;
        if(layer->current_frame>=(int)layer->textures.size())
            layer->current_frame=0;

        //Logic
        layer->alignment_x+=layer->velocity_x;
        if(layer->alignment_x>layer->max_x)
            layer->alignment_x=layer->initial_x;
        if(layer->alignment_x<layer->min_x)
            layer->alignment_x=layer->initial_x;
    }

    //Get current image
    Image* texture=layer->textures[layer->current_frame];

    //Paint
    int size_x=layer->textures_size_x[layer->current_frame];
    int size_y=layer->textures_size_y[layer->current_frame];

    int pos_x=-size_x/2+painter->screen_width/2+layer->alignment_x;
    int pos_y=painter->screen_height-size_y-layer->alignment_y;

    painter->draw2DImage
    (   texture,
        size_x,size_y,
        pos_x,pos_y,
        1.0,
        0.0,
        false,
        layer->depth_effect_x,
        layer->depth_effect_y,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow());
}

void Stage::dibujarBack(bool time_stopped)
{
    for(int i=0;i<(int)back.size();i++)
    {
        Layer* layer=back[i];
        drawLayer(layer,time_stopped);
    }
}

void Stage::dibujarFront(bool time_stopped)
{
    for(int i=0;i<(int)front.size();i++)
    {
        Layer* layer=front[i];
        drawLayer(layer,time_stopped);
    }
}

void Stage::loadFromXML(std::string path)
{
    writeLogLine("Loading stage from XML.");

    string xml_path=assets_directory+"stages/"+path+"/main.xml";

    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode *stage_file=doc->FirstChild("StageFile");

    //Load settings
    music_path=assets_directory+"stages/"+path+"/music.ogg";

    TiXmlNode *nodo_ss=stage_file->FirstChild("StageSize");
    this->size=atoi(nodo_ss->ToElement()->Attribute("x"));

    TiXmlNode *nodo_floor=stage_file->FirstChild("Floor");
    this->pos_piso=atoi(nodo_floor->ToElement()->Attribute("position"));

    writeLogLine("Loading stage's BackLayers.");

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

        int velocity_x=0;
        if(nodo_back->ToElement()->Attribute("velocity_x")!=NULL)
            velocity_x=atoi(nodo_back->ToElement()->Attribute("velocity_x"));

        int min_x=-999999;
        if(nodo_back->ToElement()->Attribute("min_x")!=NULL)
            min_x=atoi(nodo_back->ToElement()->Attribute("min_x"));

        int max_x=999999;
        if(nodo_back->ToElement()->Attribute("max_x")!=NULL)
            max_x=atoi(nodo_back->ToElement()->Attribute("max_x"));

        std::vector <Image*> textures;
        std::vector <int> textures_size_x;
        std::vector <int> textures_size_y;

        for(TiXmlNode* layer=nodo_back->FirstChild("frame");
                layer!=NULL;
                layer=layer->NextSibling("frame"))
        {
            string image_path=assets_directory+"stages/"+path+"/images/"+layer->ToElement()->Attribute("image_path");

            Image* image=painter->getTexture(image_path);
            textures.push_back(image);

            int size_x=image->getWidth();
            if(layer->ToElement()->Attribute("size_x")!=NULL)
                size_x=atoi(layer->ToElement()->Attribute("size_x"));

            int size_y=image->getHeight();
            if(layer->ToElement()->Attribute("size_y")!=NULL)
                size_y=atoi(layer->ToElement()->Attribute("size_y"));

            textures_size_x.push_back(size_x);
            textures_size_y.push_back(size_y);
        }

        back.push_back(new Layer(textures,textures_size_x,textures_size_y,frame_duration,depth_effect_x,depth_effect_y,alignment_x,alignment_y,velocity_x,min_x,max_x));
    }

    writeLogLine("Loading stage's FrontLayers.");

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

        int velocity_x=0;
        if(nodo_back->ToElement()->Attribute("velocity_x")!=NULL)
            velocity_x=atoi(nodo_back->ToElement()->Attribute("velocity_x"));

        int min_x=-999999;
        if(nodo_back->ToElement()->Attribute("min_x")!=NULL)
            min_x=atoi(nodo_back->ToElement()->Attribute("min_x"));

        int max_x=999999;
        if(nodo_back->ToElement()->Attribute("max_x")!=NULL)
            max_x=atoi(nodo_back->ToElement()->Attribute("max_x"));

        std::vector <Image*> textures;
        std::vector <int> textures_size_x;
        std::vector <int> textures_size_y;

        for(TiXmlNode* layer=nodo_back->FirstChild("frame");
                layer!=NULL;
                layer=layer->NextSibling("frame"))
        {
            string image_path=assets_directory+"stages/"+path+"/images/"+layer->ToElement()->Attribute("image_path");

            Image* image=painter->getTexture(image_path);
            textures.push_back(image);

            int size_x=image->getWidth();
            if(layer->ToElement()->Attribute("size_x")!=NULL)
                size_x=atoi(layer->ToElement()->Attribute("size_x"));

            int size_y=image->getHeight();
            if(layer->ToElement()->Attribute("size_y")!=NULL)
                size_y=atoi(layer->ToElement()->Attribute("size_y"));

            textures_size_x.push_back(size_x);
            textures_size_y.push_back(size_y);
        }

        front.push_back(new Layer(textures,textures_size_x,textures_size_y,frame_duration,depth_effect_x,depth_effect_y,alignment_x,alignment_y,velocity_x,min_x,max_x));
    }
    writeLogLine("Stage loaded succesfully from XML.");
}

Stage::~Stage()
{
    writeLogLine("Deleting stage.");
    for(;!back.empty();)
    {
        Layer*layer=back.back();
        back.pop_back();
        delete layer;
    }
    for(;!front.empty();)
    {
        Layer*layer=front.back();
        front.pop_back();
        delete layer;
    }
}
