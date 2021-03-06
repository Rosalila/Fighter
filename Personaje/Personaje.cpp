#include "Personaje.h"

Personaje::Personaje(RosalilaGraphics* painter,Sound* sonido,int numero,int num_paleta)
{
    writeLogLine("Initializing char.");
    this->painter=painter;
    this->sonido=sonido;
    this->numero=numero;
    this->combo=0;
    this->stage_piso=0;
    this->num_paleta=num_paleta;
    this->proyectiles_activos=0;

    setString("projectile_disolve","no");
    setString("projectile_disolve_chip","no");
    setString("projectile_hit","no");

    setString("player","0");
    if(numero==1)
        setString("player","1");
    if(numero==2)
        setString("player","2");

    std::vector<Hitbox*> hitbox;
    setHitboxes("red",hitbox);
    setHitboxes("blue",hitbox);
    setImagen("current_image",NULL);
    setString("change_char","off");
    setEntero("distance",0);
    setEntero("distance_absolute",0);
    setString("hit","no");
    setEntero("velocity_x",0);
    setEntero("velocity_y",0);
    setEntero("acceleration_x",0);
    setEntero("acceleration_y",0);
}
Personaje::~Personaje()
{
    writeLogLine("Deleting character.");
    for(; !textures.empty();)
    {
        writeLogLine("Deleting character image.");
        Image*image=textures.back();
        textures.pop_back();
        delete image;
    }

    for(; !animaciones_back.empty();)
    {
        writeLogLine("Deleting character back animation.");
        Animacion*animacion=animaciones_back.back();
        animaciones_back.pop_back();
        delete animacion;
    }

    for(; !animaciones_front.empty();)
    {
        writeLogLine("Deleting character front animation.");
        Animacion*animacion=animaciones_front.back();
        animaciones_front.pop_back();
        delete animacion;
    }

    for(; !inputs.empty();)
    {
        writeLogLine("Deleting character input image.");
        InputMovimiento*input_movimiento=inputs.back();
        inputs.pop_back();
        delete input_movimiento;
    }

    for(; !movimientos_constantes_actuales.empty();)
    {
        writeLogLine("Deleting character move.");
        Movimiento*movimiento=movimientos_constantes_actuales.back();
        movimientos_constantes_actuales.pop_back();
        delete movimiento;
    }

    for(; !proyectiles_actuales.empty();)
    {
        writeLogLine("Deleting character projectile.");
        Proyectil*proyectil=proyectiles_actuales.back();
        proyectiles_actuales.pop_back();
        delete proyectil;
    }

    for(; !barras.empty();)
    {
        writeLogLine("Deleting character bar.");
        Barra*barra=barras.back();
        barras.pop_back();
        delete barra;
    }

//((Movimiento*)movimientos[movimiento])->agregarFrame(duracion);
    for(map<string,Movimiento*>::iterator i=movimientos.begin();
            i!=movimientos.end();
            i++)//!!!!
    {
        writeLogLine("Deleting move.");
        Movimiento* movimiento = i->second;
        delete movimiento;
    }
}
//DIBUJAR
void Personaje::dibujar()
{
    bool shadow=getString("effect.shadow")==std::string("on");
    bool violet=getString("effect.violet")==std::string("on");
    bool red=getString("effect.red")==std::string("on");
    bool green=getString("effect.green")==std::string("on");
    bool blue=getString("effect.blue")==std::string("on");
    if(sombra.size()>7)
    {
        sombra.erase (sombra.begin());
        sombra_x.erase (sombra_x.begin());
        sombra_y.erase (sombra_y.begin());
        flip_sombra.erase (flip_sombra.begin());
    }
    if(shadow)
    {
        for(int i=1; i<(int)sombra.size(); i++)
        {
            if(i%3!=0)
                continue;
            if(sombra[i]->imagen==NULL)
                continue;
            int dimension_x=sombra[i]->dimension_x;
            int dimension_y=sombra[i]->dimension_y;
            int alineacion_x=sombra[i]->alineacion_x;
            int alineacion_y=sombra[i]->alineacion_y;
            if(flip_sombra[i])
                alineacion_x=-alineacion_x;
            //    u32 t=painter->device->getTimer()->getTime();
            //    int t2=t%255;
            int pos_x=sombra_x[i]-(dimension_x*sombra[i]->escala/2)+alineacion_x;
            int pos_y=-sombra_y[i]-(dimension_y*sombra[i]->escala)-alineacion_y+painter->screen_height-stage_piso;
            painter->draw2DImage
            (   sombra[i]->imagen,
                dimension_x,dimension_y,
                pos_x,pos_y,
                sombra[i]->escala,
                0.0,
                flip_sombra[i],
                0,0,
                Color(0,0,255,128),
                0,0,
                true,
                FlatShadow());
        }
    }

    if(getImagen("current_image")==NULL)
        return;
    if(getImagen("current_image")->imagen==NULL)
        return;
    int dimension_x=getImagen("current_image")->dimension_x;
    int dimension_y=getImagen("current_image")->dimension_y;
    int alineacion_x=getImagen("current_image")->alineacion_x;
    int alineacion_y=getImagen("current_image")->alineacion_y;
    //u32 t=painter->device->getTimer()->getTime();//!!COOL VFX
    int t=painter->current_fps;
    int tr=255,tg=255,tb=255;

    if(getString("orientation")=="i")
        alineacion_x=-alineacion_x;

    if(violet)//!!COOL VFX
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

    //Image* texture=getImagen("current_image")->imagen;
    //if(numero==1)
    //paleta.paintTexture(texture);

    //get pos
    int pos_x=getEntero("position_x")-(dimension_x*getImagen("current_image")->escala/2)+alineacion_x;
    int pos_y=-getEntero("position_y")-(dimension_y*getImagen("current_image")->escala)-alineacion_y+painter->screen_height-stage_piso;


    painter->draw2DImage
    (   getImagen("current_image")->imagen,
        dimension_x,dimension_y,
        pos_x,pos_y,
        getImagen("current_image")->escala,
        0.0,
        getString("orientation")=="i",
        0,0,
        Color(tr,tg,tb,255),
        -200,-300,
        true,
        FlatShadow());
//    if(numero==1)
    //paleta.restoreTexture(texture);

    sombra.push_back(getImagen("current_image"));
    sombra_x.push_back(getEntero("position_x"));
    sombra_y.push_back(getEntero("position_y"));
    flip_sombra.push_back(getString("orientation")=="i");
}
void Personaje::dibujarHitboxes(std::string variable,std::string path,bool izquierda,int x,int y)
{
    /*
    std::vector <Hitbox*> hitbox=getHitboxes(variable);
    if(getString("orientation")=="i")
        for(int i=0; i<(int)hitbox.size(); i++)
        {
            int a=hitbox[i]->p1x;
            int b=hitbox[i]->p2x;
            hitbox[i]->p1x=-b;
            hitbox[i]->p2x=-a;
        }
    for(int i=0; i<(int)hitbox.size(); i++)
    {
        int p1x=x+hitbox[i]->p1x;
        int p1y=-y+hitbox[i]->p1y+painter->screen_height-stage_piso;
        int p2x=x+hitbox[i]->p2x;
        int p2y=-y+hitbox[i]->p2y+painter->screen_height-stage_piso;
        if(variable=="blue")
            painter->drawRectangle(p1x,p1y,p2x-p1x,p2y-p1y,0.0,0,0,100,127,true);
        else
            painter->drawRectangle(p1x,p1y,p2x-p1x,p2y-p1y,0.0,100,0,0,127,true);
    }
    if(getString("orientation")=="i")
        for(int i=0; i<(int)hitbox.size(); i++)
        {
            int a=hitbox[i]->p1x;
            int b=hitbox[i]->p2x;
            hitbox[i]->p1x=-b;
            hitbox[i]->p2x=-a;
        }
    */
}

