#include "Personaje/Personaje.h"

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
        irr::core::position2d<irr::f32>(getEntero("posicion_x")-(dimension_x*getImagen("imagen_personaje").escala/2)+alineacion_x,getEntero("posicion_y")-(dimension_y*getImagen("imagen_personaje").escala/2)-alineacion_y),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (getImagen("imagen_personaje").escala,getImagen("imagen_personaje").escala),
        true,
        irr::video::SColor(255,255,255,255),
        getString("orientacion")=="i",
        false);
}
void Personaje::dibujarHitBoxes(stringw variable,stringw path,bool izquierda,int x,int y)
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
            grafico->draw2DRectangle(irr::video::SColor(100,0,0,100),core::rect<s32>(x+hitbox[i].p1x,y+hitbox[i].p1y,x+hitbox[i].p2x,y+hitbox[i].p2y));
        else
            grafico->draw2DRectangle(irr::video::SColor(100,100,0,0),core::rect<s32>(x+hitbox[i].p1x,y+hitbox[i].p1y,x+hitbox[i].p2x,y+hitbox[i].p2y));
    }
}

void Personaje::dibujarBarra(stringw variable,int alineacion_x,int alineacion_y)
{
    Barra barra=getBarra(variable);
    position2d<s32>prueba= barra.posicion.UpperLeftCorner;
    position2d<s32>prueba2= barra.posicion.LowerRightCorner;
    int l=prueba2.X-prueba.X;
    int bx2=(getEntero(barra.valor_maximo)/l)*getEntero(barra.valor_actual);
    //int alineacion_x=,alineacion_y=;
    grafico->draw2DRectangle(barra.color,core::rect<s32>(prueba.X+alineacion_x,prueba.Y+alineacion_y,prueba.X+bx2+alineacion_x,prueba2.Y+alineacion_y));
}

