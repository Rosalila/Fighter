#include "Layer.h"

Layer::Layer(vector<Image*> textures,vector <int> textures_size_x,vector <int> textures_size_y,int frame_duration,int depth_effect_x,int depth_effect_y,int alignment_x,int alignment_y,int velocity_x,int min_x,int max_x)
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
    this->velocity_x=velocity_x;
    this->initial_x=alignment_x;
    this->max_x=max_x;
    this->min_x=min_x;
}

Layer::~Layer()
{
    writeLogLine("Deleting layer.");
    for(;!textures.empty();)
    {
        Image*image=textures.back();
        textures.pop_back();
        delete image;
    }
}