void Personaje::dibujarBarra(Barra* barra)
{
//    irr::core::position2d<irr::s32>punto1= barra->posicion.UpperLeftCorner;
//    irr::core::position2d<irr::s32>punto2= barra->posicion.LowerRightCorner;
    //resize 800x600
//    float w=painter->screen_width;
//    barra->pos_x1*=w/1024.0;
//    barra->pos_x2*=w/1024.0;
    float longitud_total=(float)barra->pos_x2-(float)barra->pos_x1;
    if(longitud_total<0)//if esta flipeada
        longitud_total=-longitud_total;
    float longitud_actual=((float)longitud_total/getEntero(barra->valor_maximo))*(float)getEntero(barra->valor_actual);
    float altura=(float)barra->pos_y2-(float)barra->pos_y1;

    float p1x,p1y,p2x,p2y;
    bool player2=false;
    if(numero==1)//player 1
    {
        p1x=barra->pos_x1;
        p1y=barra->pos_y1;
        p2x=barra->pos_x1+longitud_actual;
        p2y=barra->pos_y2;

        if(barra->pos_x1>barra->pos_x2)
        {
            p1x=barra->pos_x1-longitud_actual;
            p2x=barra->pos_x1;
        }
    }
    else //flip if player 2
    {
        float temp_x1=painter->screen_width-barra->pos_x1-longitud_actual;
        float temp_x2=painter->screen_width-barra->pos_x1;

        if(barra->pos_x1>barra->pos_x2)
        {
            temp_x1=painter->screen_width-barra->pos_x1+longitud_actual;
            temp_x2=painter->screen_width-barra->pos_x1;
        }

        p1x=temp_x2;
        p1y=barra->pos_y1;
        p2x=temp_x1;
        p2y=barra->pos_y2;

        player2=true;
    }
    bool flip=false;
    if(barra->pos_x1>barra->pos_x2 && !player2)
    {
        flip=true;
    }
    if(( (barra->pos_x1>barra->pos_x2) == false) && player2)
    {
        flip=true;
    }

    if(barra->imagen==NULL)
        painter->drawRectangle(p1x,p1y,p2x-p1x,p2y-p1y,0.0,barra->color.getRed(),barra->color.getGreen(),barra->color.getBlue(),barra->color.getAlpha(),false);
    else
        painter->draw2DImage
        (   barra->imagen,
            longitud_actual,altura,
            //irr::core::rect<irr::f32>(0,0,barra.imagen->getOriginalSize().Width*((float)getEntero(barra.valor_actual)/(float)getEntero(barra.valor_maximo)),barra.imagen->getOriginalSize().Height),//!!DRAW BAR
            p1x,p1y,
            1.0,
            0.0,
            flip,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());
}

void Personaje::dibujarBarraPequena(Barra* barra,int cambio_x,int cambio_y)
{
//    irr::core::position2d<irr::s32>punto1= barra->posicion.UpperLeftCorner;
//    irr::core::position2d<irr::s32>punto2= barra->posicion.LowerRightCorner;
    //resize 800x600
    float w=painter->screen_width;
    barra->pos_x1*=w/1024.0;
    barra->pos_x2*=w/1024.0;
    float longitud_total=(float)barra->pos_x2-(float)barra->pos_x1;
    float longitud_actual=((float)longitud_total/getEntero(barra->valor_maximo))*(float)getEntero(barra->valor_actual);
    float altura=(float)barra->pos_y2-(float)barra->pos_y1;

    float p1x,p1y,p2x,p2y;
    bool player2=false;
    if(numero==1)//player 1
    {
        p1x=barra->pos_x1;
        p1y=barra->pos_y1;
        p2x=barra->pos_x1+longitud_actual;
        p2y=barra->pos_y2;

        p1x+=cambio_x;
        p2x+=cambio_x;
        p1y+=cambio_y;
        p2y+=cambio_y;
        p2x-=(p2x-p1x)/2;
        p2y-=(p2y-p1y)/2;
    }
    else //flip if player 2
    {
        float temp_x2=painter->screen_width-barra->pos_x1;
        float temp_x1=painter->screen_width-barra->pos_x1-longitud_actual;

        p1x=temp_x1;
        p1y=barra->pos_y1;
        p2x=temp_x2;
        p2y=barra->pos_y2;

        p1x-=cambio_x;
        p2x-=cambio_x;
        p1y+=cambio_y;
        p2y+=cambio_y;
        p1x-=(p1x-p2x)/2;
        p2y-=(p2y-p1y)/2;

        player2=true;
    }
    if(barra->imagen==NULL)
    {
        painter->drawRectangle(p1x,p1y,p1x-p2x,p1y-p2y,0.0,barra->color.getRed(),barra->color.getGreen(),barra->color.getBlue(),barra->color.getAlpha(),false);
    }
    else
        painter->draw2DImage
        (   barra->imagen,
            longitud_actual,altura,
            //irr::core::rect<irr::f32>(0,0,barra.imagen->getOriginalSize().Width*((float)getEntero(barra.valor_actual)/(float)getEntero(barra.valor_maximo)),barra.imagen->getOriginalSize().Height),//!!DRAW BAR
            p1x,p1y,
            1.0,
            0.0,
            player2,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());
}

void Personaje::dibujarBarras()
{
    for(int i=0; i<(int)barras.size(); i++)
    {
        dibujarBarra(barras[i]);
    }
}

void Personaje::dibujarProyectiles()
{
    for(int i=0; i<(int)proyectiles_actuales.size(); i++)
    {
        Proyectil* proyectil=proyectiles_actuales[i];
        if(getString(proyectil->estado)!="on")
            continue;

        if(proyectil->sprites.size()!=0)
        {
            Imagen* imagen=getImagen(proyectil->imagen);
            int pos_x=getEntero(proyectil->posicion_x)-(imagen->imagen->getWidth()*imagen->escala/2)+imagen->alineacion_x;
            int pos_y=getEntero(proyectil->posicion_y)-(imagen->imagen->getHeight()*imagen->escala/2)+imagen->alineacion_y+painter->screen_height-stage_piso;
            painter->draw2DImage
            (   imagen->imagen,
                imagen->imagen->getWidth(),imagen->imagen->getHeight(),
                pos_x,pos_y,
                imagen->escala,
                0.0,
                getString(proyectil->orientacion)=="i",
                0,0,
                Color(255,255,255,255),
                0,0,
                true,
                FlatShadow());
        }
//        //Dibujar hitboxes
//        if(input->receiver->IsKeyDownn(SDLK_h))
//        {
//            std::string nombre=proyectil->nombre;
//            dibujarHitboxes(proyectil->hitboxes,"",
//                        getString(proyectil->orientacion)=="i",
//                        getEntero(proyectil->posicion_x),
//                        -getEntero(proyectil->posicion_y));
//        }
    }
}
//GETS shortcuts
Movimiento* Personaje::getMovimientoActual()
{
    return movimientos[getString("current_move")];
}
Frame* Personaje::getFrameActual()
{
    return getMovimientoActual()->getFrameActual();
}
//GETS variables
int Personaje::getEntero(std::string variable)
{
    if(enteros.find(variable)==enteros.end())
    {
        writeLogLine("Integer error: "+variable+" not defined.");
    }
    return enteros[variable];
}
Barra* Personaje::getBarra(std::string variable)
{
    for(int i=0; i<(int)barras.size(); i++)
        if(barras[i]->nombre==variable)
            return barras[i];
    writeLogLine("Bar error: "+variable+" not defined.");
    return NULL;
//    return new Barra("error","","","","",Color(0,0,0,0),irr::core::rect<irr::s32> (0,0,0,0),NULL);
}
vector<Hitbox*> Personaje::getHitboxes(std::string variable)
{
    if(hitboxes.find(variable)==hitboxes.end())
    {
        writeLogLine("Hitbox error: "+variable+" not defined.");
    }
    return hitboxes[variable];
}
Imagen* Personaje::getImagen(std::string variable)
{
    if(imagenes.find(variable)==imagenes.end())
    {
        writeLogLine("Image error: "+variable+" not defined.");
    }
    return imagenes[variable];
}
std::string Personaje::getString(std::string variable)
{
    if(strings.find(variable)==strings.end())
    {
        writeLogLine("Strings error: "+variable+" not defined.");
    }
    return strings[variable];
}
//SETS variables
void Personaje::setImagen(std::string variable,Imagen *valor)
{
    imagenes[variable]=valor;
}
void Personaje::setEntero(std::string variable,int valor)
{
    enteros[variable]=valor;
}
void Personaje::agregarBarra(Barra* valor)
{
    barras.push_back(valor);
}
void Personaje::setHitboxes(std::string variable,vector<Hitbox*> valor)
{
    hitboxes[variable]=valor;
}
void Personaje::setString(std::string variable,std::string valor)
{
    strings[variable]=valor;
}

//Agregares
void Personaje::agregarRosalilaInputs(vector<std::string> input,std::string movimiento)
{
    inputs.push_back(new InputMovimiento(input,movimiento));
}

void Personaje::agregarRosalilaInputs(std::string input,std::string movimiento)
{
    std::vector<std::string> lista_input;
    lista_input.push_back(input);
    inputs.push_back(new InputMovimiento(lista_input,movimiento));
}

void Personaje::agregarCondicion(std::string movimiento,int frame,vector<Condicion*> condicion)
{
    ((Movimiento*)movimientos[movimiento])->agregarCondicion(condicion,frame);
}