void Personaje::dibujarProyectiles()
{
    for(int i=0;i<(int)proyectiles_actuales.size();i++)
    {
        if(getString(proyectiles_actuales[i]->estado)!="activo")
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
        dibujarHitBoxes("hadouken hitboxes","resources/red.png",getString("hadouken orientacion")=="i",getEntero("hadouken posicion x"),getEntero("hadouken posicion y"));
    }
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
    movimientos[movimiento]=new Movimiento(movimiento);
}
void Personaje::agregarProyectil(stringw nombre,stringw posicion_x,stringw posicion_y,stringw imagen,stringw hitboxes,stringw estado,stringw orientacion)
{
    proyectiles_actuales.push_back(new Proyectil(nombre,posicion_x,posicion_y,imagen,hitboxes,estado,orientacion));
}
void Personaje::agregarFrame(stringw movimiento, int duracion)
{
    ((Movimiento*)movimientos[movimiento])->agregarFrame(duracion);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw variable,Imagen modificador,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(stringw movimiento,int frame,stringw variable,int modificador,bool relativo,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,variable,relativo,aplicar_a_contrario);
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
void Personaje::agregarModificador(stringw movimiento,int frame,stringw tipo,stringw variable,stringw variable_modificador,bool relativo,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(tipo,variable_modificador,variable,relativo,aplicar_a_contrario);
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
    {
        if(me->aplicar_a_contrario)
        {
            personaje_contrario->setEntero(me->variable,me->modificador_entero+personaje_contrario->getEntero(me->variable));
        }
        else
        {
            if(me->variable=="posicion_x" && getEntero(me->variable)-me->modificador_entero<80 && me->modificador_entero<0)
                return;
            if(me->variable=="posicion_x" && getEntero(me->variable)-me->modificador_entero>900 && me->modificador_entero>0)
                return;
            setEntero(me->variable,me->modificador_entero+getEntero(me->variable));
        }
    }
    else
    {
        if(me->aplicar_a_contrario)
        {
            personaje_contrario->setEntero(me->variable,me->modificador_entero);
        }
        else
        {
            setEntero(me->variable,me->modificador_entero);
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

void Personaje::aplicarModificador(ModificadorPorVariable* mv)
{
    if(mv->tipo_variable=="entero")
    {
        if(mv->relativo)
        {
            if(mv->aplicar_a_contrario)
                personaje_contrario->setEntero(mv->variable,personaje_contrario->getEntero(mv->modificador_string)+personaje_contrario->getEntero(mv->variable));
            else
                setEntero(mv->variable,getEntero(mv->modificador_string)+getEntero(mv->variable));
        }else
        {
            if(mv->aplicar_a_contrario)
                personaje_contrario->setEntero(mv->variable,personaje_contrario->getEntero(mv->modificador_string));
            else
                setEntero(mv->variable,getEntero(mv->modificador_string));
        }
    }
}

//Logica
stringw Personaje::mapInputToMovimiento()
{
    input->actualizarBuffer();
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
    Movimiento *movimiento=movimientos[str_movimiento];
    Frame *frame=&movimiento->frames[0];
    vector<vector<Condicion> > condiciones=frame->condiciones;
    for(int i=0;i<(int)condiciones.size();i++)
    {
        vector<Condicion> subcondiciones=condiciones[i];
        bool flag=true;
        for(int j=0;j<(int)subcondiciones.size();j++)
        {
            if(!cumpleCondicion(&subcondiciones[j]))
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
void Personaje::aplicarModificadores(vector<Modificador> modificadores)
{
    for(int i=0;i<(int)modificadores.size();i++)
    {
        Modificador modificador=modificadores[i];
        if(modificador.tipo=="imagen")
            aplicarModificador((ModificadorImagen*)&modificador);
        if(modificador.tipo=="entero")
            aplicarModificador((ModificadorEntero*)&modificador);
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
    //Desde Xml
    //Abrir personaje.xml
    TiXmlDocument doc_t( archivo_xml );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    //for each Movimiento
    for(TiXmlNode* nodo=doc->FirstChild("Declaraciones");
            nodo!=NULL;
            nodo=nodo->NextSibling("Declaraciones"))
    {
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("imagen")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("imagen"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                stringw path(elemento_imagen->Attribute("path"));
                stringw dir("chars/");
                path=dir+path;
                int escala=atoi(elemento_imagen->Attribute("escala"));
                int alineacion_x=atoi(elemento_imagen->Attribute("alineacion_x"));
                int alineacion_y=atoi(elemento_imagen->Attribute("alineacion_y"));
                setImagen(variable,Imagen(grafico->getTexture(path),escala,alineacion_x,alineacion_y));
            }
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("cadena")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("cadena"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                stringw valor(elemento_imagen->Attribute("valor"));
                setString(variable,valor);
            }
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("entero")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("entero"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                int valor=atoi(elemento_imagen->Attribute("valor"));
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
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("proyectil")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("proyectil"))
            {
                stringw nombre(elemento_imagen->Attribute("nombre"));
                stringw posicion_x(elemento_imagen->Attribute("posicion_x"));
                stringw posicion_y(elemento_imagen->Attribute("posicion_y"));
                stringw imagen(elemento_imagen->Attribute("imagen"));
                stringw hitboxes(elemento_imagen->Attribute("hitboxes"));
                stringw estado(elemento_imagen->Attribute("estado"));
                stringw orientacion(elemento_imagen->Attribute("orientacion"));
                agregarProyectil(nombre,posicion_x,posicion_y,imagen,hitboxes,estado,orientacion);
            }
            for(TiXmlElement *elemento_imagen=nodo->FirstChild("barra")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("barra"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                stringw valor_maximo(elemento_imagen->Attribute("valor_maximo"));
                stringw valor_actual(elemento_imagen->Attribute("valor_actual"));
                stringw modificador_periodico(elemento_imagen->Attribute("modificador_periodico"));
                stringw periodo(elemento_imagen->Attribute("periodico"));
                int alpha=atoi(elemento_imagen->Attribute("alpha"));
                int r=atoi(elemento_imagen->Attribute("r"));
                int g=atoi(elemento_imagen->Attribute("g"));
                int b=atoi(elemento_imagen->Attribute("b"));
                int x1=atoi(elemento_imagen->Attribute("x1"));
                int y1=atoi(elemento_imagen->Attribute("y1"));
                int x2=atoi(elemento_imagen->Attribute("x2"));
                int y2=atoi(elemento_imagen->Attribute("y2"));
                setBarra(variable,Barra(valor_maximo,valor_actual,modificador_periodico,periodo,video::SColor(alpha,r,g,b),core::rect<s32>(x1,y1,x2,y2),NULL));
            }
    }
    for(TiXmlNode* nodo=doc->FirstChild("Movimiento");
            nodo!=NULL;
            nodo=nodo->NextSibling("Movimiento"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        stringw nombre(elemento->Attribute("nombre"));
        if(movimientos.find(nombre)==0)
            agregarMovimiento(nombre);
        //For each Input
        for(TiXmlNode* nodo_input=nodo->FirstChild("Input");
                nodo_input!=NULL;
                nodo_input=nodo_input->NextSibling("Input"))
        {
            vector<stringw> lista_botones;
            for(TiXmlElement *elemento_boton=nodo_input->FirstChild("boton")->ToElement();
                    elemento_boton!=NULL;
                    elemento_boton=elemento_boton->NextSiblingElement("boton"))
            {
                stringw boton(elemento_boton->Attribute("valor"));
                lista_botones.push_back(boton);
            }
            agregarInput(lista_botones,nombre);
        }
        //For each Frame
        int frame=0;
        for(TiXmlNode* nodo_frame=nodo->FirstChild("Frame");
                nodo_frame!=NULL;
                nodo_frame=nodo_frame->NextSibling("Frame"))
        {
            TiXmlElement *elemento_frame=nodo_frame->ToElement();
            if((int)((Movimiento*)movimientos[nombre])->frames.size()<=frame)
                agregarFrame(nombre,atoi(elemento_frame->Attribute("duracion")));
            //For each Modificador
            if(!nodo_frame->NoChildren())
            {
                for(TiXmlElement *elemento_modificador=nodo_frame->FirstChild("Modificador")->ToElement();
                        elemento_modificador!=NULL;
                        elemento_modificador=elemento_modificador->NextSiblingElement("Modificador"))
                {
                    stringw tipo(elemento_modificador->Attribute("tipo"));
                    if(tipo=="Entero")
                    {
                        stringw str_variable(elemento_modificador->Attribute("variable"));
                        stringw str_contrario(elemento_modificador->Attribute("contrario"));
                        stringw str_relativo(elemento_modificador->Attribute("relativo"));
                        int valor=atoi(elemento_modificador->Attribute("valor"));
                        bool contrario=(str_contrario=="si");
                        bool relativo=(str_relativo=="si");
                        agregarModificador(nombre,frame,str_variable,valor,relativo,contrario);
                    }
                    if(tipo=="Cadena")
                    {
                        //agregarModificador("hadouken",3,"iniciar hadouken","activo",false);
                        stringw str_variable(elemento_modificador->Attribute("variable"));
                        stringw str_contrario(elemento_modificador->Attribute("contrario"));
                        stringw str_valor(elemento_modificador->Attribute("valor"));
                        bool contrario=(str_contrario=="si");
                        agregarModificador(nombre,frame,str_variable,str_valor,contrario);
                    }
                    if(tipo=="Hitbox")
                    {
                        vector <HitBox> hitbox;
                        stringw str_variable(elemento_modificador->Attribute("variable"));
                        stringw str_contrario(elemento_modificador->Attribute("contrario"));
                        bool contrario=(str_contrario=="si");
                        if(!elemento_modificador->NoChildren())
                        {
                            for(TiXmlElement *elemento_hitbox=elemento_modificador->FirstChild("Hitbox")->ToElement();
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
                    if(tipo=="Imagen")
                    {
                        stringw str_variable(elemento_modificador->Attribute("variable"));
                        stringw path(elemento_modificador->Attribute("path"));
                        stringw dir("chars/");
                        path=dir+path;
                        int escala=atoi(elemento_modificador->Attribute("escala"));
                        int alineacion_x=atoi(elemento_modificador->Attribute("alineacion_x"));
                        int alineacion_y=atoi(elemento_modificador->Attribute("alineacion_y"));
                        stringw str_contrario(elemento_modificador->Attribute("contrario"));
                        bool contrario=(str_contrario=="si");
                        agregarModificador(nombre,frame,str_variable,Imagen(grafico->getTexture(irr::io::path(path)),escala,alineacion_x,alineacion_y),contrario);
                    }
                    if(tipo=="Variable")
                    {
                        stringw str_tipo(elemento_modificador->Attribute("tipo_variable"));
                        stringw str_variable(elemento_modificador->Attribute("variable"));
                        stringw str_valor(elemento_modificador->Attribute("valor"));
                        stringw str_contrario(elemento_modificador->Attribute("contrario"));
                        stringw str_relativo(elemento_modificador->Attribute("relativo"));
                        bool contrario=(str_contrario=="si");
                        bool relativo=(str_relativo=="si");
                        agregarModificador(nombre,frame,str_tipo,str_variable,str_valor,relativo,contrario);
                    }
                }
            }
            frame++;
        }
        //For each Condiciones
        for(TiXmlNode* nodo_condiciones=nodo->FirstChild("Condiciones");
                nodo_condiciones!=NULL;
                nodo_condiciones=nodo_condiciones->NextSibling("Condiciones"))
        {
            vector<Condicion> condiciones;
            for(TiXmlElement *elemento_condicion=nodo_condiciones->FirstChild("condicion")->ToElement();
                    elemento_condicion!=NULL;
                    elemento_condicion=elemento_condicion->NextSiblingElement("condicion"))
            {
                stringw exp_i(elemento_condicion->Attribute("exp_izquierda"));
                stringw op(elemento_condicion->Attribute("op_relacional"));
                stringw exp_d(elemento_condicion->Attribute("exp_derecha"));
                stringw str_contrario(elemento_condicion->Attribute("contrario"));
                bool contrario=(str_contrario=="si");
                condiciones.push_back(Condicion(exp_i,op,exp_d,contrario));
            }
            agregarCondicion(nombre,0,condiciones);
        }
    }
}

void Personaje::cargarDesdeXML(int px,int py,Grafico* grafico,Input* input,char* archivo_xml)
{
    this->input=input;
    this->grafico=grafico;

    cargarArchivo(archivo_xml);

    setEntero("posicion_x",px);
    setEntero("posicion_y",py);

    TiXmlDocument doc_t( archivo_xml );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;
    //for each Movimiento
    TiXmlNode *archivos=doc->FirstChild("Archivos");
    for(TiXmlNode* nodo=archivos->FirstChild("archivo");
            nodo!=NULL;
            nodo=nodo->NextSibling("archivo"))
    {
        char* str_archivo=(char*)nodo->ToElement()->Attribute("nombre");
        cargarArchivo(str_archivo);
    }
}
