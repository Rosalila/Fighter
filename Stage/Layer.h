#ifndef LAYER_H
#define LAYER_H

#include "TinyXml/tinyxml.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"

class Layer
{
public:
    std::vector <Image*> textures;
    std::vector <int> textures_size_x;
    std::vector <int> textures_size_y;

    //External logic
    int frame_duration,depth_effect_x,depth_effect_y,alignment_x,alignment_y;
    int initial_x;
    int velocity_x;
    int max_x;
    int min_x;
    //Internal logic
    int current_frame,time_elapsed;

    Layer(vector<Image*> textures,vector <int> textures_size_x,vector <int> textures_size_y,int frame_duration,int depth_effect_x,int depth_effect_y,int alignment_x,int alignment_y,int velocity_x,int min_x,int max_x);
    ~Layer();
};

#endif