void Personaje::agregarMovimiento(std::string movimiento,int damage, int blockstun,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low,int velocity_x,int velocity_y,int acceleration_x,int acceleration_y,bool inherits_velocity, bool pushes,int separate_blue,int separate_red,int repeat_from,bool land_cancelable,bool crouched,bool is_status,int stop_time_at,int resume_time_at,string cancel_on_hit,bool is_attack,bool friction,int final_velocity_x,int final_velocity_y,int final_acceleration_x,int final_acceleration_y)
{
    movimientos[movimiento]=new Movimiento(movimiento,damage, blockstun,chip_damage,multihit,unblockable_air,unblockable_high,unblockable_low,velocity_x,velocity_y,acceleration_x,acceleration_y,inherits_velocity,pushes,separate_blue,separate_red,repeat_from,land_cancelable,crouched,is_status,stop_time_at,resume_time_at,cancel_on_hit,is_attack,friction,final_velocity_x,final_velocity_y,final_acceleration_x,final_acceleration_y);
}
void Personaje::agregarProyectil(Proyectil* proyectil)
{
    proyectiles_actuales.push_back(proyectil);
}
void Personaje::agregarFrame(std::string movimiento, int duracion)
{
    ((Movimiento*)movimientos[movimiento])->agregarFrame(duracion);
}
void Personaje::agregarModificador(std::string movimiento,int frame,std::string variable,Imagen* modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame]->agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(std::string movimiento,int frame,std::string variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame]->agregarModificador(modificador,variable,relativo,aplicar_a_contrario,flipeable);
}
void Personaje::agregarModificador(std::string movimiento,int frame,std::string variable,Barra modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame]->agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(std::string movimiento,int frame,std::string variable,vector <Hitbox*> modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame]->agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(std::string movimiento,int frame,std::string variable,std::string modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame]->agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(std::string movimiento,int frame,std::string tipo,std::string variable,std::string variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame]->agregarModificador(tipo,variable_modificador,variable,relativo,aplicar_a_contrario,flipeable);
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

void Personaje::flipHitboxes()
{
    /*
    std::vector<Hitbox*> hb=getHitboxes("blue");
    for(int i=0; i<(int)hb.size(); i++)
    {
        int a=hb[i]->p1x;
        int b=hb[i]->p2x;
        hb[i]->p1x=-b;
        hb[i]->p2x=-a;
    }
    setHitboxes("blue",hb);

    hb=getHitboxes("red");
    for(int i=0; i<(int)hb.size(); i++)
    {
        int a=hb[i]->p1x;
        int b=hb[i]->p2x;
        hb[i]->p1x=-b;
        hb[i]->p2x=-a;
    }
    setHitboxes("red",hb);
    */
}

void Personaje::aplicarModificador(ModificadorHitboxes* mh)
{
    if(mh->aplicar_a_contrario)
        personaje_contrario->setHitboxes(mh->variable,mh->modificador_hitbox);
    else
        setHitboxes(mh->variable,mh->modificador_hitbox);
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
        }
        else
        {
            if(mv->aplicar_a_contrario)
            {
                int temp_entero=0;
                if(mv->modificador_string!="position_y")
                {
                    temp_entero=personaje_contrario->getEntero(mv->modificador_string);
                }
                else
                {
                    temp_entero=-personaje_contrario->getEntero(mv->modificador_string);
                }
                if(mv->flipeable)
                    temp_entero=-temp_entero;
                personaje_contrario->setEntero(mv->variable,temp_entero);
            }
            else
            {
                int temp_entero;
                if(mv->modificador_string!="position_y")
                {
                    temp_entero=getEntero(mv->modificador_string);
                }
                else
                {
                    temp_entero=-getEntero(mv->modificador_string);
                }

                if(mv->flipeable)
                    temp_entero=-temp_entero;
                setEntero(mv->variable,temp_entero);
            }
        }
    }
}

//Logica
std::string Personaje::mapInputToMovimiento()
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

    for(int i=0; i<(int)inputs.size(); i++)
        if(inputEstaEnBuffer(inputs[i]->input,input->getBufferRosalilaInputs()))
            if(cumpleCondiciones(inputs[i]->movimiento))
                return inputs[i]->movimiento;
    return "";
}
bool Personaje::inputEstaEnBuffer(vector<std::string> input,vector<std::string> buffer)
{
    if(input.size()==1)
    {
        if(input[0]=="*")
            return true;
        return input[0]==buffer[0];
    }
    int j=(int)input.size()-1;

    //Precise
    for(int i=0; i<(int)buffer.size(); i++)
    {
        if(input[j]!=buffer[i])
            return false;
        while(i<(int)buffer.size())
        {
            if(input[j]!=buffer[i])
                break;
            i++;
        }
        i--;
        j--;
        if(j==-1)
            return true;
    }
    return false;

//    //Not precise
//    for(int i=0;i<(int)buffer.size();i++)
//    {
//        if(input[j]==buffer[i])
//            j--;
//        if(j==-1)
//            return true;
//    }
//    return false;
}
bool Personaje::cumpleCondiciones(std::string str_movimiento)
{
    Movimiento*movimiento=movimientos[str_movimiento];
    Frame *frame=movimiento->frames[0];
    std::vector<vector<Condicion*> > condiciones=frame->condiciones;
    for(int i=0; i<(int)condiciones.size(); i++)
    {
        std::vector<Condicion*> subcondiciones=condiciones[i];
        bool flag=true;
        for(int j=0; j<(int)subcondiciones.size(); j++)
        {
            Condicion* c_temp=(Condicion*)subcondiciones[j];
            if(!cumpleCondicion(c_temp))
            {
                flag=false;
            }
        }
        if(flag)
        {
            return true;
        }
    }
    return false;
}
bool Personaje::cumpleCondiciones(vector<vector<Condicion*> >condiciones)
{
    for(int i=0; i<(int)condiciones.size(); i++)
    {
        std::vector<Condicion*> subcondiciones=condiciones[i];
        bool flag=true;
        for(int j=0; j<(int)subcondiciones.size(); j++)
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
    }
    else if(condicion->tipo=="entero")
    {
        return condicion->comparar(personaje->getEntero(condicion->variable));
    }
    return false;
}
void Personaje::aplicarModificadores(vector<Modificador*> modificadores,bool flip)
{
    for(int i=0; i<(int)modificadores.size(); i++)
    {
        Modificador* modificador=modificadores[i];
        if(modificador->tipo=="imagen")
            aplicarModificador((ModificadorImagen*)modificador);
        if(modificador->tipo=="entero")
            aplicarModificador((ModificadorEntero*)modificador,flip);
        if(modificador->tipo=="string")
            aplicarModificador((ModificadorString*)modificador);
        if(modificador->tipo=="hitboxes")
            aplicarModificador((ModificadorHitboxes*)modificador);
        if(modificador->tipo=="variable")
            aplicarModificador((ModificadorPorVariable*)modificador);
    }
}

void Personaje::loadFromXML(RosalilaInputs* input,char* nombre)
{
    writeLogLine("Loading "+std::string(nombre)+" from XML.");
    this->input=input;
    this->painter=painter;
    this->char_name=std::string(nombre);
    this->char_name_ptr=nombre;

    setString("effect.shadow","off");
    setString("effect.violet","off");
    setString("effect.red","off");
    setString("effect.green","off");
    setString("effect.blue","off");

    setString("attacking","no");
    setString("projectile_active","no");

    setEntero("Colision.x",0);
    setEntero("Colision.y",0);

    setEntero("position_x",0);
    setEntero("position_y",0);

    string xml_path=assets_directory+"chars/"+nombre+"/palettes.xml";
    paleta.cargarXML((char*)xml_path.c_str(),num_paleta);

    loadMain();

    loadVars();

    loadInputs();

    loadTriggers();

    loadSprites();

    loadHitboxes();

    loadSfx();

    loadAnimations();

    loadProjectiles();
}

void Personaje::logicaBarras()
{
    for(int i=0; i<(int)barras.size(); i++)
    {
        if(barras[i]->procesarTiempo(getEntero(barras[i]->periodo)))
            if(!barras[i]->stay_at_max || getEntero(barras[i]->valor_actual)<getEntero(barras[i]->valor_maximo))
                setEntero(barras[i]->valor_actual,getEntero(barras[i]->valor_actual)+getEntero(barras[i]->modificador_periodico));
        if(getEntero(barras[i]->valor_actual)>getEntero(barras[i]->valor_maximo))
            setEntero(barras[i]->valor_actual,getEntero(barras[i]->valor_maximo));
        if(getEntero(barras[i]->valor_actual)<0)
            setEntero(barras[i]->valor_actual,0);
    }
}

