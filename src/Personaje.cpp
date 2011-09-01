#include "../include/Personaje.h"

Personaje::Personaje(Barra hp,int px,int py,int a,stringw orientacion,Grafico* grafico)
{
    setImagen("imagen_personaje",Imagen(grafico->getTexture("resources/Personajes/Ryu/Sprites/mover/saltar/arriba/01.png"),1,100,100));
    this->grafico=grafico;
    strings["estado_posicion"]="";
    strings["movimiento_actual"]="";
    strings["orientacion"]="";
    enteros["tiempo_transcurrido"]=0;
    enteros["frame_actual_saltando"]=0;

    setString("estado_posicion","");
    setEntero("frame_actual_saltando",0);
    setEntero("tiempo_transcurrido",0);
    setString("orientacion",orientacion);
    setString("movimiento_actual","5");

    enteros["posicion_x"]=px;
    enteros["posicion_y"]=py;

    barras["hp"]=hp;

    vector<HitBox> hb_vacia;
    hitboxes["azules"]=hb_vacia;
    hitboxes["rojas"]=hb_vacia;

}

Personaje::Personaje()
{

}
//DIBUJAR
void Personaje::dibujar()
{
    if(getImagen("imagen_personaje").imagen==NULL)
        return;
    int dimension_x=getImagen("imagen_personaje").dimension_x;
    int dimension_y=getImagen("imagen_personaje").dimension_y;
    int alineacion_x=getImagen("imagen_personaje").alineacion_x;
    int alineacion_y=getImagen("imagen_personaje").alineacion_y;
    grafico->draw2DImage
    (   getImagen("imagen_personaje").imagen,
        irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
        irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
        irr::core::position2d<irr::f32>(getEntero("posicion_x")-(dimension_x*getImagen("imagen_personaje").escala/2)+alineacion_x,getEntero("posicion_y")-(dimension_y*getImagen("imagen_personaje").escala/2)+alineacion_y),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (getImagen("imagen_personaje").escala,getImagen("imagen_personaje").escala),
        true,
        irr::video::SColor(255,255,255,255),
        getString("orientacion")=="i",
        false);
}
void Personaje::dibujarHitBoxes(stringw variable,stringw path,bool izquierda)
{
    vector <HitBox> hitbox=getHitBoxes(variable);
    if(getString("orientacion")=="i")
    for(int i=0;i<(int)hitbox.size();i++)
    {
        int a=hitbox[i].p1x;
        int b=hitbox[i].p2x;
        hitbox[i].p1x=-b;
        hitbox[i].p2x=-a;
    }
    for(int i=0;i<(int)hitbox.size();i++)
    {
        if(variable=="azules")
            grafico->draw2DRectangle(irr::video::SColor(100,0,0,100),core::rect<s32>(getEntero("posicion_x")+hitbox[i].p1x,getEntero("posicion_y")+hitbox[i].p1y,getEntero("posicion_x")+hitbox[i].p2x,getEntero("posicion_y")+hitbox[i].p2y));
        else
            grafico->draw2DRectangle(irr::video::SColor(100,100,0,0),core::rect<s32>(getEntero("posicion_x")+hitbox[i].p1x,getEntero("posicion_y")+hitbox[i].p1y,getEntero("posicion_x")+hitbox[i].p2x,getEntero("posicion_y")+hitbox[i].p2y));
    }
}
void Personaje::dibujarBarra(stringw variable)
{
    Barra barra=getBarra(variable);
    position2d<s32>prueba= barra.posicion.UpperLeftCorner;
    position2d<s32>prueba2= barra.posicion.LowerRightCorner;
    int l=prueba2.X-prueba.X;
    int bx2=(getEntero(barra.valor_maximo)/l)*getEntero(barra.valor_actual);
    grafico->draw2DRectangle(barra.color,core::rect<s32>(prueba.X,prueba.Y,prueba.X+bx2,prueba2.Y));
}
//GETS shortcuts
Movimiento* Personaje::getMovimientoActual()
{
    return movimientos[getString("movimiento_actual")];
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
    return barras[variable];
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
void Personaje::setBarra(stringw variable,Barra valor)
{
    barras[variable]=valor;
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

void Personaje::agregarCondicion(stringw movimiento,int frame,vector<Condicion> condicion)
{
    ((Movimiento*)movimientos[movimiento])->agregarCondicion(condicion,frame);
}
void Personaje::agregarCondicion(stringw movimiento,int frame,int posicion,Condicion condicion)
{
    ((Movimiento*)movimientos[movimiento])->agregarCondicion(posicion,condicion,frame);
}
void Personaje::agregarMovimiento(stringw movimiento)
{
    movimientos[movimiento]=new Movimiento();
}
void Personaje::agregarFrame(stringw movimiento, int duracion)
{
    ((Movimiento*)movimientos[movimiento])->agregarFrame(duracion);
}
void Personaje::agregarModificador(stringw movimiento,int frame,Imagen modificador,stringw variable,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,int modificador,stringw variable,bool relativo,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,relativo,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,Barra modificador,stringw variable,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,vector <HitBox> modificador,stringw variable,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw modificador,stringw variable,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}

//Aplicares
void Personaje::aplicarModificador(ModificadorImagen* mi)
{
    if(mi->aplicar_a_contrario)
        personaje_contrario->setImagen(mi->variable,mi->modificador_imagen);
    else
        setImagen(mi->variable,mi->modificador_imagen);
}


void Personaje::aplicarModificador(ModificadorEntero* me)
{
    if(me->relativo)
        if(me->aplicar_a_contrario)
            personaje_contrario->setEntero(me->variable,me->modificador_entero+getEntero(me->variable));
        else
            setEntero(me->variable,me->modificador_entero+getEntero(me->variable));
    else
        if(me->aplicar_a_contrario)
            personaje_contrario->setEntero(me->variable,me->modificador_entero);
        else
            setEntero(me->variable,me->modificador_entero);
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
    vector<HitBox> hb=getHitBoxes("azules");
    for(int i=0;i<(int)hb.size();i++)
    {
        int a=hb[i].p1x;
        int b=hb[i].p2x;
        hb[i].p1x=-b;
        hb[i].p2x=-a;
    }
    setHitBoxes("azules",hb);

    hb=getHitBoxes("rojas");
    for(int i=0;i<(int)hb.size();i++)
    {
        int a=hb[i].p1x;
        int b=hb[i].p2x;
        hb[i].p1x=-b;
        hb[i].p2x=-a;
    }
    setHitBoxes("rojas",hb);
}

void Personaje::aplicarModificador(ModificadorHitboxes* mh)
{
    if(mh->aplicar_a_contrario)
        personaje_contrario->setHitBoxes(mh->variable,mh->modificador_hitbox);
    else
        setHitBoxes(mh->variable,mh->modificador_hitbox);
}

//Logica
bool Personaje::verificarFinDeMovimiento()
{
    if((int)getMovimientoActual()->frames.size()==getMovimientoActual()->frame_actual)
    {
        getMovimientoActual()->frame_actual=0;
        setString("movimiento_actual","5");
    }
    if(getString("movimiento_actual_continuo")!="")
    if((int)((Movimiento*)movimientos[getString("movimiento_actual_continuo")])->frames.size()==((Movimiento*)movimientos[getString("movimiento_actual_continuo")])->frame_actual)
    {
        ((Movimiento*)movimientos[getString("movimiento_actual_continuo")])->frame_actual=0;
        setString("movimiento_actual_continuo","");
    }
    return false;
}

bool Personaje::ejecutarMovimientosConstantes()
{
    for(int x=0;x<(int)inputs.size();x++)
    {
        if(inputs[x].input[0]=="*")
        {
            stringw movimiento=inputs[x].movimiento;
            vector<Condicion> condiciones;
            condiciones=((Movimiento*)movimientos[movimiento])->frames[0].condiciones[0];
            bool flag=true;
            for(int i=0;i<(int)condiciones.size();i++)
                if(!condiciones[i].comparar(getString(condiciones[i].variable)))
                    flag=false;
            if(flag)
            {
                if(getString("movimiento_actual_continuo")!="")
                    ((Movimiento*)movimientos[getString("movimiento_actual_continuo")])->frame_actual=0;
                setString("movimiento_actual_continuo",movimiento);
                return true;
            }
        }
    }
    return false;
}

bool Personaje::ejectuarCancel(stringw input)
{
    for(int x=0;x<(int)inputs.size();x++)
    {
        if(input==inputs[x].input[0])
        {
            stringw movimiento=inputs[x].movimiento;
            vector<Condicion> condiciones;
            condiciones=((Movimiento*)movimientos[movimiento])->frames[0].condiciones[0];
            bool flag=false;
            for(int i=0;i<(int)condiciones.size();i++)
                if(condiciones[i].personaje_contrario)
                {
                    if(condiciones[i].comparar(personaje_contrario->getString(condiciones[i].variable)))
                        flag=true;
                }else
                {
                    if(condiciones[i].comparar(getString(condiciones[i].variable)))
                        flag=true;
                }
            if(flag)
            {
                getMovimientoActual()->frame_actual=0;
                setString("movimiento_actual",movimiento);
                return true;
            }
        }
    }
    return false;
}

bool Personaje::aplicarModificadores()
{
    if(getEntero("tiempo_transcurrido")>getFrameActual().duracion)
    {
        Frame frame=getFrameActual();
        int frame_modificadores_size=frame.modificadores.size();
        for(int i=0;i<frame_modificadores_size;i++)
        {
            Modificador modificador=frame.modificadores[i];
            if(modificador.tipo=="imagen")
                aplicarModificador((ModificadorImagen*)&modificador);
            if(modificador.tipo=="entero")
                aplicarModificador((ModificadorEntero*)&modificador);
            if(modificador.tipo=="string")
                aplicarModificador((ModificadorString*)&modificador);
            if(modificador.tipo=="hitboxes")
                aplicarModificador((ModificadorHitboxes*)&modificador);
        }
        getMovimientoActual()->frame_actual++;
        setEntero("tiempo_transcurrido",0);
        return true;
    }
    return false;
}

bool Personaje::aplicarModificadoresConstantes()
{
    if(getString("movimiento_actual_continuo")!="")
    if(getEntero("tiempo_transcurrido_continuo")>((Movimiento*)movimientos[getString("movimiento_actual_continuo")])->getFrameActual().duracion)
    {
        Frame frame=((Movimiento*)movimientos[getString("movimiento_actual_continuo")])->getFrameActual();
        int frame_modificadores_size=frame.modificadores.size();
        for(int i=0;i<frame_modificadores_size;i++)
        {
            Modificador modificador=frame.modificadores[i];
            if(modificador.tipo=="imagen")
                aplicarModificador((ModificadorImagen*)&modificador);
            if(modificador.tipo=="entero")
                aplicarModificador((ModificadorEntero*)&modificador);
            if(modificador.tipo=="string")
                aplicarModificador((ModificadorString*)&modificador);
            if(modificador.tipo=="hitboxes")
                aplicarModificador((ModificadorHitboxes*)&modificador);
        }
        ((Movimiento*)movimientos[getString("movimiento_actual_continuo")])->frame_actual++;
        setEntero("tiempo_transcurrido_continuo",0);
        return true;
    }
    return false;
}
