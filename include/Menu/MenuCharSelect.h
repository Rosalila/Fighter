#ifndef MENUCHARSELECT_H
#define MENUCHARSELECT_H

#include <vector>
#include "Menu/Elemento.h"

class LockedChar
{
public:
    int x,y;
    std::string name;
    int num_paleta;
    SDL_Surface*preview;
    LockedChar(int x,int y,std::string name,int num_paleta,SDL_Surface*preview)
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
    std::vector<SDL_Surface*>portraits;
    std::vector<SDL_Surface*>previews;
    std::vector<std::string>names;
    std::vector<LockedChar>locks_pa;
    std::vector<LockedChar>locks_pb;
    SDL_Surface* selected_char_p1;
    SDL_Surface* selected_char_p2;
    SDL_Surface* locked_char_p1;
    SDL_Surface* locked_char_p2;
    SDL_Surface* no_portrait;
public:
    int select_p1_x,select_p1_y;
    int select_p2_x,select_p2_y;
    int size_x,size_y;
    MenuCharSelect(Painter*painter,int x, int y, int width, int height,
                   int size_x,int size_y,
                   int size_cuadro_x,int size_cuadro_y,
                   int separacion_x,int  separacion_y,
                   int max_locked_chars_pa,int max_locked_chars_pb,
                   int preview_pa_x,int preview_pa_y,
                   int preview_pb_x,int preview_pb_y,
                   std::vector<std::string>names,
                   int select_p1_x,int select_p1_y,
                   int select_p2_x,int select_p2_y);
    void lockPA(int num_paleta);
    void lockPB(int num_paleta);
    std::vector<std::string> getLockedNamesPA();
    std::vector<std::string> getLockedNamesPB();
    std::vector<int> getLockedPalettesPA();
    std::vector<int> getLockedPalettesPB();
    std::vector<SDL_Surface*> getLockedPreviewsPA();
    std::vector<SDL_Surface*> getLockedPreviewsPB();
    bool listo();
    bool listoPA();
    bool listoPB();
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
    void clearLocks();
};

#endif