void Personaje::loadMain()
{
    writeLogLine("Loading main.xml");
    string xml_path=assets_directory+"chars/"+char_name_ptr+"/main.xml";

    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;
    TiXmlNode*main_file=doc->FirstChild("MainFile");

    writeLogLine("Loading IgnoreColor.");

    TiXmlNode* ignore_color_node=main_file->FirstChild("IgnoreColor");
    Color* ignore_color=NULL;
    if(ignore_color_node!=NULL)
    {
        ignore_color=new Color(0,atoi(ignore_color_node->ToElement()->Attribute("red")),
                               atoi(ignore_color_node->ToElement()->Attribute("green")),
                               atoi(ignore_color_node->ToElement()->Attribute("blue")));
    }

    writeLogLine("Loading Declarations.");

    for(TiXmlNode* nodo=main_file->FirstChild("Declarations");
            nodo!=NULL;
            nodo=nodo->NextSibling("Declarations"))
    {
        writeLogLine("Loading Moves declarations.");
        for(TiXmlElement *elemento_imagen=nodo->FirstChild("Move")->ToElement();
                elemento_imagen!=NULL;
                elemento_imagen=elemento_imagen->NextSiblingElement("Move"))
        {
            std::string nombre(elemento_imagen->Attribute("name"));
            writeLogLine("Loading "+nombre);
            int frames=atoi(elemento_imagen->Attribute("frames"));
            int frame_duration=atoi(elemento_imagen->Attribute("frame_duration"));

            int damage=0;
            if(elemento_imagen->Attribute("damage")!=NULL)
                damage=atoi(elemento_imagen->Attribute("damage"));

            int blockstun=0;
            if(elemento_imagen->Attribute("blockstun")!=NULL)
                blockstun=atoi(elemento_imagen->Attribute("blockstun"));

            int chip_damage=0;
            if(elemento_imagen->Attribute("chip_damage")!=NULL)
                chip_damage=atoi(elemento_imagen->Attribute("chip_damage"));

            bool multihit=false;
            if(elemento_imagen->Attribute("multihit")!=NULL)
                multihit=strcmp(elemento_imagen->Attribute("multihit"),"yes")==0;

            bool unblockable_air=false;
            if(elemento_imagen->Attribute("unblockable_air")!=NULL)
                unblockable_air=strcmp(elemento_imagen->Attribute("unblockable_air"),"yes")==0;

            bool unblockable_high=false;
            if(elemento_imagen->Attribute("unblockable_high")!=NULL)
                unblockable_high=strcmp(elemento_imagen->Attribute("unblockable_high"),"yes")==0;

            bool unblockable_low=false;
            if(elemento_imagen->Attribute("unblockable_low")!=NULL)
                unblockable_low=strcmp(elemento_imagen->Attribute("unblockable_low"),"yes")==0;

            int velocity_x=0;
            if(elemento_imagen->Attribute("velocity_x")!=NULL)
                velocity_x=atoi(elemento_imagen->Attribute("velocity_x"));

            int velocity_y=0;
            if(elemento_imagen->Attribute("velocity_y")!=NULL)
                velocity_y=atoi(elemento_imagen->Attribute("velocity_y"));

            int acceleration_x=0;
            if(elemento_imagen->Attribute("acceleration_x")!=NULL)
                acceleration_x=atoi(elemento_imagen->Attribute("acceleration_x"));

            int acceleration_y=0;
            if(elemento_imagen->Attribute("acceleration_y")!=NULL)
                acceleration_y=atoi(elemento_imagen->Attribute("acceleration_y"));

            bool inherits_velocity=false;
            if(elemento_imagen->Attribute("inherits_velocity")!=NULL)
                inherits_velocity=strcmp(elemento_imagen->Attribute("inherits_velocity"),"yes")==0;

            bool pushes=false;
            if(elemento_imagen->Attribute("pushes")!=NULL)
                pushes=strcmp(elemento_imagen->Attribute("pushes"),"yes")==0;

            int separate_blue=0;
            if(elemento_imagen->Attribute("separate_blue")!=NULL)
                separate_blue=atoi(elemento_imagen->Attribute("separate_blue"));

            int separate_red=0;
            if(elemento_imagen->Attribute("separate_red")!=NULL)
                separate_red=atoi(elemento_imagen->Attribute("separate_red"));

            int repeat_from=-1;
            if(elemento_imagen->Attribute("repeat_from")!=NULL)
                repeat_from=atoi(elemento_imagen->Attribute("repeat_from"))-1;

            bool land_cancelable=false;
            if(elemento_imagen->Attribute("land_cancelable")!=NULL)
                land_cancelable=strcmp(elemento_imagen->Attribute("land_cancelable"),"yes")==0;

            bool crouched=false;
            if(elemento_imagen->Attribute("crouched")!=NULL)
                crouched=strcmp(elemento_imagen->Attribute("crouched"),"yes")==0;

            bool is_status=false;
            if(elemento_imagen->Attribute("is_status")!=NULL)
                is_status=strcmp(elemento_imagen->Attribute("is_status"),"yes")==0;

            int stop_time_at=-1;
            if(elemento_imagen->Attribute("stop_time_at")!=NULL)
                stop_time_at=atoi(elemento_imagen->Attribute("stop_time_at"));

            int resume_time_at=-1;
            if(elemento_imagen->Attribute("resume_time_at")!=NULL)
                resume_time_at=atoi(elemento_imagen->Attribute("resume_time_at"));

            string cancel_on_hit="";
            if(elemento_imagen->Attribute("cancel_on_hit")!=NULL)
                cancel_on_hit=elemento_imagen->Attribute("cancel_on_hit");

            bool is_attack=false;
            if(elemento_imagen->Attribute("is_attack")!=NULL)
                is_attack=strcmp(elemento_imagen->Attribute("is_attack"),"yes")==0;

            bool friction=false;
            if(elemento_imagen->Attribute("friction")!=NULL)
                friction=strcmp(elemento_imagen->Attribute("friction"),"yes")==0;

            int final_velocity_x=9999;
            if(elemento_imagen->Attribute("final_velocity_x")!=NULL)
                final_velocity_x=atoi(elemento_imagen->Attribute("final_velocity_x"));

            int final_velocity_y=9999;
            if(elemento_imagen->Attribute("final_velocity_y")!=NULL)
                final_velocity_y=atoi(elemento_imagen->Attribute("final_velocity_y"));

            int final_acceleration_x=9999;
            if(elemento_imagen->Attribute("final_acceleration_x")!=NULL)
                final_acceleration_x=atoi(elemento_imagen->Attribute("final_acceleration_x"));

            int final_acceleration_y=9999;
            if(elemento_imagen->Attribute("final_acceleration_y")!=NULL)
                final_acceleration_y=atoi(elemento_imagen->Attribute("final_acceleration_y"));

            setString(std::string("isActive.")+nombre,"no");

            agregarMovimiento(nombre,damage,blockstun,chip_damage,multihit,unblockable_air,unblockable_high,unblockable_low,velocity_x,velocity_y,acceleration_x,acceleration_y,inherits_velocity,pushes,separate_blue,separate_red,repeat_from,land_cancelable,crouched,is_status,stop_time_at,resume_time_at,cancel_on_hit,is_attack,friction,final_velocity_x,final_velocity_y,final_acceleration_x,final_acceleration_y);
            for(int i=0; i<frames; i++)
                agregarFrame(nombre,frame_duration);
        }

        writeLogLine("Loading sprites.");
        if(nodo->FirstChild("sprite")!=NULL)
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("sprite")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("sprite"))
            {
                std::string variable(elemento_imagen->Attribute("variable"));
                std::string path(elemento_imagen->Attribute("path"));
                writeLogLine("Loading "+path);
                std::string dir("chars/");
                path=dir+char_name+"/"+path;
                int escala=atoi(elemento_imagen->Attribute("scale"));
                int alineacion_x=atoi(elemento_imagen->Attribute("align_x"));
                int alineacion_y=atoi(elemento_imagen->Attribute("align_y"));

                if(ignore_color==NULL)
                    setImagen(variable,new Imagen(painter->getTexture(assets_directory+path),escala,alineacion_x,alineacion_y));
//                else//!!IGNORE COLOR
//                    setImagen(variable,Imagen(painter->getTexture(path,ignore_color),escala,alineacion_x,alineacion_y));
            }
        writeLogLine("Loading strings.");
        if(nodo->FirstChild("string")!=NULL)
        {
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("string")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("string"))
            {
                std::string variable(elemento_imagen->Attribute("variable"));
                writeLogLine("Loading "+variable);
                std::string valor(elemento_imagen->Attribute("value"));
                setString(variable,valor);
            }
        }
        writeLogLine("Loading integer.");
        if(nodo->FirstChild("integer")!=NULL)
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("integer")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("integer"))
            {
                std::string variable(elemento_imagen->Attribute("variable"));
                writeLogLine("Loading "+variable);
                int valor=atoi(elemento_imagen->Attribute("value"));
                setEntero(variable,valor);
            }
        writeLogLine("Loading hitboxes.");
        if(nodo->FirstChild("hitboxes")!=NULL)
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("hitboxes")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("hitboxes"))
            {
                std::string variable(elemento_imagen->Attribute("variable"));
                writeLogLine("Loading "+variable);
                std::vector<Hitbox*> hitbox;
                if(!elemento_imagen->NoChildren())
                    for(TiXmlElement *elemento_hitbox=elemento_imagen->FirstChild("Hitbox")->ToElement();
                            elemento_hitbox!=NULL;
                            elemento_hitbox=elemento_hitbox->NextSiblingElement("Hitbox"))
                    {
                        int x1=atoi(elemento_hitbox->Attribute("x1"));
                        int y1=atoi(elemento_hitbox->Attribute("y1"));
                        int x2=atoi(elemento_hitbox->Attribute("x2"));
                        int y2=atoi(elemento_hitbox->Attribute("y2"));
                        hitbox.push_back(new Hitbox(x1,-y1,x2,-y2,0.0));
                    }
                setHitboxes(variable,hitbox);
            }
        writeLogLine("Loading bars.");
        for(TiXmlElement *elemento_imagen=nodo->FirstChild("bar")->ToElement();
                elemento_imagen!=NULL;
                elemento_imagen=elemento_imagen->NextSiblingElement("bar"))
        {
            std::string variable(elemento_imagen->Attribute("variable"));
            writeLogLine("Loading "+variable);
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

            bool stay_at_max=false;
            if(elemento_imagen->Attribute("stay_at_max")!=NULL)
                stay_at_max=strcmp(elemento_imagen->Attribute("stay_at_max"),"yes")==0;

            if(elemento_imagen->Attribute("image")!=NULL)
            {
                std::string imagen(elemento_imagen->Attribute("image"));
                imagen=std::string("chars/")+char_name+std::string("/")+imagen;
                agregarBarra(new Barra(variable,variable+".max_value",variable+".current_value",variable+".periodic_modifier",variable+".period",Color(r,g,b,alpha),x1,y1,x2,y2,stay_at_max,painter->getTexture(assets_directory+imagen)));
            }
            else
                agregarBarra(new Barra(variable,variable+".max_value",variable+".current_value",variable+".periodic_modifier",variable+".period",Color(r,g,b,alpha),x1,y1,x2,y2,stay_at_max,NULL));
        }
    }
}

