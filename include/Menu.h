#include "../include/Stage.h"
#include "../include/Grafico.h"
#include "../include/irrKlang/irrKlang.h"
#include "../include/Personaje.h"
using namespace irrklang;


/*
class Elemento
{
    int x;
    int y;
    int height;
    int width;
    int getTipo()=0;
}

class Contenedor:Elemento
{
    string imagen_bg;
    vector<Elemento> elementos;
    int getTipo();
}

class Imagen:Elemento
{
    string imagen;
    int getTipo();
}

class Texto:Elemento
{

}

texto: elemento
{
  texto
  tipo de letra
  tamaño
  color
  tipoElem()
}

boton: elemento
{
  imagen BG
  texto
  lista de acciones//  funcion(elemento)  cambiarFondo(elemento)
  tipoElem()
}

listas: elemento
{
  lista de elementos
  imgaen flechaDer
  imagen flechaIzq
  actual
}

barras: elemento
{
  imagen fondo
  imagen barra
  valor maximo
  valor actual
}
*/

class Menu
{
    Stage* stage;
    Personaje *pa;
    Personaje *pb;
    //Engines
    Sonido* sonido;
    Grafico* grafico;
    Input* receiver;

public:
    Menu(Stage* stage,Personaje *pa,Personaje *pb,Sonido* sonido,Grafico* grafico,Input* receiver);
    void loopMenu();
    bool dibujarImagen(video::ITexture* imagen);
    bool dibujarMenu(video::ITexture* imagen,int opcion,int opcion_stage);
};
