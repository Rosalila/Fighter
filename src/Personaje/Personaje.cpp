#include "Personaje/Personaje.h"

Personaje::Personaje(Grafico* grafico,Sonido* sonido,int numero)
{
    rango=10;
    this->grafico=grafico;
    this->sonido=sonido;
    this->numero=numero;
    this->combo=0;
}
//DIBUJAR
void Personaje::dibujar()
{
    bool shadow=getString("effect.shadow")==stringw("on");
    bool violet=getString("effect.violet")==stringw("on");
    bool red=getString("effect.red")==stringw("on");
    bool green=getString("effect.green")==stringw("on");
    bool blue=getString("effect.blue")==stringw("on");
    if(sombra.size()>20)
    {
        sombra.erase (sombra.begin());
        sombra_x.erase (sombra_x.begin());
        sombra_y.erase (sombra_y.begin());
        flip_sombra.erase (flip_sombra.begin());
    }
    if(shadow)
    {
        for(int i=1;i<(int)sombra.size();i++)
        {
            if(i%8!=0)
                continue;
            if(sombra[i].imagen==NULL)
                continue;
            int dimension_x=sombra[i].dimension_x;
            int dimension_y=sombra[i].dimension_y;
            int alineacion_x=sombra[i].alineacion_x;
            int alineacion_y=sombra[i].alineacion_y;
            if(flip_sombra[i])
                alineacion_x=-alineacion_x;
        //    u32 t=grafico->device->getTimer()->getTime();
        //    int t2=t%255;
            grafico->draw2DImage
            (   sombra[i].imagen,
                irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
                irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
                irr::core::position2d<irr::f32>(sombra_x[i]-(dimension_x*sombra[i].escala/2)+alineacion_x,sombra_y[i]-(dimension_y*sombra[i].escala/2)-alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (sombra[i].escala,sombra[i].escala),
                true,
                irr::video::SColor(255,0,0,255),
                flip_sombra[i],
                false);
        }
    }

    if(getImagen("current_image").imagen==NULL)
        return;
    int dimension_x=getImagen("current_image").dimension_x;
    int dimension_y=getImagen("current_image").dimension_y;
    int alineacion_x=getImagen("current_image").alineacion_x;
    int alineacion_y=getImagen("current_image").alineacion_y;
    u32 t=grafico->device->getTimer()->getTime();
    int tr=255,tg=255,tb=255;

    if(getString("orientation")=="i")
        alineacion_x=-alineacion_x;

    if(violet)
    {
        tg=t%255;
    }
    if(red)
    {
        tg=t%255;
        tb=t%255;
    }
    if(green)
    {
        tr=t%255;
        tb=t%255;
    }
    if(blue)
    {
        tr=t%255;
        tg=t%255;
    }





    video::ITexture* texture=getImagen("current_image").imagen;
    // set color for texture
    SColor base(255,238,167,34);
    int modificacion_r=10;
    int modificacion_g=-60;
    int modificacion_b=100;

    int r_min=base.getRed()-rango;
    int r_max=base.getRed()+rango;
    int g_min=base.getGreen()-rango;
    int g_max=base.getGreen()+rango;
    int b_min=base.getBlue()-rango;
    int b_max=base.getBlue()+rango;

    if(r_min<0)r_min=0;
    if(r_max>255)r_max=255;
    if(g_min<0)g_min=0;
    if(g_max>255)g_max=255;
    if(b_min<0)b_min=0;
    if(b_max>255)b_max=255;

    if(this->numero==1)
    {
        // update texture with color
        s32* p = (s32*)texture->lock();
        for(s32 i=0; i<texture->getSize().Width*texture->getSize().Height; i++)
        {

            //verficacion
            SColor actual(p[i]);

           if(actual.getRed()>=r_min && actual.getRed()<=r_max
              && actual.getGreen()>=g_min && actual.getGreen()<=g_max
              && actual.getBlue()>=b_min && actual.getBlue()<=b_max
              )
           {
               int nuevo_r=actual.getRed()+modificacion_r;
               int nuevo_g=actual.getGreen()+modificacion_g;
               int nuevo_b=actual.getBlue()+modificacion_b;
               if(nuevo_r<0)nuevo_r=0;
               if(nuevo_g<0)nuevo_g=0;
               if(nuevo_b<0)nuevo_b=0;
               if(nuevo_r>255)nuevo_r=255;
               if(nuevo_g>255)nuevo_g=255;
               if(nuevo_b>255)nuevo_b=255;
               actual.setRed(nuevo_r);
               actual.setGreen(nuevo_g);
               actual.setBlue(nuevo_b);

               p[i]=actual.color;
           }
        }
        texture->unlock();
    }

    grafico->draw2DImage
    (   getImagen("current_image").imagen,
        irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
        irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
        irr::core::position2d<irr::f32>(getEntero("posicion_x")-(dimension_x*getImagen("current_image").escala/2)+alineacion_x,getEntero("posicion_y")-(dimension_y*getImagen("current_image").escala/2)-alineacion_y),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (getImagen("current_image").escala,getImagen("current_image").escala),
        true,
        irr::video::SColor(255,tr,tg,tb),
        getString("orientation")=="i",
        false);

    if(this->numero==1)
    {
        // update texture with color
        s32* p = (s32*)texture->lock();
        for(s32 i=0; i<texture->getSize().Width*texture->getSize().Height; i++)
        {
            //verficacion
            SColor actual(p[i]);

           if(actual.getRed()>=r_min+modificacion_r && actual.getRed()<=r_max+modificacion_r
              && actual.getGreen()>=g_min+modificacion_g && actual.getGreen()<=g_max+modificacion_g
              && actual.getBlue()>=b_min+modificacion_b && actual.getBlue()<=b_max+modificacion_b
              )
           {
               int nuevo_r=actual.getRed()-modificacion_r;
               int nuevo_g=actual.getGreen()-modificacion_g;
               int nuevo_b=actual.getBlue()-modificacion_b;
               if(nuevo_r<0)nuevo_r=0;
               if(nuevo_g<0)nuevo_g=0;
               if(nuevo_b<0)nuevo_b=0;
               if(nuevo_r>255)nuevo_r=255;
               if(nuevo_g>255)nuevo_g=255;
               if(nuevo_b>255)nuevo_b=255;
               actual.setRed(nuevo_r);
               actual.setGreen(nuevo_g);
               actual.setBlue(nuevo_b);

               p[i]=actual.color;
           }
        }
        texture->unlock();
    }

    sombra.push_back(getImagen("current_image"));
    sombra_x.push_back(getEntero("posicion_x"));
    sombra_y.push_back(getEntero("posicion_y"));
    flip_sombra.push_back(getString("orientation")=="i");
}
void Personaje::dibujarHitBoxes(stringw variable,stringw path,bool izquierda,int x,int y)
{
    vector <HitBox> hitbox=getHitBoxes(variable);
    if(getString("orientation")=="i")
    for(int i=0;i<(int)hitbox.size();i++)
    {
        int a=hitbox[i].p1x;
        int b=hitbox[i].p2x;
        hitbox[i].p1x=-b;
        hitbox[i].p2x=-a;
    }
    for(int i=0;i<(int)hitbox.size();i++)
    {
        if(variable=="blue")
            grafico->draw2DRectangle(irr::video::SColor(100,0,0,100),core::rect<s32>(x+hitbox[i].p1x,y+hitbox[i].p1y,x+hitbox[i].p2x,y+hitbox[i].p2y));
        else
            grafico->draw2DRectangle(irr::video::SColor(100,100,0,0),core::rect<s32>(x+hitbox[i].p1x,y+hitbox[i].p1y,x+hitbox[i].p2x,y+hitbox[i].p2y));
    }
}

void Personaje::dibujarBarra(Barra barra)
{
    position2d<s32>punto1= barra.posicion.UpperLeftCorner;
    position2d<s32>punto2= barra.posicion.LowerRightCorner;
    float longitud_total=(float)punto2.X-(float)punto1.X;
    float longitud_actual=((float)longitud_total/getEntero(barra.valor_maximo))*(float)getEntero(barra.valor_actual);
    float altura=(float)punto2.Y-(float)punto1.Y;

    float p1x,p1y,p2x,p2y;
    bool player2=false;
    if(numero==1)//player 1
    {
        p1x=punto1.X;
        p1y=punto1.Y;
        p2x=punto1.X+longitud_actual;
        p2y=punto2.Y;
    }else//flip if player 2
    {
        float temp_x2=grafico->ventana_x-punto1.X;
        float temp_x1=grafico->ventana_x-punto1.X-longitud_actual;

        p1x=temp_x1;
        p1y=punto1.Y;
        p2x=temp_x2;
        p2y=punto2.Y;

        player2=true;
    }
    if(barra.imagen==NULL)
        grafico->draw2DRectangle(barra.color,core::rect<s32>(p1x,p1y,p2x,p2y));
    else
        grafico->draw2DImage
        (   barra.imagen,
            irr::core::dimension2d<irr::f32> (longitud_actual,altura),
            irr::core::rect<irr::f32>(0,0,barra.imagen->getOriginalSize().Width*((float)getEntero(barra.valor_actual)/(float)getEntero(barra.valor_maximo)),barra.imagen->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(p1x,p1y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            player2,
            false);
}

void Personaje::dibujarBarraPequena(Barra barra,int cambio_x,int cambio_y)
{
    position2d<s32>punto1= barra.posicion.UpperLeftCorner;
    position2d<s32>punto2= barra.posicion.LowerRightCorner;
    float longitud_total=(float)punto2.X-(float)punto1.X;
    float longitud_actual=((float)longitud_total/getEntero(barra.valor_maximo))*(float)getEntero(barra.valor_actual);
    float altura=(float)punto2.Y-(float)punto1.Y;

    float p1x,p1y,p2x,p2y;
    bool player2=false;
    if(numero==1)//player 1
    {
        p1x=punto1.X;
        p1y=punto1.Y;
        p2x=punto1.X+longitud_actual;
        p2y=punto2.Y;

        p1x+=cambio_x;
        p2x+=cambio_x;
        p1y+=cambio_y;
        p2y+=cambio_y;
        p2x-=(p2x-p1x)/2;
        p2y-=(p2y-p1y)/2;
    }else//flip if player 2
    {
        float temp_x2=grafico->ventana_x-punto1.X;
        float temp_x1=grafico->ventana_x-punto1.X-longitud_actual;

        p1x=temp_x1;
        p1y=punto1.Y;
        p2x=temp_x2;
        p2y=punto2.Y;

        p1x-=cambio_x;
        p2x-=cambio_x;
        p1y+=cambio_y;
        p2y+=cambio_y;
        p1x-=(p1x-p2x)/2;
        p2y-=(p2y-p1y)/2;

        player2=true;
    }
    if(barra.imagen==NULL)
        grafico->draw2DRectangle(barra.color,core::rect<s32>(p1x,p1y,p2x,p2y));
    else
        grafico->draw2DImage
        (   barra.imagen,
            irr::core::dimension2d<irr::f32> (longitud_actual,altura),
            irr::core::rect<irr::f32>(0,0,barra.imagen->getOriginalSize().Width*((float)getEntero(barra.valor_actual)/(float)getEntero(barra.valor_maximo)),barra.imagen->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(p1x,p1y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            player2,
            false);
}

void Personaje::dibujarBarras()
{
    for(int i=0;i<(int)barras.size();i++)
    {
        dibujarBarra(barras[i]);
    }
}

void Personaje::dibujarProyectiles()
{
    for(int i=0;i<(int)proyectiles_actuales.size();i++)
    {
        if(getString(proyectiles_actuales[i]->estado)!="on")
            continue;
        Imagen imagen=getImagen(proyectiles_actuales[i]->imagen);
        grafico->draw2DImage
        (   imagen.imagen,
            irr::core::dimension2d<irr::f32> (imagen.imagen->getSize().Width,imagen.imagen->getSize().Height),
            irr::core::rect<irr::f32>(0,0,imagen.imagen->getSize().Width,imagen.imagen->getSize().Height),
            irr::core::position2d<irr::f32>(getEntero(proyectiles_actuales[i]->posicion_x)-(imagen.imagen->getSize().Width*imagen.escala/2)+imagen.alineacion_x,getEntero(proyectiles_actuales[i]->posicion_y)-(imagen.imagen->getSize().Height*imagen.escala/2)+imagen.alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (imagen.escala,imagen.escala),
            true,
            irr::video::SColor(255,255,255,255),
            getString(proyectiles_actuales[i]->orientacion)=="i",
            false);
        //dibujarHitBoxes("hadouken hitboxes","resources/red.png",getString("hadouken orientacion")=="i",getEntero("hadouken posicion x"),getEntero("hadouken posicion y"));
    }
}
//GETS shortcuts
Movimiento* Personaje::getMovimientoActual()
{
    return movimientos[getString("current_move")];
}
Frame Personaje::getFrameActual()
{
    return getMovimientoActual()->getFrameActual();
}
//GETS variables
int Personaje::getEntero(stringw variable)
{
    return enteros[variable];
}
Barra Personaje::getBarra(stringw variable)
{
    for(int i=0;i<(int)barras.size();i++)
        if(barras[i].nombre==variable)
            return barras[i];
    return Barra("error","","","","",video::SColor(0,0,0,0),core::rect<s32> (0,0,0,0),NULL);
}
vector<HitBox> Personaje::getHitBoxes(stringw variable)
{
    return hitboxes[variable];
}
Imagen Personaje::getImagen(stringw variable)
{
    return imagenes[variable];
}
stringw Personaje::getString(stringw variable)
{
    return strings[variable];
}
//SETS variables
void Personaje::setImagen(stringw variable,Imagen valor)
{
    imagenes[variable]=valor;
}
void Personaje::setEntero(stringw variable,int valor)
{
    enteros[variable]=valor;
}
void Personaje::agregarBarra(Barra valor)
{
    barras.push_back(valor);
}
void Personaje::setHitBoxes(stringw variable,vector<HitBox> valor)
{
    hitboxes[variable]=valor;
}
void Personaje::setString(stringw variable,stringw valor)
{
    strings[variable]=valor;
}

//Agregares
void Personaje::agregarInput(vector<stringw> input,stringw movimiento)
{
    inputs.push_back(InputMovimiento(input,movimiento));
}

void Personaje::agregarInput(stringw input,stringw movimiento)
{
    vector<stringw> lista_input;
    lista_input.push_back(input);
    inputs.push_back(InputMovimiento(lista_input,movimiento));
}

void Personaje::agregarCondicion(stringw movimiento,int frame,vector<Condicion*> condicion)
{
    ((Movimiento*)movimientos[movimiento])->agregarCondicion(condicion,frame);
}
//void Personaje::agregarCondicion(stringw movimiento,int frame,int posicion,Condicion condicion)
//{
//    ((Movimiento*)movimientos[movimiento])->agregarCondicion(posicion,condicion,frame);
//}
void Personaje::agregarMovimiento(stringw movimiento)
{
    movimientos[movimiento]=new Movimiento(movimiento);
}
void Personaje::agregarProyectil(Proyectil* proyectil)
{
    proyectiles_actuales.push_back(proyectil);
}
void Personaje::agregarFrame(stringw movimiento, int duracion)
{
    ((Movimiento*)movimientos[movimiento])->agregarFrame(duracion);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw variable,Imagen modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,relativo,aplicar_a_contrario,flipeable);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw variable,Barra modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw variable,vector <HitBox> modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw variable,stringw modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw tipo,stringw variable,stringw variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(tipo,variable_modificador,variable,relativo,aplicar_a_contrario,flipeable);
}

//Aplicares
void Personaje::aplicarModificador(ModificadorImagen* mi)
{
    if(mi->aplicar_a_contrario)
        personaje_contrario->setImagen(mi->variable,mi->modificador_imagen);
    else
        setImagen(mi->variable,mi->modificador_imagen);
}


void Personaje::aplicarModificador(ModificadorEntero* me,bool flip)
{
    if(me->relativo)
    {
        if(me->aplicar_a_contrario)
        {
            int temp_entero=personaje_contrario->getEntero(me->variable)+me->modificador_entero;
            if(me->flipeable && flip)
                temp_entero=personaje_contrario->getEntero(me->variable)-me->modificador_entero;
            personaje_contrario->setEntero(me->variable,temp_entero);
        }
        else
        {
            int temp_entero=getEntero(me->variable)+me->modificador_entero;
            if(me->flipeable && flip)
                temp_entero=getEntero(me->variable)-me->modificador_entero;
            setEntero(me->variable,temp_entero);
        }
    }
    else
    {
        if(me->aplicar_a_contrario)
        {
            int temp_entero=me->modificador_entero;
            if(me->flipeable && flip)
                temp_entero=-temp_entero;
            personaje_contrario->setEntero(me->variable,temp_entero);
        }
        else
        {
            int temp_entero=me->modificador_entero;
            if(me->flipeable && flip)
                temp_entero=-temp_entero;
            setEntero(me->variable,temp_entero);
        }
    }
}

void Personaje::aplicarModificador(ModificadorString* ms)
{
    if(ms->aplicar_a_contrario)
        personaje_contrario->setString(ms->variable,ms->modificador_string);//limpio
    else
        setString(ms->variable,ms->modificador_string);
}

void Personaje::flipHitBoxes()
{
    vector<HitBox> hb=getHitBoxes("blue");
    for(int i=0;i<(int)hb.size();i++)
    {
        int a=hb[i].p1x;
        int b=hb[i].p2x;
        hb[i].p1x=-b;
        hb[i].p2x=-a;
    }
    setHitBoxes("blue",hb);

    hb=getHitBoxes("red");
    for(int i=0;i<(int)hb.size();i++)
    {
        int a=hb[i].p1x;
        int b=hb[i].p2x;
        hb[i].p1x=-b;
        hb[i].p2x=-a;
    }
    setHitBoxes("red",hb);
}

void Personaje::aplicarModificador(ModificadorHitboxes* mh)
{
    if(mh->aplicar_a_contrario)
        personaje_contrario->setHitBoxes(mh->variable,mh->modificador_hitbox);
    else
        setHitBoxes(mh->variable,mh->modificador_hitbox);
}

void Personaje::aplicarModificador(ModificadorPorVariable* mv)
{
    if(mv->tipo_variable=="entero")
    {
        if(mv->relativo)
        {
            if(mv->aplicar_a_contrario)
            {
                int temp_entero=personaje_contrario->getEntero(mv->variable)+personaje_contrario->getEntero(mv->modificador_string);
                if(mv->flipeable)
                    temp_entero=personaje_contrario->getEntero(mv->variable)-personaje_contrario->getEntero(mv->modificador_string);
                personaje_contrario->setEntero(mv->variable,temp_entero);
            }
            else
            {
                int temp_entero=getEntero(mv->variable)+getEntero(mv->modificador_string);
                if(mv->flipeable)
                    temp_entero=getEntero(mv->variable)-getEntero(mv->modificador_string);
                setEntero(mv->variable,temp_entero);
            }
        }else
        {
            if(mv->aplicar_a_contrario)
            {
                int temp_entero=personaje_contrario->getEntero(mv->modificador_string);
                if(mv->flipeable)
                    temp_entero=-temp_entero;
                personaje_contrario->setEntero(mv->variable,temp_entero);
            }
            else
            {
                int temp_entero=getEntero(mv->modificador_string);
                if(mv->flipeable)
                    temp_entero=-temp_entero;
                setEntero(mv->variable,temp_entero);
            }
        }
    }
}

//Logica
stringw Personaje::mapInputToMovimiento()
{
    if(comparacion_hp>getEntero("hp.current_value") && input->inteligencia_artificial)
    {
        comparacion_hp=getEntero("hp.current_value");
        input->ia->quitarRecompensa();
    }
    if(comparacion_hp_contrario>personaje_contrario->getEntero("hp.current_value") && input->inteligencia_artificial)
    {
        comparacion_hp_contrario=personaje_contrario->getEntero("hp.current_value");
        input->ia->darRecompensa();
    }
    input->actualizarBuffer(&strings,&personaje_contrario->strings,&enteros,&personaje_contrario->enteros);

    for(int i=0;i<(int)inputs.size();i++)
        if(inputEstaEnBuffer(inputs[i].input,input->getBufferInputs()))
            if(cumpleCondiciones(inputs[i].movimiento))
                return inputs[i].movimiento;
    return "";
}
bool Personaje::inputEstaEnBuffer(vector<stringw> input,vector<stringw> buffer)
{
    if(input.size()==1)
        return input[0]==buffer[0];
    int j=(int)input.size()-1;
    for(int i=0;i<(int)buffer.size();i++)
    {
        if(input[j]==buffer[i])
            j--;
        if(j==-1)
            return true;
    }
    return false;
}
bool Personaje::cumpleCondiciones(stringw str_movimiento)
{
    Movimiento*movimiento=movimientos[str_movimiento];
    Frame *frame=&movimiento->frames[0];
    vector<vector<Condicion*> > condiciones=frame->condiciones;
    for(int i=0;i<(int)condiciones.size();i++)
    {
        vector<Condicion*> subcondiciones=condiciones[i];
        bool flag=true;
        for(int j=0;j<(int)subcondiciones.size();j++)
        {
            Condicion* c_temp=(Condicion*)subcondiciones[j];
            if(!cumpleCondicion(c_temp))
                flag=false;
        }
        if(flag)
            return true;
    }
    return false;
}
bool Personaje::cumpleCondiciones(vector<vector<Condicion*> >condiciones)
{
    for(int i=0;i<(int)condiciones.size();i++)
    {
        vector<Condicion*> subcondiciones=condiciones[i];
        bool flag=true;
        for(int j=0;j<(int)subcondiciones.size();j++)
        {
            Condicion* c_temp=(Condicion*)subcondiciones[j];
            if(!cumpleCondicion(c_temp))
                flag=false;
        }
        if(flag)
            return true;
    }
    return false;
}
bool Personaje::cumpleCondicion(Condicion* condicion)
{
    Personaje* personaje;
    if(!condicion->personaje_contrario)
        personaje=this;
    else
        personaje=personaje_contrario;
    if(condicion->tipo=="cadena")
    {
        return condicion->comparar(personaje->getString(condicion->variable));
    }else if(condicion->tipo=="entero")
    {
        return condicion->comparar(personaje->getEntero(condicion->variable));
    }
    return false;
}
void Personaje::aplicarModificadores(vector<Modificador> modificadores,bool flip)
{
    for(int i=0;i<(int)modificadores.size();i++)
    {
        Modificador modificador=modificadores[i];
        if(modificador.tipo=="imagen")
            aplicarModificador((ModificadorImagen*)&modificador);
        if(modificador.tipo=="entero")
            aplicarModificador((ModificadorEntero*)&modificador,flip);
        if(modificador.tipo=="string")
            aplicarModificador((ModificadorString*)&modificador);
        if(modificador.tipo=="hitboxes")
            aplicarModificador((ModificadorHitboxes*)&modificador);
        if(modificador.tipo=="variable")
            aplicarModificador((ModificadorPorVariable*)&modificador);
    }
}

void Personaje::cargarArchivo(char* archivo_xml)
{
}

void Personaje::cargarDesdeXML(int px,int py,Input* input,char* nombre)
{
    this->input=input;
    this->grafico=grafico;
    this->char_name=stringw(nombre);
    this->char_name_ptr=nombre;

    setString("effect.shadow","off");
    setString("effect.violet","off");
    setString("effect.red","off");
    setString("effect.green","off");
    setString("effect.blue","off");

    setEntero("Colision.x",0);
    setEntero("Colision.y",0);

    setEntero("posicion_x",px);
    setEntero("posicion_y",py);

    cargarMain();

    cargarVars();

    cargarInputs();

    cargarTriggers();

    cargarSprites();

    cargarHitboxes();

    cargarSfx();

    cargarAnimations();
}

void Personaje::logicaBarras()
{
    for(int i=0;i<(int)barras.size();i++)
    {
        if(barras[i].procesarTiempo(getEntero(barras[i].periodo)))
            setEntero(barras[i].valor_actual,getEntero(barras[i].valor_actual)+getEntero(barras[i].modificador_periodico));
        if(getEntero(barras[i].valor_actual)>getEntero(barras[i].valor_maximo))
            setEntero(barras[i].valor_actual,getEntero(barras[i].valor_maximo));
        if(getEntero(barras[i].valor_actual)<0)
            setEntero(barras[i].valor_actual,0);
    }
}

void Personaje::cargarMain()
{
    char* path=new char[255];
    strcpy(path,"chars/");
    strcat(path,char_name_ptr);
    strcat(path,"/main.xml\0");

    TiXmlDocument doc_t(path);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode* ignore_color_node=doc->FirstChild("IgnoreColor");
    irr::video::SColor ignore_color=NULL;
    if(ignore_color_node!=NULL)
    {
        ignore_color=irr::video::SColor(0,atoi(ignore_color_node->ToElement()->Attribute("red")),
                                        atoi(ignore_color_node->ToElement()->Attribute("green")),
                                        atoi(ignore_color_node->ToElement()->Attribute("blue")));
    }

    for(TiXmlNode* nodo=doc->FirstChild("Declarations");
            nodo!=NULL;
            nodo=nodo->NextSibling("Declarations"))
    {
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("Move")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("Move"))
            {
                stringw nombre(elemento_imagen->Attribute("name"));
                int frames=atoi(elemento_imagen->Attribute("frames"));
                int frame_duration=atoi(elemento_imagen->Attribute("frame_duration"));
                agregarMovimiento(nombre);
                for(int i=0;i<frames;i++)
                    agregarFrame(nombre,frame_duration);
            }
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("projectile")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("projectile"))
            {
                stringw nombre(elemento_imagen->Attribute("name"));
                int posicion_x(atoi(elemento_imagen->Attribute("position_x")));
                int posicion_y(atoi(elemento_imagen->Attribute("position_y")));
                int speed_x(atoi(elemento_imagen->Attribute("speed_x")));
                int speed_y(atoi(elemento_imagen->Attribute("speed_y")));
                int damage(atoi(elemento_imagen->Attribute("damage")));
                setEntero(nombre+".position_x",0);
                setEntero(nombre+".position_y",0);

                setString(nombre+".state","");
                setString(nombre+".orientacion","");

                //Sprites
                vector<Imagen>sprites;
                TiXmlNode *temp=elemento_imagen->FirstChild("Sprites");
                for(TiXmlElement *elemento_sprite=temp->FirstChild("Sprite")->ToElement();
                        elemento_sprite!=NULL;
                        elemento_sprite=elemento_sprite->NextSiblingElement("Sprite"))
                {
                    stringw path(elemento_sprite->Attribute("path"));
                    stringw dir("chars/");
                    path=dir+char_name+"/"+path;
                    int escala=atoi(elemento_sprite->Attribute("scale"));
                    int alineacion_x=atoi(elemento_sprite->Attribute("align_x"));
                    int alineacion_y=atoi(elemento_sprite->Attribute("align_y"));


                    irr::video::ITexture* texture;
                    if(ignore_color==NULL)
                        texture=grafico->getTexture(path);
                    else
                        texture=grafico->getTexture(path,ignore_color);
                    sprites.push_back(Imagen(texture,escala,alineacion_x,alineacion_y));
                }

                //Hitboxes
                temp=elemento_imagen->FirstChild("Hitboxes");
                vector<HitBox> hitboxes;
                if(!temp->NoChildren())
                for(TiXmlElement *elemento_hb=temp->FirstChild("Hitbox")->ToElement();
                        elemento_hb!=NULL;
                        elemento_hb=elemento_hb->NextSiblingElement("Hitbox"))
                {
                    int x1=atoi(elemento_hb->Attribute("x1"));
                    int y1=atoi(elemento_hb->Attribute("y1"));
                    int x2=atoi(elemento_hb->Attribute("x2"));
                    int y2=atoi(elemento_hb->Attribute("y2"));
                    hitboxes.push_back(HitBox(x1,y1,x2,y2));
                }
                setHitBoxes(nombre+".hitboxes",hitboxes);

                //Proyectil listo
                Proyectil* proyectil=new Proyectil(nombre,nombre+".position_x",nombre+".position_y",nombre+".sprite",nombre+".hitboxes",nombre+".state",nombre+".orientation",sprites,damage);

                //Frames
                stringw prefijo="Projectile.";
                int frames=atoi(elemento_imagen->Attribute("frames"));
                int frame_duration=atoi(elemento_imagen->Attribute("frame_duration"));

                for(int i=0;i<frames;i++)
                {
                    proyectil->agregarFrame(frame_duration);
                    proyectil->frames[i].agregarModificador(speed_x,nombre+".position_x",true,false,true);
                    proyectil->frames[i].agregarModificador(-speed_y,nombre+".position_y",true,false,false);
                }

                //Modificadores
                proyectil->frames[0].agregarModificador("off",nombre+".trigger",false);
                proyectil->frames[0].agregarModificador("entero","posicion_x",nombre+".position_x",false,false,false);
                proyectil->frames[0].agregarModificador(posicion_x,nombre+".position_x",true,false,true);
                proyectil->frames[0].agregarModificador("entero","posicion_y",nombre+".position_y",false,false,false);
                proyectil->frames[0].agregarModificador(-posicion_y,nombre+".position_y",true,false,false);

                //Triggers
                setString(nombre+".trigger","off");
                vector<Condicion*>cond_temp;
                cond_temp.push_back(new Condicion("hadouken.trigger","=","on",false));
                proyectil->agregarCondicion(cond_temp,0);

                //Listo
                agregarProyectil(proyectil);
            }

            for(TiXmlElement *elemento_imagen=nodo->FirstChild("sprite")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("sprite"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                stringw path(elemento_imagen->Attribute("path"));
                stringw dir("chars/");
                path=dir+char_name+"/"+path;
                int escala=atoi(elemento_imagen->Attribute("scale"));
                int alineacion_x=atoi(elemento_imagen->Attribute("align_x"));
                int alineacion_y=atoi(elemento_imagen->Attribute("align_y"));

                if(ignore_color==NULL)
                    setImagen(variable,Imagen(grafico->getTexture(path),escala,alineacion_x,alineacion_y));
                else
                    setImagen(variable,Imagen(grafico->getTexture(path,ignore_color),escala,alineacion_x,alineacion_y));
            }
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("string")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("string"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                stringw valor(elemento_imagen->Attribute("value"));
                setString(variable,valor);
            }
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("integer")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("integer"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                int valor=atoi(elemento_imagen->Attribute("value"));
                setEntero(variable,valor);
            }
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("hitboxes")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("hitboxes"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                vector<HitBox> hitbox;
                if(!elemento_imagen->NoChildren())
                for(TiXmlElement *elemento_hitbox=elemento_imagen->FirstChild("Hitbox")->ToElement();
                        elemento_hitbox!=NULL;
                        elemento_hitbox=elemento_hitbox->NextSiblingElement("Hitbox"))
                {
                    int x1=atoi(elemento_hitbox->Attribute("x1"));
                    int y1=atoi(elemento_hitbox->Attribute("y1"));
                    int x2=atoi(elemento_hitbox->Attribute("x2"));
                    int y2=atoi(elemento_hitbox->Attribute("y2"));
                    hitbox.push_back(HitBox(x1,y1,x2,y2));
                }
                setHitBoxes(variable,hitbox);
            }
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("bar")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("bar"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                int valor_maximo(atoi(elemento_imagen->Attribute("max_value")));
                int valor_actual(atoi(elemento_imagen->Attribute("current_value")));
                int modificador_periodico(atoi(elemento_imagen->Attribute("periodic_modifier")));
                int periodo(atoi(elemento_imagen->Attribute("period")));
                setEntero(variable+".max_value",valor_maximo);
                setEntero(variable+".current_value",valor_actual);
                setEntero(variable+".periodic_modifier",modificador_periodico);
                setEntero(variable+".period",periodo);

                int alpha=atoi(elemento_imagen->Attribute("alpha"));
                int r=atoi(elemento_imagen->Attribute("r"));
                int g=atoi(elemento_imagen->Attribute("g"));
                int b=atoi(elemento_imagen->Attribute("b"));
                int x1=atoi(elemento_imagen->Attribute("x1"));
                int y1=atoi(elemento_imagen->Attribute("y1"));
                int x2=atoi(elemento_imagen->Attribute("x2"));
                int y2=atoi(elemento_imagen->Attribute("y2"));
                stringw imagen(elemento_imagen->Attribute("image"));
                imagen=stringw("chars/")+char_name+stringw("/")+imagen;

                if(imagen!=NULL)
                    agregarBarra(Barra(variable,variable+".max_value",variable+".current_value",variable+".periodic_modifier",variable+".period",video::SColor(alpha,r,g,b),core::rect<s32>(x1,y1,x2,y2),grafico->getTexture(imagen)));
//                else
//                    agregarBarra(Barra(variable,variable+".max_value",variable+".current_value",variable+".periodic_modifier",variable+".period",video::SColor(alpha,r,g,b),core::rect<s32>(x1,y1,x2,y2),NULL));
            }
    }
}

void Personaje::cargarVars()
{
    char* path=new char[255];
    strcpy(path,"chars/");
    strcat(path,char_name_ptr);
    strcat(path,"/vars.xml\0");

    TiXmlDocument doc_t(path);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    for(TiXmlNode* nodo=doc->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        stringw nombre(elemento->Attribute("name"));
        //For each Input

        //For each Frame
        for(TiXmlNode* nodo_frame=nodo->FirstChild("Frame");
                nodo_frame!=NULL;
                nodo_frame=nodo_frame->NextSibling("Frame"))
        {
            TiXmlElement *elemento_frame=nodo_frame->ToElement();
            int frame=atoi(elemento_frame->Attribute("number"))-1;
            //For each Modificador
            if(!nodo_frame->NoChildren())
            {
                if(nodo_frame->FirstChild("Variable")!=NULL)
                {
                    for(TiXmlElement *e=nodo_frame->FirstChild("Variable")->ToElement();
                            e!=NULL;
                            e=e->NextSiblingElement("Variable"))
                    {
                        stringw str_tipo(e->Attribute("type"));
                        stringw str_variable(e->Attribute("variable"));
                        stringw str_valor(e->Attribute("value"));
                        stringw str_contrario(e->Attribute("to_opponent"));
                        stringw str_relativo(e->Attribute("relative"));
                        stringw str_flipeable(e->Attribute("flipable"));
                        bool contrario=(str_contrario=="yes");
                        bool relativo=(str_relativo=="yes");
                        bool flipeable=(str_flipeable=="yes");
                        agregarModificador(nombre,frame,str_tipo,str_variable,str_valor,relativo,contrario,flipeable);
                    }
                }

                if(nodo_frame->FirstChild("Integer")!=NULL)
                {
                    for(TiXmlElement *e=nodo_frame->FirstChild("Integer")->ToElement();
                            e!=NULL;
                            e=e->NextSiblingElement("Integer"))
                    {
                        stringw str_variable(e->Attribute("variable"));
                        stringw str_contrario(e->Attribute("to_opponent"));
                        stringw str_relativo(e->Attribute("relative"));
                        stringw str_flipeable(e->Attribute("flipable"));
                        int valor=atoi(e->Attribute("value"));
                        bool contrario=(str_contrario=="yes");
                        bool relativo=(str_relativo=="yes");
                        bool flipeable=(str_flipeable=="yes");
                        agregarModificador(nombre,frame,str_variable,valor,relativo,contrario,flipeable);
                    }
                }
                if(nodo_frame->FirstChild("String")!=NULL)
                {
                    for(TiXmlElement *e=nodo_frame->FirstChild("String")->ToElement();
                            e!=NULL;
                            e=e->NextSiblingElement("String"))
                    {
                        stringw str_variable(e->Attribute("variable"));
                        stringw str_contrario(e->Attribute("to_opponent"));
                        stringw str_valor(e->Attribute("value"));
                        bool contrario=(str_contrario=="yes");
                        agregarModificador(nombre,frame,str_variable,str_valor,contrario);
                    }
                }
            }
        }
        //For each Condiciones
    }
}

void Personaje::cargarInputs()
{
    char* path=new char[255];
    strcpy(path,"chars/");
    strcat(path,char_name_ptr);
    strcat(path,"/input.xml\0");

    TiXmlDocument doc_t(path);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;


    for(TiXmlNode* nodo_input=doc->FirstChild("Input");
            nodo_input!=NULL;
            nodo_input=nodo_input->NextSibling("Input"))
    {
        stringw move_name=(nodo_input->ToElement()->Attribute("move_name"));
        vector<stringw> lista_botones;
        for(TiXmlElement *elemento_boton=nodo_input->FirstChild("button")->ToElement();
                elemento_boton!=NULL;
                elemento_boton=elemento_boton->NextSiblingElement("button"))
        {
            stringw boton(elemento_boton->Attribute("value"));
            if(boton[0]=='*' && boton.size()>1)
            {
                boton[0]='1';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarInput(lista_botones,move_name);
                boton[0]='2';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarInput(lista_botones,move_name);
                boton[0]='3';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarInput(lista_botones,move_name);
                boton[0]='4';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarInput(lista_botones,move_name);
                boton[0]='6';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarInput(lista_botones,move_name);
                boton[0]='7';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarInput(lista_botones,move_name);
                boton[0]='8';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarInput(lista_botones,move_name);
                boton[0]='9';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarInput(lista_botones,move_name);
                boton[0]='5';
                stringw str_temp="";
                for(int i=1;i<boton.size();i--)
                    str_temp+=boton[i];
                lista_botones.clear();
                lista_botones.push_back(str_temp);
                agregarInput(lista_botones,move_name);
            }else
            {
                lista_botones.push_back(boton);
            }
        }
        agregarInput(lista_botones,move_name);
    }
}

void Personaje::cargarTriggers()
{
    char* path=new char[255];
    strcpy(path,"chars/");
    strcat(path,char_name_ptr);
    strcat(path,"/triggers.xml\0");

    TiXmlDocument doc_t(path);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    for(TiXmlNode* nodo=doc->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        stringw nombre(elemento->Attribute("name"));
        for(TiXmlNode* nodo_condiciones=nodo->FirstChild("Trigger");
                nodo_condiciones!=NULL;
                nodo_condiciones=nodo_condiciones->NextSibling("Trigger"))
        {
            vector<Condicion*> condiciones_temp;
            if(nodo_condiciones->FirstChild("condition")!=NULL)
            {
                for(TiXmlElement *elemento_condicion=nodo_condiciones->FirstChild("condition")->ToElement();
                        elemento_condicion!=NULL;
                        elemento_condicion=elemento_condicion->NextSiblingElement("condition"))
                {
                    stringw exp_i(elemento_condicion->Attribute("left_exp"));
                    stringw op(elemento_condicion->Attribute("relational_op"));
                    stringw exp_d(elemento_condicion->Attribute("right_exp"));
                    bool es_entero=false;
                    if(enteros.find(exp_i)!=0)
                        es_entero=true;
                    stringw str_contrario(elemento_condicion->Attribute("to_opponent"));
                    bool contrario=(str_contrario=="yes");
                    if(es_entero)
                    {
                        condiciones_temp.push_back(new Condicion(exp_i,op,atoi(elemento_condicion->Attribute("right_exp")),contrario));
                    }else
                    {
                        condiciones_temp.push_back(new Condicion(exp_i,op,exp_d,contrario));
                    }
                }
            }
            agregarCondicion(nombre,0,condiciones_temp);
        }
    }
}

void Personaje::cargarSprites()
{
    char* path=new char[255];
    strcpy(path,"chars/");
    strcat(path,char_name_ptr);
    strcat(path,"/sprites.xml\0");

    TiXmlDocument doc_t(path);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode* ignore_color_node=doc->FirstChild("IgnoreColor");
    irr::video::SColor ignore_color=NULL;
    if(ignore_color_node!=NULL)
    {
        ignore_color=irr::video::SColor(0,atoi(ignore_color_node->ToElement()->Attribute("red")),
                                        atoi(ignore_color_node->ToElement()->Attribute("green")),
                                        atoi(ignore_color_node->ToElement()->Attribute("blue")));
    }
    for(TiXmlNode* nodo=doc->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        stringw nombre(elemento->Attribute("name"));

        if(nodo->FirstChild("Sprite")!=NULL)
        {
            for(TiXmlElement *e=nodo->FirstChild("Sprite")->ToElement();
                    e!=NULL;
                    e=e->NextSiblingElement("Sprite"))
            {
                int frame=atoi(e->Attribute("frame_number"))-1;
                stringw str_variable(e->Attribute("variable"));
                stringw path(e->Attribute("path"));
                stringw dir("chars/");
                path=dir+char_name+"/"+path;
                int escala=atoi(e->Attribute("scale"));
                int alineacion_x=atoi(e->Attribute("align_x"));
                int alineacion_y=atoi(e->Attribute("align_y"));
                stringw str_contrario(e->Attribute("to_opponent"));
                bool contrario=(str_contrario=="si");

                if(ignore_color==NULL)
                    agregarModificador(nombre,frame,str_variable,Imagen(grafico->getTexture(irr::io::path(path)),escala,alineacion_x,alineacion_y),contrario);
                else
                    agregarModificador(nombre,frame,str_variable,Imagen(grafico->getTexture(irr::io::path(path),ignore_color),escala,alineacion_x,alineacion_y),contrario);
            }
        }
    }
}

void Personaje::cargarHitboxes()
{
    char* path=new char[255];
    strcpy(path,"chars/");
    strcat(path,char_name_ptr);
    strcat(path,"/hitboxes.xml\0");

    TiXmlDocument doc_t(path);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    for(TiXmlNode* nodo=doc->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        stringw nombre(elemento->Attribute("name"));
        for(TiXmlNode* nodo_frame=nodo->FirstChild("Frame");
                nodo_frame!=NULL;
                nodo_frame=nodo_frame->NextSibling("Frame"))
        {
            TiXmlElement *elemento_frame=nodo_frame->ToElement();
            int frame=atoi(elemento_frame->Attribute("number"))-1;
            if(nodo_frame->FirstChild("Hitboxes")!=NULL)
            {
                for(TiXmlElement *e=nodo_frame->FirstChild("Hitboxes")->ToElement();
                        e!=NULL;
                        e=e->NextSiblingElement("Hitboxes"))
                {
                    vector <HitBox> hitbox;
                    stringw str_variable(e->Attribute("variable"));
                    stringw str_contrario(e->Attribute("to_opponent"));
                    bool contrario=(str_contrario=="yes");
                    if(!e->NoChildren())
                    {
                        for(TiXmlElement *elemento_hitbox=e->FirstChild("Hitbox")->ToElement();
                                elemento_hitbox!=NULL;
                                elemento_hitbox=elemento_hitbox->NextSiblingElement("Hitbox"))
                        {
                            int x1=atoi(elemento_hitbox->Attribute("x1"));
                            int y1=atoi(elemento_hitbox->Attribute("y1"));
                            int x2=atoi(elemento_hitbox->Attribute("x2"));
                            int y2=atoi(elemento_hitbox->Attribute("y2"));
                            hitbox.push_back(HitBox(x1,y1,x2,y2));
                        }
                    }
                    agregarModificador(nombre,frame,str_variable,hitbox,contrario);
                }
            }
        }

    }
}

void Personaje::cargarSfx()
{
    char* path=new char[255];
    strcpy(path,"chars/");
    strcat(path,char_name_ptr);
    strcat(path,"/sfx.xml\0");

    TiXmlDocument doc_t(path);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    for(TiXmlNode* nodo_sonido=doc->FirstChild("Sound");
            nodo_sonido!=NULL;
            nodo_sonido=nodo_sonido->NextSibling("Sound"))
    {
        TiXmlElement* elemento_sonido=nodo_sonido->ToElement();
        stringw move(elemento_sonido->Attribute("move"));

        char*file=new char[255];
        strcpy(file,"chars/");

        //convert char_name to char*
        size_t count = 255;
        c8* c_name = (char*)malloc( 255 );
        wcstombs(c_name, char_name.c_str(), count);


        strcat(file,(char*)c_name);
        strcat(file,"/sfx/");
        strcat(file,elemento_sonido->Attribute("file"));
        sonido->agregarSonido(move,file);
    }

}

void Personaje::cargarAnimations()
{
    char* path_animations=new char[255];
    strcpy(path_animations,"chars/");
    strcat(path_animations,char_name_ptr);
    strcat(path_animations,"/animations.xml");
    TiXmlDocument doc_t(path_animations);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode *back=doc->FirstChild("Back");
    TiXmlNode *front=doc->FirstChild("Front");

    //Back
    for(TiXmlNode* nodo=back->FirstChild("Animation");
            nodo!=NULL;
            nodo=nodo->NextSibling("Animation"))
    {
        vector<Imagen>i_temp;
        for(TiXmlNode* nodo_frame=nodo->FirstChild("Sprite");
        nodo_frame!=NULL;
        nodo_frame=nodo_frame->NextSibling("Sprite"))
        {
            TiXmlElement *elem_frame=nodo_frame->ToElement();
            irr::video::ITexture *texture=grafico->getTexture(stringw(elem_frame->Attribute("path")));
            i_temp.push_back(Imagen(texture,
                                    (float)atoi(elem_frame->Attribute("scale")),
                                    atoi(elem_frame->Attribute("align_x")),
                                    atoi(elem_frame->Attribute("align_y"))));
        }
        TiXmlElement *elem_animation=nodo->ToElement();
        bool to_oponent=strcmp(elem_animation->Attribute("to_opponent"),"i")==0;
        stringw name=stringw(elem_animation->Attribute("name"));
        stringw pos_x=stringw(elem_animation->Attribute("position_x"));
        stringw pos_y=stringw(elem_animation->Attribute("position_y"));
        if(enteros.find(pos_x)==0)
        {
            pos_x=stringw("Animation.")+name+stringw(".x");
            setEntero(pos_x,atoi(elem_animation->Attribute("position_x")));
        }
        if(enteros.find(pos_y)==0)
        {
            pos_y=stringw("Animation.")+name+stringw(".y");
            setEntero(pos_y,atoi(elem_animation->Attribute("position_y")));
        }
        animaciones_back.push_back(Animacion(name,
                                        i_temp,
                                        pos_x,
                                        pos_y,
                                        atoi(elem_animation->Attribute("duration")),
                                        to_oponent));
        setString(stringw("Animation.")+name,"off");

    }


    for(TiXmlNode* nodo=front->FirstChild("Animation");
            nodo!=NULL;
            nodo=nodo->NextSibling("Animation"))
    {
        vector<Imagen>i_temp;
        for(TiXmlNode* nodo_frame=nodo->FirstChild("Sprite");
        nodo_frame!=NULL;
        nodo_frame=nodo_frame->NextSibling("Sprite"))
        {
            TiXmlElement *elem_frame=nodo_frame->ToElement();
            irr::video::ITexture *texture=grafico->getTexture(stringw(elem_frame->Attribute("path")));
            i_temp.push_back(Imagen(texture,
                                    (float)atoi(elem_frame->Attribute("scale")),
                                    atoi(elem_frame->Attribute("align_x")),
                                    atoi(elem_frame->Attribute("align_y"))));
        }
        TiXmlElement *elem_animation=nodo->ToElement();
        bool to_oponent=strcmp(elem_animation->Attribute("to_opponent"),"i")==0;
        stringw name=stringw(elem_animation->Attribute("name"));
        stringw pos_x=stringw(elem_animation->Attribute("position_x"));
        stringw pos_y=stringw(elem_animation->Attribute("position_y"));
        if(enteros.find(pos_x)==0)
        {
            pos_x=stringw("Animation.")+name+stringw(".x");
            setEntero(pos_x,atoi(elem_animation->Attribute("position_x")));
        }
        if(enteros.find(pos_y)==0)
        {
            pos_y=stringw("Animation.")+name+stringw(".y");
            setEntero(pos_y,atoi(elem_animation->Attribute("position_y")));
        }
        animaciones_front.push_back(Animacion(name,
                                        i_temp,
                                        pos_x,
                                        pos_y,
                                        atoi(elem_animation->Attribute("duration")),
                                        to_oponent));
        setString(stringw("Animation.")+name,"off");

    }
}

void Personaje::logicaProyectiles()
{
    for(int i=0;i<(int)proyectiles_actuales.size();i++)
    {
        Proyectil* proyectil=proyectiles_actuales[i];

        if(getString(proyectil->estado)!=stringw("on"))
            continue;

        Frame* fc=&proyectil->frames[proyectil->frame_actual];
        if(proyectil->tiempo_transcurrido==0)
        {
            aplicarModificadores(fc->modificadores,getString(proyectil->orientacion)=="i");
            setImagen(proyectil->imagen,proyectil->sprites[proyectil->sprite_actual]);
            proyectil->sprite_actual++;
            if(proyectil->sprite_actual>=(int)proyectil->sprites.size())
                proyectil->sprite_actual=0;
        }
        //avanzar frame
        if(proyectil->tiempo_transcurrido==fc->duracion)
        {
            proyectil->frame_actual++;
            proyectil->tiempo_transcurrido=0;
        }else
            proyectil->tiempo_transcurrido++;
        //verificar fin de movimiento
        if(proyectil->frame_actual==(int)proyectil->frames.size())
        {
            proyectil->frame_actual=0;
            setString(proyectil->estado,"off");
        }
        if(getColisionHitBoxes(personaje_contrario->getHitBoxes("blue"),getHitBoxes(proyectil->hitboxes),personaje_contrario->getEntero("posicion_x"),personaje_contrario->getEntero("posicion_y"),getEntero(proyectil->posicion_x),getEntero(proyectil->posicion_y)))
        {
            personaje_contrario->setEntero("hp.current_value",personaje_contrario->getEntero("hp.current_value")-proyectil->damage);
            proyectil->frame_actual=0;
            personaje_contrario->setString("hit","yes");
            setString(proyectil->estado,"off");
            setEntero("Colision.x",px_colision);
            setEntero("Colision.y",py_colision);
        }
    }
}

bool Personaje::getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
{
    int x1r=hb_roja.p1x+atacante_x;
    int y1r=hb_roja.p1y+atacante_y;
    int x2r=hb_roja.p2x+atacante_x;
    int y2r=hb_roja.p2y+atacante_y;

    int x1a=hb_azul.p1x+atacado_x;
    int y1a=hb_azul.p1y+atacado_y;
    int x2a=hb_azul.p2x+atacado_x;
    int y2a=hb_azul.p2y+atacado_y;

    bool hay_colision=(
                          (x1r<=x1a && x1a<=x2r && x2r<=x2a) ||
                          (x1r<=x1a && x1a<=x2a && x2a<=x2r) ||
                          (x1a<=x1r && x1r<=x2r && x2r<=x2a) ||
                          (x1a<=x1r && x1r<=x2a && x2a<=x2r)
                      )&&(
                          (y1r<=y1a && y1a<=y2r && y2r<=y2a) ||
                          (y1r<=y1a && y1a<=y2a && y2a<=y2r) ||
                          (y1a<=y1r && y1r<=y2r && y2r<=y2a) ||
                          (y1a<=y1r && y1r<=y2a && y2a<=y2r)
                      );

    if(hay_colision)
    {
        int x1,x2,y1,y2;
        if(x1a>x1r)x1=x1a;else x1=x1r;
        if(x2a<x2r)x2=x2a;else x2=x2r;

        if(y1a>y1r)y1=y1a;else y1=y1r;
        if(y2a<y2r)y2=y2a;else y2=y2r;

        px_colision=x1+((x2-x1)/2);
        py_colision=y1+((y2-y1)/2);
//        getPbActual()->setEntero("Colision.x",x1+((x2-x1)/2));
//        getPbActual()->setEntero("Colision.y",y1+((y2-y1)/2));
    }

    return hay_colision;
}

bool Personaje::getColisionHitBoxes(vector<HitBox> hb_azules,vector<HitBox> hb_rojas,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
{
    for(int a=0;a<(int)hb_azules.size();a++)
        for(int r=0;r<(int)hb_rojas.size();r++)
            if(getColisionHitBoxes(hb_azules[a],hb_rojas[r],atacado_x,atacado_y,atacante_x,atacante_y))
                return true;
    return false;
}

void Personaje::dibujarImagen(Grafico* grafico,Imagen imagen,int posicion_x,int posicion_y)
{
    irr::video::ITexture *texture=imagen.imagen;
    grafico->draw2DImage
    (   texture,
        irr::core::dimension2d<irr::f32> (texture->getOriginalSize ().Width,texture->getOriginalSize ().Height),
        irr::core::rect<irr::f32>(0,0,texture->getOriginalSize().Width,texture->getOriginalSize().Height),
        irr::core::position2d<irr::f32>(posicion_x+imagen.alineacion_x-(texture->getOriginalSize().Width*imagen.escala)/2,posicion_y+imagen.alineacion_y-(texture->getOriginalSize().Height*imagen.escala)/2),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (imagen.escala,imagen.escala),
        true,
        irr::video::SColor(255,255,255,255),
        false,
        false);
}
void Personaje::dibujarAnimacionesBack()
{
    for(int i=0;i<(int)animaciones_back.size();i++)
    {
        if(getString(stringw(stringw("Animation.")+animaciones_back[i].nombre))=="on")
        {
            animaciones_actuales_back.push_back(animaciones_back[i]);
            setString(stringw(stringw("Animation.")+animaciones_back[i].nombre),"off");
        }
    }
    for(int i=0;i<(int)animaciones_actuales_back.size();i++)
    {
        Animacion* animacion=&animaciones_actuales_back[i];
        dibujarImagen(grafico,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),getEntero(animacion->posicion_y));
        if(animacion->tiempo_transcurrido<animacion->duracion)//si todavia no termina la frame
        {
            animacion->tiempo_transcurrido++;
            continue;
        }
        //si ya termino el frame
        animacion->imagen_actual++;
        animacion->tiempo_transcurrido=0;
        //Cuando termina
        if(animacion->imagen_actual>=(int)animacion->sprites.size())
        {
            animaciones_actuales_back.erase(animaciones_actuales_back.begin()+i);
        }
    }
}

void Personaje::dibujarAnimacionesFront()
{
    for(int i=0;i<(int)animaciones_front.size();i++)
    {
        if(getString(stringw(stringw("Animation.")+animaciones_front[i].nombre))=="on")
        {
            animaciones_actuales_front.push_back(animaciones_front[i]);
            setString(stringw(stringw("Animation.")+animaciones_front[i].nombre),"off");
        }
    }
    for(int i=0;i<(int)animaciones_actuales_front.size();i++)
    {
        Animacion* animacion=&animaciones_actuales_front[i];
        dibujarImagen(grafico,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),getEntero(animacion->posicion_y));
        if(animacion->tiempo_transcurrido<animacion->duracion)//si todavia no termina la frame
        {
            animacion->tiempo_transcurrido++;
            continue;
        }
        //si ya termino el frame
        animacion->imagen_actual++;
        animacion->tiempo_transcurrido=0;
        //Cuando termina
        if(animacion->imagen_actual>=(int)animacion->sprites.size())
        {
            animaciones_actuales_front.erase(animaciones_actuales_front.begin()+i);
        }
    }
}