void Personaje::loadVars()
{
    writeLogLine("Loading vars.xml");

    string xml_path=assets_directory+"chars/"+char_name_ptr+"/vars.xml";

    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode*vars_file=doc->FirstChild("VarsFile");

    for(TiXmlNode* nodo=vars_file->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        std::string nombre(elemento->Attribute("name"));
        //For each RosalilaInputs

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
                        std::string str_tipo(e->Attribute("type"));
                        std::string str_variable(e->Attribute("variable"));
                        std::string str_valor(e->Attribute("value"));
                        std::string str_contrario(e->Attribute("to_opponent"));
                        std::string str_relativo(e->Attribute("relative"));
                        std::string str_flipeable(e->Attribute("flipable"));
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
                        std::string str_variable(e->Attribute("variable"));
                        std::string str_contrario(e->Attribute("to_opponent"));
                        std::string str_relativo(e->Attribute("relative"));
                        std::string str_flipeable(e->Attribute("flipable"));
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
                        std::string str_variable(e->Attribute("variable"));
                        std::string str_contrario(e->Attribute("to_opponent"));
                        std::string str_valor(e->Attribute("value"));
                        bool contrario=(str_contrario=="yes");
                        agregarModificador(nombre,frame,str_variable,str_valor,contrario);
                    }
                }
            }
        }
        //For each Condiciones
    }
}

void Personaje::loadInputs()
{
    writeLogLine("Loading input.xml");

    string xml_path=assets_directory+"chars/"+char_name_ptr+"/input.xml";

    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode*input_file=doc->FirstChild("InputFile");

    for(TiXmlNode* nodo_input=input_file->FirstChild("Input");
            nodo_input!=NULL;
            nodo_input=nodo_input->NextSibling("Input"))
    {
        std::string move_name=(nodo_input->ToElement()->Attribute("move_name"));
        std::vector<std::string> lista_botones;
        for(TiXmlElement *elemento_boton=nodo_input->FirstChild("button")->ToElement();
                elemento_boton!=NULL;
                elemento_boton=elemento_boton->NextSiblingElement("button"))
        {
            std::string boton(elemento_boton->Attribute("value"));
            if(boton[0]=='*' && boton.size()>1)
            {
                boton[0]='1';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[0]='2';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[0]='3';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[0]='4';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[0]='6';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[0]='7';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[0]='8';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[0]='9';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[0]='5';
                std::string str_temp="";
                for(int i=1; i<(int)boton.size(); i++)
                    str_temp+=boton[i];
                lista_botones.clear();
                lista_botones.push_back(str_temp);
                agregarRosalilaInputs(lista_botones,move_name);
            }
            else if(boton[boton.size()-1]=='*' && boton.size()>1)
            {
                boton[boton.size()-1]='a';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[boton.size()-1]='b';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[boton.size()-1]='c';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[boton.size()-1]='d';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[boton.size()-1]='e';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[boton.size()-1]='f';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[boton.size()-1]='g';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                boton[boton.size()-1]='h';
                lista_botones.clear();
                lista_botones.push_back(boton);
                agregarRosalilaInputs(lista_botones,move_name);
                std::string str_temp="";
                for(int i=0; i<(int)boton.size()-1; i++)
                    str_temp+=boton[i];
                lista_botones.clear();
                lista_botones.push_back(str_temp);
                agregarRosalilaInputs(lista_botones,move_name);
            }
            else
            {
                lista_botones.push_back(boton);
            }
        }
        agregarRosalilaInputs(lista_botones,move_name);
    }
}

void Personaje::loadTriggers()
{
    writeLogLine("Loading triggers.xml");

    string xml_path=assets_directory+"chars/"+char_name_ptr+"/triggers.xml";

    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode*triggers_file=doc->FirstChild("TriggersFile");

    for(TiXmlNode* nodo=triggers_file->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        std::string nombre(elemento->Attribute("name"));
        for(TiXmlNode* nodo_condiciones=nodo->FirstChild("Trigger");
                nodo_condiciones!=NULL;
                nodo_condiciones=nodo_condiciones->NextSibling("Trigger"))
        {
            std::vector<Condicion*> condiciones_temp;
            if(nodo_condiciones->FirstChild("condition")!=NULL)
            {
                for(TiXmlElement *elemento_condicion=nodo_condiciones->FirstChild("condition")->ToElement();
                        elemento_condicion!=NULL;
                        elemento_condicion=elemento_condicion->NextSiblingElement("condition"))
                {
                    std::string exp_i(elemento_condicion->Attribute("left_exp"));
                    std::string op(elemento_condicion->Attribute("relational_op"));
                    std::string exp_d(elemento_condicion->Attribute("right_exp"));
                    bool es_entero=false;
                    if(enteros.find(exp_i)!=enteros.end())
                        es_entero=true;
                    std::string str_contrario(elemento_condicion->Attribute("to_opponent"));
                    bool contrario=(str_contrario=="yes");
                    if(es_entero)
                    {
                        condiciones_temp.push_back(new Condicion(exp_i,op,atoi(elemento_condicion->Attribute("right_exp")),contrario));
                    }
                    else
                    {
                        condiciones_temp.push_back(new Condicion(exp_i,op,exp_d,contrario));
                    }
                }
            }
            agregarCondicion(nombre,0,condiciones_temp);
        }
    }
}

