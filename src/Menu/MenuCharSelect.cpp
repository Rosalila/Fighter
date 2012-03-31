#include "Menu/MenuCharSelect.h"

MenuCharSelect::MenuCharSelect(Grafico*grafico,int x, int y, int width, int height,
                   int size_x,int size_y,
                   int size_cuadro_x,int size_cuadro_y,
                   int separacion_x,int separacion_y,
                   int max_locked_chars_pa,int max_locked_chars_pb,
                   vector<stringw>names)
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->grafico=grafico;

    this->size_x=size_x;
    this->size_y=size_y;
    this->size_cuadro_x=size_cuadro_x;
    this->size_cuadro_y=size_cuadro_y;

    this->separacion_x=separacion_x;
    this->separacion_y=separacion_y;

    this->max_locked_chars_pa=max_locked_chars_pa;
    this->max_locked_chars_pb=max_locked_chars_pb;

    for(int i=0;i<(int)names.size();i++)
    {
        portraits.push_back(grafico->getTexture(stringw("chars/")+names[i]+stringw("/portrait.png")));
    }
    this->names=names;

    select_p1_x=select_p1_y=0;
    select_p2_y=0;
    select_p2_x=size_x-1;

    selected_char_p1=grafico->getTexture("misc/selected_char_p1.png");
    selected_char_p2=grafico->getTexture("misc/selected_char_p2.png");
    locked_char_p1=grafico->getTexture("misc/locked_char_p1.png");
    locked_char_p2=grafico->getTexture("misc/locked_char_p2.png");
}

void MenuCharSelect::lockPA()
{
    int name_pos=select_p1_x+select_p1_y*size_x;
    if((int)locks_pa.size()<max_locked_chars_pa)
        if(name_pos<(int)names.size())
            locks_pa.push_back(LockedChar(select_p1_x,select_p1_y,names[name_pos]));
}

void MenuCharSelect::lockPB()
{
    int name_pos=select_p2_x+select_p2_y*size_x;
    if((int)locks_pb.size()<max_locked_chars_pb)
        if(name_pos<(int)names.size())
            locks_pb.push_back(LockedChar(select_p2_x,select_p2_y,names[name_pos]));
}

vector<stringw> MenuCharSelect::getLockedNamesPA()
{
    vector<stringw>res;
    for(int i=0;i<(int)locks_pa.size();i++)
        res.push_back(locks_pa[i].name);
    return res;
}

vector<stringw> MenuCharSelect::getLockedNamesPB()
{
    vector<stringw>res;
    for(int i=0;i<(int)locks_pb.size();i++)
        res.push_back(locks_pb[i].name);
    return res;
}

bool MenuCharSelect::listo()
{
    return (int)locks_pa.size()==max_locked_chars_pa && (int)locks_pb.size()<max_locked_chars_pb;
}

int MenuCharSelect::getTipo()
{
    return 7;
}

void MenuCharSelect::dibujar()
{

    int cont=0;
    for(int j=0;j<size_y;j++)
        for(int i=0;i<size_x;i++)
        {
            //dibujar portraits
            if(cont>=(int)portraits.size())
            {
                grafico->draw2DRectangle(irr::video::SColor(255,0,255,255),core::rect<s32>(x+i*(size_cuadro_x+separacion_x),y+j*(size_cuadro_y+separacion_y),
                                                                                           x+i*(size_cuadro_x+separacion_x)+size_cuadro_x,y+j*(size_cuadro_y+separacion_y)+size_cuadro_y));
            }else
            {
                irr::video::ITexture *imagen=portraits[cont];
                grafico->draw2DImage
                (   imagen,
                    irr::core::dimension2d<irr::f32> (size_cuadro_x,size_cuadro_y),
                    irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
                    irr::core::position2d<irr::f32>(x+i*(size_cuadro_x+separacion_x),y+j*(size_cuadro_y+separacion_y)),
                    irr::core::position2d<irr::f32>(0,0),
                    irr::f32(0), irr::core::vector2df (0,0),
                    true,
                    irr::video::SColor(255,255,255,255),
                    false,
                    false);
            }
            //dibjuar locks pa
            for(int l=0;l<(int)locks_pa.size();l++)
            {
                if(locks_pa[l].x==i && locks_pa[l].y==j)
                {
                    irr::video::ITexture *imagen=locked_char_p1;
                    grafico->draw2DImage
                    (   imagen,
                        irr::core::dimension2d<irr::f32> (size_cuadro_x,size_cuadro_y),
                        irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
                        irr::core::position2d<irr::f32>(x+locks_pa[l].x*(size_cuadro_x+separacion_x),y+locks_pa[l].y*(size_cuadro_y+separacion_y)),
                        irr::core::position2d<irr::f32>(0,0),
                        irr::f32(0), irr::core::vector2df (0,0),
                        true,
                        irr::video::SColor(255,255,255,255),
                        false,
                        false);
                }
            }
            //dibjujar cursor PA
            if(select_p1_x==i&&select_p1_y==j && (int)locks_pa.size()<max_locked_chars_pa)
            {
                irr::video::ITexture *imagen=selected_char_p1;
                grafico->draw2DImage
                (   imagen,
                    irr::core::dimension2d<irr::f32> (size_cuadro_x,size_cuadro_y),
                    irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
                    irr::core::position2d<irr::f32>(x+i*(size_cuadro_x+separacion_x),y+j*(size_cuadro_y+separacion_y)),
                    irr::core::position2d<irr::f32>(0,0),
                    irr::f32(0), irr::core::vector2df (0,0),
                    true,
                    irr::video::SColor(255,255,255,255),
                    false,
                    false);
            }
            //dibjujar cursor PB
            if(select_p2_x==i&&select_p2_y==j && (int)locks_pb.size()<max_locked_chars_pb)
            {
                irr::video::ITexture *imagen=selected_char_p2;
                grafico->draw2DImage
                (   imagen,
                    irr::core::dimension2d<irr::f32> (size_cuadro_x,size_cuadro_y),
                    irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
                    irr::core::position2d<irr::f32>(x+i*(size_cuadro_x+separacion_x),y+j*(size_cuadro_y+separacion_y)),
                    irr::core::position2d<irr::f32>(0,0),
                    irr::f32(0), irr::core::vector2df (0,0),
                    true,
                    irr::video::SColor(255,255,255,255),
                    false,
                    false);
            }
            cont++;
        }
}

void MenuCharSelect::dibujar(int alineacion_x,int alineacion_y)
{
    grafico->draw2DRectangle(irr::video::SColor(255,0,255,255),core::rect<s32>(0,0,50,50));
//    grafico->draw2DImage
//    (   imagen,
//        irr::core::dimension2d<irr::f32> (width,height),
//        irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
//        irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
//        irr::core::position2d<irr::f32>(0,0),
//        irr::f32(0), irr::core::vector2df (0,0),
//        true,
//        irr::video::SColor(255,255,255,255),
//        false,
//        false);
}
