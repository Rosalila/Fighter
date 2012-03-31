#ifndef MENUCHARSELECT_H
#define MENUCHARSELECT_H

#include "Menu/Elemento.h"

class LockedChar
{
public:
    int x,y;
    stringw name;
    LockedChar(int x,int y,stringw name)
    {
        this->x=x;
        this->y=y;
        this->name=name;
    }
};

class MenuCharSelect:Elemento
{
private:
    int size_cuadro_x,size_cuadro_y;
    int separacion_x,separacion_y;
    int max_locked_chars_pa;
    int max_locked_chars_pb;
    vector<irr::video::ITexture*>portraits;
    vector<stringw>names;
    vector<LockedChar>locks_pa;
    vector<LockedChar>locks_pb;
    irr::video::ITexture* selected_char_p1;
    irr::video::ITexture* selected_char_p2;
    irr::video::ITexture* locked_char_p1;
    irr::video::ITexture* locked_char_p2;
public:
    int select_p1_x,select_p1_y;
    int select_p2_x,select_p2_y;
    int size_x,size_y;
    MenuCharSelect(Grafico*grafico,int x, int y, int width, int height,
                   int size_x,int size_y,
                   int size_cuadro_x,int size_cuadro_y,
                   int separacion_x,int  separacion_y,
                   int max_locked_chars_pa,int max_locked_chars_pb,
                   vector<stringw>names);
    void lockPA();
    void lockPB();
    vector<stringw> getLockedNamesPA();
    vector<stringw> getLockedNamesPB();
    bool listo();
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
};

#endif