void Personaje::loadSprites()
{
    writeLogLine("Loading sprites.xml");

    string xml_path=assets_directory+"chars/"+char_name_ptr+"/sprites.xml";

    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode*sprites_file=doc->FirstChild("SpritesFile");

    writeLogLine("Loading IgnoreColor.");

    TiXmlNode* ignore_color_node=sprites_file->FirstChild("IgnoreColor");
    Color* ignore_color=NULL;
    if(ignore_color_node!=NULL)
    {
        ignore_color=new Color(0,atoi(ignore_color_node->ToElement()->Attribute("red")),
                               atoi(ignore_color_node->ToElement()->Attribute("green")),
                               atoi(ignore_color_node->ToElement()->Attribute("blue")));
    }
    for(TiXmlNode* nodo=sprites_file->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        std::string nombre(elemento->Attribute("name"));

        writeLogLine("Loading "+nombre+".");

        if(nodo->FirstChild("Sprite")!=NULL)
        {
            for(TiXmlElement *e=nodo->FirstChild("Sprite")->ToElement();
                    e!=NULL;
                    e=e->NextSiblingElement("Sprite"))
            {
                int frame=atoi(e->Attribute("frame_number"))-1;
                std::string str_variable="current_image";
                std::string path(e->Attribute("path"));
                std::string dir("chars/");
                if(numero==1)
                    path=dir+char_name+"/sprites/"+path;
                else
                    path=dir+char_name+"/sprites_player2/"+path;
                double escala;
                e->QueryDoubleAttribute("scale",&escala);
                int alineacion_x=atoi(e->Attribute("align_x"));
                int alineacion_y=atoi(e->Attribute("align_y"));
                bool to_opponent=false;
                if(e->Attribute("to_opponent")!=NULL)
                {
                    to_opponent=strcmp(e->Attribute("to_opponent"),"yes")==0;
                }

                writeLogLine("Loading "+path+".");

                if(ignore_color==NULL)
                {
                    Image* texture=painter->getTexture(assets_directory+path);
                    textures.push_back(texture);
// paleta.paintTexture(texture);
                    agregarModificador(nombre,frame,str_variable,new Imagen(texture,escala,alineacion_x,alineacion_y),to_opponent);
// paleta.restoreTexture(texture);
                }
                else//!!IGNORE COLOR
                {
                    Image* texture=painter->getTexture(assets_directory+path);
                    textures.push_back(texture);
// paleta.paintTexture(texture);
                    agregarModificador(nombre,frame,str_variable,new Imagen(texture,escala,alineacion_x,alineacion_y),to_opponent);
// paleta.restoreTexture(texture);
// video::IImage* image = painter->driver->createImageFromFile(path);
//
// video::Image* texture = painter->driver->addTexture("test",image);
// textures.push_back(texture);
// painter->driver->makeColorKeyTexture(texture,ignore_color);
//
// paleta.paintTexture(texture);
// agregarModificador(nombre,frame,str_variable,Imagen(texture,escala,alineacion_x,alineacion_y),contrario);
                }
            }
        }
    }
}

void Personaje::loadHitboxes()
{
    writeLogLine("Loading hitboxes.xml");

    string xml_path=assets_directory+"chars/"+char_name_ptr+"/hitboxes.xml";

    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode*hitboxes_file=doc->FirstChild("HitboxesFile");

    for(TiXmlNode* nodo=hitboxes_file->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        std::string nombre(elemento->Attribute("name"));
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
                    std::vector <Hitbox*> hitbox;
                    std::string str_variable(e->Attribute("variable"));
                    std::string str_contrario(e->Attribute("to_opponent"));
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
                            hitbox.push_back(new Hitbox(x1,-y1,x2,-y2,0.0));
                        }
                    }
                    agregarModificador(nombre,frame,str_variable,hitbox,contrario);
                }
            }
        }

    }
}

void Personaje::loadSfx()
{
    writeLogLine("Loading sfx.xml");

    string xml_path=assets_directory+"chars/"+char_name_ptr+"/sfx.xml";

    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode*sfx_file=doc->FirstChild("SfxFile");

    for(TiXmlNode* nodo_sonido=sfx_file->FirstChild("Sound");
            nodo_sonido!=NULL;
            nodo_sonido=nodo_sonido->NextSibling("Sound"))
    {
        TiXmlElement* elemento_sonido=nodo_sonido->ToElement();
        std::string move(elemento_sonido->Attribute("move"));

        sonido->addSound(char_name+move,assets_directory+std::string("chars/")+
                         char_name+std::string("/sfx/")+std::string(elemento_sonido->Attribute("file")));
    }

}

void Personaje::loadAnimations()
{
    writeLogLine("Loading vfx.xml");

    string xml_path=assets_directory+"chars/"+char_name_ptr+"/vfx.xml";
    string files_path=assets_directory+"chars/"+char_name_ptr+"/sprites/";
    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;
    TiXmlNode*animations_file=doc->FirstChild("AnimationsFile");
    TiXmlNode *back=animations_file->FirstChild("Back");
    TiXmlNode *front=animations_file->FirstChild("Front");
    //Back
    for(TiXmlNode* nodo=back->FirstChild("Animation");
            nodo!=NULL;
            nodo=nodo->NextSibling("Animation"))
    {
        std::vector<Imagen*>i_temp;
        for(TiXmlNode* nodo_frame=nodo->FirstChild("Sprite");
                nodo_frame!=NULL;
                nodo_frame=nodo_frame->NextSibling("Sprite"))
        {
            TiXmlElement *elem_frame=nodo_frame->ToElement();
            Image *texture=painter->getTexture(files_path+elem_frame->Attribute("path"));
            i_temp.push_back(new Imagen(texture,
                                        (float)atoi(elem_frame->Attribute("scale")),
                                        atoi(elem_frame->Attribute("align_x")),
                                        atoi(elem_frame->Attribute("align_y"))));
        }
        TiXmlElement *elem_animation=nodo->ToElement();
        bool to_oponent=strcmp(elem_animation->Attribute("to_opponent"),"i")==0;
        std::string name=std::string(elem_animation->Attribute("name"));
        std::string pos_x=std::string(elem_animation->Attribute("position_x"));
        std::string pos_y=std::string(elem_animation->Attribute("position_y"));
        if(enteros.find(pos_x)==enteros.end())
        {
            pos_x=std::string("Animation.")+name+std::string(".x");
            setEntero(pos_x,atoi(elem_animation->Attribute("position_x")));
        }
        if(enteros.find(pos_y)==enteros.end())
        {
            pos_y=std::string("Animation.")+name+std::string(".y");
            setEntero(pos_y,atoi(elem_animation->Attribute("position_y")));
        }
        animaciones_back.push_back(new Animacion(name,
                                   i_temp,
                                   pos_x,
                                   pos_y,
                                   atoi(elem_animation->Attribute("duration")),
                                   to_oponent,
                                   strcmp(elem_animation->Attribute("use_camera"),"yes")==0
                                                )
                                  );
        setString(std::string("Animation.")+name,"off");
        setString(std::string("Animation.")+std::string(name+".isActive"),"false");

    }


    for(TiXmlNode* nodo=front->FirstChild("Animation");
            nodo!=NULL;
            nodo=nodo->NextSibling("Animation"))
    {
        std::vector<Imagen*>i_temp;
        for(TiXmlNode* nodo_frame=nodo->FirstChild("Sprite");
                nodo_frame!=NULL;
                nodo_frame=nodo_frame->NextSibling("Sprite"))
        {
            TiXmlElement *elem_frame=nodo_frame->ToElement();
            Image *texture=painter->getTexture(files_path+elem_frame->Attribute("path"));
            i_temp.push_back(new Imagen(texture,
                                        (float)atoi(elem_frame->Attribute("scale")),
                                        atoi(elem_frame->Attribute("align_x")),
                                        atoi(elem_frame->Attribute("align_y"))));
        }
        TiXmlElement *elem_animation=nodo->ToElement();
        bool to_oponent=strcmp(elem_animation->Attribute("to_opponent"),"i")==0;
        std::string name=std::string(elem_animation->Attribute("name"));
        std::string pos_x=std::string(elem_animation->Attribute("position_x"));
        std::string pos_y=std::string(elem_animation->Attribute("position_y"));
        if(enteros.find(pos_x)==enteros.end())
        {
            pos_x=std::string("Animation.")+name+std::string(".x");
            setEntero(pos_x,atoi(elem_animation->Attribute("position_x")));
        }
        if(enteros.find(pos_y)==enteros.end())
        {
            pos_y=std::string("Animation.")+name+std::string(".y");
            setEntero(pos_y,atoi(elem_animation->Attribute("position_y")));
        }
        animaciones_front.push_back(new Animacion(name,
                                    i_temp,
                                    pos_x,
                                    pos_y,
                                    atoi(elem_animation->Attribute("duration")),
                                    to_oponent,
                                    strcmp(elem_animation->Attribute("use_camera"),"yes")==0
                                                 )
                                   );
        setString(std::string("Animation.")+name,"off");
        setString(std::string("Animation.")+std::string(name+".isActive"),"false");
    }
}

