#include "../include/AtributosPersonaje.h"

Barra::Barra(stringw valor_maximo,stringw valor_actual,stringw modificador_periodico,stringw periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagenes[])
{
    this->valor_maximo=valor_maximo;
    this->valor_actual=valor_actual;
    this->modificador_periodico=modificador_periodico;
    this->periodo=periodo;
    this->color=color;
    this->posicion=posicion;
}
Barra::Barra()
{

}

HitBox::HitBox (int p1x,int p1y,int p2x,int p2y)
{
    this->p1x=p1x;
    this->p1y=p1y;
    this->p2x=p2x;
    this->p2y=p2y;
}

Imagen::Imagen(video::ITexture* imagen,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->escala=1;
    this->dimension_x=(int)imagen->getSize().Width;
    this->dimension_y=(int)imagen->getOriginalSize().Height;
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}

Imagen::Imagen(video::ITexture* imagen,float escala,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->escala=escala;
    this->dimension_x=(int)imagen->getSize().Width;
    this->dimension_y=(int)imagen->getOriginalSize().Height;
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}

Imagen::Imagen()
{

}

ModificadorImagen::ModificadorImagen(stringw variable,Imagen modificador,bool aplicar_a_contrario)
{
    tipo="imagen";
    this->variable=variable;
    this->modificador_imagen=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}

ModificadorEntero::ModificadorEntero(stringw variable,int modificador,bool relativo,bool aplicar_a_contrario)
{
    tipo="entero";
    this->variable=variable;
    this->modificador_entero=modificador;
    this->relativo=relativo;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
ModificadorBarra::ModificadorBarra(stringw variable,Barra modificador,bool aplicar_a_contrario)
{
    tipo="barra";
    this->variable=variable;
    this->modificador_barra=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
ModificadorHitboxes::ModificadorHitboxes(stringw variable,vector <HitBox> modificador,bool aplicar_a_contrario)
{
    tipo="hitboxes";
    this->variable=variable;
    this->modificador_hitbox=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
ModificadorString::ModificadorString(stringw variable,stringw modificador,bool aplicar_a_contrario)
{
    tipo="string";
    this->variable=variable;
    this->modificador_string=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
ModificadorPorVariable::ModificadorPorVariable(stringw tipo,stringw variable,stringw variable_modificador,bool relativo,bool aplicar_a_contrario)
{
    this->tipo="variable";
    this->tipo_variable=tipo;
    this->variable=variable;
    this->modificador_string=variable_modificador;
    this->relativo=relativo;
    this->aplicar_a_contrario=aplicar_a_contrario;
}

Frame::Frame(int duracion)
{
    this->modificadores=vector<Modificador>();
    this->duracion=duracion;
}
void Frame::agregarModificador(Imagen modificador,stringw variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorImagen(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(int modificador,stringw variable,bool relativo,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorEntero(variable,modificador,relativo,aplicar_a_contrario));
}
void Frame::agregarModificador(Barra modificador,stringw variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorBarra(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(vector <HitBox> modificador,stringw variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorHitboxes(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(stringw modificador,stringw variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorString(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(stringw tipo,stringw variable_modificador,stringw variable,bool relativo,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorPorVariable(tipo,variable,variable_modificador,relativo,aplicar_a_contrario));
}

Movimiento::Movimiento(stringw nombre)
{
    frame_actual=0;
    tiempo_transcurrido=0;
    this->nombre=nombre;
}
Frame Movimiento::getFrameActual()
{
    return frames[frame_actual];
}
void Movimiento::agregarFrame(int duracion)
{
    frames.push_back(Frame(duracion));
}
