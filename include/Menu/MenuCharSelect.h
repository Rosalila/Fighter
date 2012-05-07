#ifndef MENUCHARSELECT_H
#define MENUCHARSELECT_H

#include "Menu/Elemento.h"

class LockedChar
{
public:
    int x,y;
    stringw name;
    int num_paleta;
    irr::video::ITexture*preview;
    LockedChar(int x,int y,stringw name,int num_paleta,irr::video::ITexture*preview)
    {
        this->x=x;
        this->y=y;
        this->name=name;
        this->num_paleta=num_paleta;
        this->preview=preview;
    }
};

class MenuCharSelect:Elemento
{
private:
    int size_cuadro_x,size_cuadro_y;
    int separacion_x,separacion_y;
    int max_locked_chars_pa;
    int max_locked_chars_pb;
    int preview_pa_x,preview_pa_y;
    int preview_pb_x,preview_pb_y;
    vector<irr::video::ITexture*>portraits;
    vector<irr::video::ITexture*>previews;
    vector<stringw>names;
    vector<LockedChar>locks_pa;
    vector<LockedChar>locks_pb;
    irr::video::ITexture* selected_char_p1;
    irr::video::ITexture* selected_char_p2;
    irr::video::ITexture* locked_char_p1;
    irr::video::ITexture* locked_char_p2;
    irr::video::ITexture* no_portrait;
public:
    int select_p1_x,select_p1_y;
    int select_p2_x,select_p2_y;
    int size_x,size_y;
    MenuCharSelect(Grafico*grafico,int x, int y, int width, int height,
                   int size_x,int size_y,
                   int size_cuadro_x,int size_cuadro_y,
                   int separacion_x,int  separacion_y,
                   int max_locked_chars_pa,int max_locked_chars_pb,
                   int preview_pa_x,int preview_pa_y,
                   int preview_pb_x,int preview_pb_y,
                   vector<stringw>names);
    void lockPA(int num_paleta);
    void lockPB(int num_paleta);
    vector<stringw> getLockedNamesPA();
    vector<stringw> getLockedNamesPB();
    vector<int> getLockedPalettesPA();
    vector<int> getLockedPalettesPB();
    vector<irr::video::ITexture*> getLockedPreviewsPA();
    vector<irr::video::ITexture*> getLockedPreviewsPB();
    bool listo();
    bool listoPA();
    bool listoPB();
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
};

#endif