void Personaje::loadProjectiles()
{
    writeLogLine("Loading projectiles.xml");

    string xml_path=assets_directory+"chars/"+char_name_ptr+"/projectiles.xml";

    TiXmlDocument doc_t(xml_path.c_str());

    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode*projectiles_file=doc->FirstChild("ProjectilesFile");

    if(projectiles_file->FirstChild("projectile")!=NULL)
        for(TiXmlElement *projectile_element=projectiles_file->FirstChild("projectile")->ToElement();
                projectile_element!=NULL;
                projectile_element=projectile_element->NextSiblingElement("projectile"))
        {
            std::string nombre(projectile_element->Attribute("name"));
            writeLogLine("Loading "+nombre);
            int posicion_x(atoi(projectile_element->Attribute("position_x")));
            int posicion_y(atoi(projectile_element->Attribute("position_y")));
            int speed_x(atoi(projectile_element->Attribute("speed_x")));
            int speed_y(atoi(projectile_element->Attribute("speed_y")));
            int damage(atoi(projectile_element->Attribute("damage")));
            int blockstun(atoi(projectile_element->Attribute("blockstun")));
            bool multihit=false;
            if(projectile_element->Attribute("multihit")!=NULL)
                multihit=strcmp(projectile_element->Attribute("multihit"),"yes")==0;

            setEntero(nombre+".position_x",0);
            setEntero(nombre+".position_y",0);

            setString(nombre+".state","");
            setString(nombre+".orientation","");

            //Sprites
            std::vector<Imagen*>sprites;
            TiXmlNode *temp=projectile_element->FirstChild("Sprites");
            if(temp!=NULL)
            {
                if(!temp->NoChildren())
                    for(TiXmlElement *elemento_sprite=temp->FirstChild("Sprite")->ToElement();
                            elemento_sprite!=NULL;
                            elemento_sprite=elemento_sprite->NextSiblingElement("Sprite"))
                    {
                        std::string path(elemento_sprite->Attribute("path"));
                        std::string dir("chars/");
                        path=dir+char_name+"/"+path;
                        int escala=atoi(elemento_sprite->Attribute("scale"));
                        int alineacion_x=atoi(elemento_sprite->Attribute("align_x"));
                        int alineacion_y=atoi(elemento_sprite->Attribute("align_y"));


                        Image* texture;
                        texture=painter->getTexture(assets_directory+path);
                        sprites.push_back(new Imagen(texture,escala,alineacion_x,alineacion_y));
                    }
            }

            //Proyectil listo
            Proyectil* proyectil=new Proyectil(nombre,nombre+".position_x",nombre+".position_y",nombre+".sprite",nombre+".hitboxes",nombre+".state",nombre+".orientation",sprites,damage,blockstun,multihit);

            //Frames
            std::string prefijo="Projectile.";
            int frames=atoi(projectile_element->Attribute("frames"));
            int frame_duration=atoi(projectile_element->Attribute("frame_duration"));

            for(int i=0; i<frames; i++)
            {
                proyectil->agregarFrame(frame_duration);
                proyectil->frames[i]->agregarModificador(speed_x,nombre+".position_x",true,false,true);
                proyectil->frames[i]->agregarModificador(-speed_y,nombre+".position_y",true,false,false);
//                    if(i==frames-1)
//                        proyectil->frames[i].agregarModificador(hitboxes,nombre+".hitboxes",false);
            }

            //Hitboxes
            std::vector<Hitbox*> hitboxes_vacia;
            setHitboxes(nombre+".hitboxes",hitboxes_vacia);
            for(TiXmlElement *elemento_hitboxes=projectile_element->FirstChild("Hitboxes")->ToElement();
                    elemento_hitboxes!=NULL;
                    elemento_hitboxes=elemento_hitboxes->NextSiblingElement("Hitboxes"))
            {
                int num_frame=atoi(elemento_hitboxes->Attribute("frame"));
                temp=elemento_hitboxes;
                std::vector<Hitbox*> hitboxes;
                if(!temp->NoChildren())
                    for(TiXmlElement *elemento_hb=temp->FirstChild("Hitbox")->ToElement();
                            elemento_hb!=NULL;
                            elemento_hb=elemento_hb->NextSiblingElement("Hitbox"))
                    {
                        int x1=atoi(elemento_hb->Attribute("x1"));
                        int y1=atoi(elemento_hb->Attribute("y1"));
                        int x2=atoi(elemento_hb->Attribute("x2"));
                        int y2=atoi(elemento_hb->Attribute("y2"));
                        hitboxes.push_back(new Hitbox(x1,-y1,x2,-y2,0.0));
                    }
                proyectil->frames[num_frame]->agregarModificador(hitboxes,nombre+".hitboxes",false);
            }

            //Modificadores
            proyectil->frames[0]->agregarModificador("off",nombre+".trigger",false);
            proyectil->frames[0]->agregarModificador("entero","position_x",nombre+".position_x",false,false,false);
            proyectil->frames[0]->agregarModificador(posicion_x,nombre+".position_x",true,false,true);
            proyectil->frames[0]->agregarModificador("entero","position_y",nombre+".position_y",false,false,false);
            proyectil->frames[0]->agregarModificador(-posicion_y,nombre+".position_y",true,false,false);

            //Triggers
            setString(nombre+".trigger","off");
            std::vector<Condicion*>cond_temp;
            cond_temp.push_back(new Condicion(nombre+".trigger","=","on",false));
            proyectil->agregarCondicion(cond_temp,0);

            //Listo
            agregarProyectil(proyectil);
        }

}

void Personaje::logicaProyectiles()
{
    //Agregar Proyectiles
    setString("projectile_active","no");
    for(int i=0; i<(int)proyectiles_actuales.size(); i++)
    {
        Proyectil*proyectil=proyectiles_actuales[i];
        if(cumpleCondiciones(proyectil->frames[0]->condiciones))//si cumple
        {
            if(proyectil->sprites.size()!=0)
                setImagen(proyectil->imagen,proyectil->sprites[0]);
            setString(proyectil->estado,"on");
            setString(proyectil->orientacion,getString("orientation"));
            proyectil->frame_actual=0;
            proyectil->sprite_actual=0;
            proyectil->tiempo_transcurrido=0;
        }
    }

    proyectiles_activos=0;
    for(int i=0; i<(int)proyectiles_actuales.size(); i++)
    {
        Proyectil* proyectil=proyectiles_actuales[i];

        if(getString(proyectil->estado)!=std::string("on"))
            continue;

        setString("projectile_active","yes");

        proyectiles_activos++;

        Frame* fc=proyectil->frames[proyectil->frame_actual];
        if(proyectil->tiempo_transcurrido==0)
        {
            aplicarModificadores(fc->modificadores,getString(proyectil->orientacion)=="i");
            if(proyectil->sprites.size()!=0)
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
        }
        else
            proyectil->tiempo_transcurrido++;
        //verificar fin de movimiento
        if(proyectil->frame_actual==(int)proyectil->frames.size())
        {
            proyectil->frame_actual=0;
            setString(proyectil->estado,"off");
        }
    }
}

void Personaje::aplicarEfectosProyectiles()
{
    bool pego=false;
    bool disolve=false;
    bool chip=false;

    for(int i=0; i<(int)proyectiles_actuales.size(); i++)
    {
        Proyectil* proyectil=proyectiles_actuales[i];
        if(getString(proyectil->estado)!=std::string("on"))
            continue;

        //hit
        bool hit=false;
        if(getColisionHitboxes(personaje_contrario->getHitboxes("blue"),
                               getHitboxes(proyectil->hitboxes),
                               personaje_contrario->getEntero("position_x"),
                               -personaje_contrario->getEntero("position_y"),
                               getEntero(proyectil->posicion_x),
                               getEntero(proyectil->posicion_y)))
        {
            hit=true;
        }

        //hit de proyectiles
        bool colision_proyectiles=false;
        Proyectil*proyectil_c;
        for(int j=0; j<(int)personaje_contrario->proyectiles_actuales.size(); j++)
        {
            proyectil_c=personaje_contrario->proyectiles_actuales[j];
            if(personaje_contrario->getString(proyectil_c->estado)!=std::string("on"))
                continue;

            if(getColisionHitboxes(personaje_contrario->getHitboxes(proyectil_c->hitboxes),
                                   getHitboxes(proyectil->hitboxes),
                                   personaje_contrario->getEntero(proyectil_c->posicion_x),
                                   personaje_contrario->getEntero(proyectil_c->posicion_y),
                                   getEntero(proyectil->posicion_x),
                                   getEntero(proyectil->posicion_y)))
            {
                colision_proyectiles=true;
                break;
            }
        }

        //acciones
        if(hit)
        {
            if(!proyectil->multihit)
            {
                proyectil->frame_actual=0;
                setString(proyectil->estado,"off");
            }
            setEntero("Colision.x",px_colision);
            setEntero("Colision.y",py_colision);
            if(personaje_contrario->getString("current_move").substr(0,8)!=std::string("defense."))//hit player
            {
                personaje_contrario->setEntero("hp.current_value",personaje_contrario->getEntero("hp.current_value")-proyectil->damage);
                pego=true;
            }
            else //hit defense
            {
                personaje_contrario->setEntero("blockstun.current_value",proyectil->blockstun);
                chip=true;
            }
        }
        else if(colision_proyectiles)
        {
            proyectil->frame_actual=0;
            setString(proyectil->estado,"off");
            setEntero("Colision.x",px_colision);
            setEntero("Colision.y",py_colision);

            proyectil_c->frame_actual=0;
            personaje_contrario->setString(proyectil_c->estado,"off");
            personaje_contrario->setEntero("Colision.x",px_colision);
            personaje_contrario->setEntero("Colision.y",py_colision);

            disolve=true;
        }
    }
    if(pego)
        personaje_contrario->setString("projectile_hit","yes");
    else
        personaje_contrario->setString("projectile_hit","no");
    if(disolve)
        personaje_contrario->setString("projectile_disolve","yes");
    else
        personaje_contrario->setString("projectile_disolve","no");
    if(chip)
        personaje_contrario->setString("projectile_disolve_chip","yes");
    else
        personaje_contrario->setString("projectile_disolve_chip","no");
}

bool Personaje::getColisionHitboxes(Hitbox* hb_azul,Hitbox* hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
{
/*
    int x1r=hb_roja->p1x+atacante_x;
    int y1r=hb_roja->p1y+atacante_y;
    int x2r=hb_roja->p2x+atacante_x;
    int y2r=hb_roja->p2y+atacante_y;

    int x1a=hb_azul->p1x+atacado_x;
    int y1a=hb_azul->p1y+atacado_y;
    int x2a=hb_azul->p2x+atacado_x;
    int y2a=hb_azul->p2y+atacado_y;

    Hitbox hb_azul_temp(x1r,y1r,x2r,y2r);
    Hitbox hb_roja_temp(x1a,y1a,x2a,y2a);

    bool hay_colision = collisionCheck(&hb_azul_temp,&hb_roja_temp);

    if(hay_colision)
    {
        int x1,x2,y1,y2;
        if(x1a>x1r)x1=x1a;
        else x1=x1r;
        if(x2a<x2r)x2=x2a;
        else x2=x2r;

        if(y1a>y1r)y1=y1a;
        else y1=y1r;
        if(y2a<y2r)y2=y2a;
        else y2=y2r;

        px_colision=x1+((x2-x1)/2);
        py_colision=y1+((y2-y1)/2);
    }
*/
    return false;
}

bool Personaje::getColisionHitboxes(vector<Hitbox*> hb_azules,vector<Hitbox*> hb_rojas,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
{
    for(int a=0; a<(int)hb_azules.size(); a++)
        for(int r=0; r<(int)hb_rojas.size(); r++)
            if(getColisionHitboxes(hb_azules[a],hb_rojas[r],atacado_x,atacado_y,atacante_x,atacante_y))
                return true;
    return false;
}

void Personaje::dibujarImagenCameraAlign(RosalilaGraphics* painter,Imagen* imagen,int posicion_x,int posicion_y)
{
    Image *texture=imagen->imagen;

    int pos_x=posicion_x+imagen->alineacion_x-(texture->getWidth()*imagen->escala)/2;
    int pos_y=posicion_y+imagen->alineacion_y-(texture->getHeight()*imagen->escala)/2+painter->screen_height-stage_piso;

    painter->draw2DImage
    (   texture,
        texture->getWidth(),texture->getHeight(),
        pos_x,pos_y,
        //irr::core::position2d<irr::f32>(posicion_x+imagen.alineacion_x-(texture->getOriginalSize().Width*imagen.escala)/2,posicion_y+imagen.alineacion_y-(texture->getOriginalSize().Height*imagen.escala)/2),
        imagen->escala,
        0.0,
        getString("orientation")!="d",
        0,0,
        Color(255,255,255,255),
        0,0,
        true,
        FlatShadow());
}
void Personaje::dibujarImagen(RosalilaGraphics* painter,Imagen* imagen,int posicion_x,int posicion_y)
{
    Image *texture=imagen->imagen;

    int pos_x=posicion_x+imagen->alineacion_x;
    int pos_y=posicion_y+imagen->alineacion_y;

    painter->draw2DImage
    (   texture,
        texture->getWidth(),texture->getHeight(),
        pos_x,pos_y,
        //irr::core::position2d<irr::f32>(posicion_x+imagen.alineacion_x-(texture->getOriginalSize().Width*imagen.escala)/2,posicion_y+imagen.alineacion_y-(texture->getOriginalSize().Height*imagen.escala)/2),
        imagen->escala,
        0.0,
        getString("orientation")!="d",
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow());
}
void Personaje::dibujarAnimacionesBack()
{
    for(int i=0; i<(int)animaciones_back.size(); i++)
    {
        if(getString(std::string(std::string("Animation.")+animaciones_back[i]->nombre))=="on")
        {
            animaciones_actuales_back.push_back(i);
            setString(std::string(std::string("Animation.")+animaciones_back[i]->nombre),"off");
            setString(std::string("Animation.")+std::string(animaciones_back[i]->nombre+".isActive"),"true");
        }
    }
    for(int i=0; i<(int)animaciones_actuales_back.size(); i++)
    {
        Animacion* animacion=animaciones_back[animaciones_actuales_back[i]];
        if(animacion->usa_camara)
        {
            if(animacion->posicion_y=="position_y")
            {
                dibujarImagenCameraAlign(painter,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),-getEntero(animacion->posicion_y));
            }
            else
            {
                dibujarImagenCameraAlign(painter,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),getEntero(animacion->posicion_y));
            }
        }
        else
        {
            if(animacion->posicion_y=="position_y")
            {
                dibujarImagen(painter,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),-getEntero(animacion->posicion_y));
            }
            else
            {
                dibujarImagen(painter,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),getEntero(animacion->posicion_y));
            }
        }

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
            animacion->imagen_actual=0;
            animacion->tiempo_transcurrido=0;
            setString(std::string("Animation.")+std::string(animacion->nombre+".isActive"),"false");
            animaciones_actuales_back.erase(animaciones_actuales_back.begin()+i);
        }
    }
}

void Personaje::dibujarAnimacionesFront()
{
    for(int i=0; i<(int)animaciones_front.size(); i++)
    {
        if(getString(std::string(std::string("Animation.")+animaciones_front[i]->nombre))=="on")
        {
            animaciones_actuales_front.push_back(i);
            setString(std::string(std::string("Animation.")+animaciones_front[i]->nombre),"off");
            setString(std::string("Animation.")+std::string(animaciones_front[i]->nombre+".isActive"),"true");
        }
    }
    for(int i=0; i<(int)animaciones_actuales_front.size(); i++)
    {
        Animacion* animacion=animaciones_front[animaciones_actuales_front[i]];
        if(animacion->usa_camara)
        {
            if(animacion->posicion_y=="position_y")
            {
                dibujarImagenCameraAlign(painter,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),-getEntero(animacion->posicion_y));
            }
            else
            {
                dibujarImagenCameraAlign(painter,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),getEntero(animacion->posicion_y));
            }
        }
        else
        {
            if(animacion->posicion_y=="position_y")
            {
                dibujarImagen(painter,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),-getEntero(animacion->posicion_y));
            }
            else
            {
                dibujarImagen(painter,animacion->sprites[animacion->imagen_actual],getEntero(animacion->posicion_x),getEntero(animacion->posicion_y));
            }
        }
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
            animacion->imagen_actual=0;
            animacion->tiempo_transcurrido=0;
            setString(std::string("Animation.")+std::string(animacion->nombre+".isActive"),"false");
            animaciones_actuales_front.erase(animaciones_actuales_front.begin()+i);
        }
    }
}

void Personaje::resetPersonaje()
{
    setString("projectile_disolve","no");
    setString("projectile_disolve_chip","no");
    setString("projectile_hit","no");

    setEntero("hp.current_value",getEntero("hp.max_value"));
    setEntero("position_x",0);
    setEntero("position_y",0);

    setString("effect.shadow","off");
    setString("effect.violet","off");
    setString("effect.red","off");
    setString("effect.green","off");
    setString("effect.blue","off");

    setString("attacking","no");

    setEntero("Colision.x",0);
    setEntero("Colision.y",0);

//    loadMain();
//
//    loadVars();
//
//    loadInputs();
//
//    loadTriggers();
//
//    loadHitboxes();
//
//    loadSfx();
//
//    loadAnimations();
}

void Personaje::flipLeft()
{
    setString("orientation","i");
}

void Personaje::flipRight()
{
    setString("orientation","d");
}

void Personaje::takeDamage(int damage)
{
    setEntero("hp.current_value",getEntero("hp.current_value")-damage);
}

void Personaje::heal(int hp)
{
    setEntero("hp.current_value",getEntero("hp.current_value")+hp);
    if(getEntero("hp.current_value")>getEntero("hp.max_value"))
        setEntero("hp.current_value",getEntero("hp.max_value"));
}
