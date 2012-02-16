#include "Personaje/Personaje.h"

Personaje::Personaje(Grafico* grafico,Sonido* sonido,int numero)
{
    this->grafico=grafico;
    this->sonido=sonido;
    this->numero=numero;
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

void Personaje::dibujarBarras()
{
    for(int i=0;i<(int)barras.size();i++)
    {
        position2d<s32>punto1= barras[i].posicion.UpperLeftCorner;
        position2d<s32>punto2= barras[i].posicion.LowerRightCorner;
        float longitud_total=(float)punto2.X-(float)punto1.X;
        float longitud_actual=((float)longitud_total/getEntero(barras[i].valor_maximo))*(float)getEntero(barras[i].valor_actual);
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
        if(barras[i].imagen==NULL)
            grafico->draw2DRectangle(barras[i].color,core::rect<s32>(p1x,p1y,p2x,p2y));
        else
            grafico->draw2DImage
            (   barras[i].imagen,
                irr::core::dimension2d<irr::f32> (longitud_actual,altura),
                irr::core::rect<irr::f32>(0,0,barras[i].imagen->getOriginalSize().Width*((float)getEntero(barras[i].valor_actual)/(float)getEntero(barras[i].valor_maximo)),barras[i].imagen->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(p1x,p1y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                player2,
                false);
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
    //cout<<getEntero("hp_valor_actual")<<endl;
    input->actualizarBuffer(&strings,&personaje_contrario->strings);

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
    //Desde Xml
    //Abrir personaje.xml
    TiXmlDocument doc_t( archivo_xml );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    //for each Movimiento
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
                setEntero(nombre+".position_x",posicion_x);
                setEntero(nombre+".position_y",posicion_y);

                setString(nombre+".state","");
                setString(nombre+".orientacion","");

                vector<Imagen>sprites;

                TiXmlNode *temp=elemento_imagen->FirstChild("Sprites");
                for(TiXmlElement *elemento_sprite=temp->FirstChild("Sprite")->ToElement();
                        elemento_sprite!=NULL;
                        elemento_sprite=elemento_sprite->NextSiblingElement("Sprite"))
                {
                    stringw path(elemento_sprite->Attribute("path"));
                    stringw dir("chars/");
                    path=dir+path;
                    int escala=atoi(elemento_sprite->Attribute("scale"));
                    int alineacion_x=atoi(elemento_sprite->Attribute("align_x"));
                    int alineacion_y=atoi(elemento_sprite->Attribute("align_y"));
                    sprites.push_back(Imagen(grafico->getTexture(path),escala,alineacion_x,alineacion_y));
                }

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


                Proyectil* proyectil=new Proyectil(nombre,nombre+".position_x",nombre+".position_y",nombre+".sprite",nombre+".hitboxes",nombre+".state",nombre+".orientation",sprites);

                //agregar a inputs constantes
                stringw prefijo="Projectile.";
                int frames=atoi(elemento_imagen->Attribute("frames"));
                int frame_duration=atoi(elemento_imagen->Attribute("frame_duration"));

                //sets
                setString(nombre+".trigger","off");
                setString(nombre+".triggeri","off");

                for(int i=0;i<frames;i++)
                {
                    proyectil->agregarFrame(frame_duration);
                    proyectil->frames[i].agregarModificador(25,nombre+".position_x",true,false,true);
                }
                //modificadores
                proyectil->frames[0].agregarModificador("off",nombre+".trigger",false);
                proyectil->frames[0].agregarModificador("entero","posicion_x",nombre+".position_x",false,false,false);
                proyectil->frames[0].agregarModificador(125,nombre+".position_x",true,false,true);

                //triggers
                vector<Condicion*>cond_temp;
                cond_temp.push_back(new Condicion("hadouken.trigger","=","on",false));
                proyectil->agregarCondicion(cond_temp,0);

//                //agregarModificador("Projectile.hadouken",2,"hadouken.position_x",500,"yes","no");
//                for(int i=0;i<frames;i++)
//                {
//                    agregarFrame(prefijo+nombre+"i",frame_duration);
//                    agregarModificador(prefijo+nombre+"i",i,nombre+"i"+".position_x",25,true,false);
//                }

//                vector<stringw> lista_botones;
//                lista_botones.push_back("*");
                //agregarInput(lista_botones,stringw(prefijo+nombre));

                agregarProyectil(proyectil);
            }

            for(TiXmlElement *elemento_imagen=nodo->FirstChild("sprite")->ToElement();
                    elemento_imagen!=NULL;
                    elemento_imagen=elemento_imagen->NextSiblingElement("sprite"))
            {
                stringw variable(elemento_imagen->Attribute("variable"));
                stringw path(elemento_imagen->Attribute("path"));
                stringw dir("chars/");
                path=dir+path;
                int escala=atoi(elemento_imagen->Attribute("scale"));
                int alineacion_x=atoi(elemento_imagen->Attribute("align_x"));
                int alineacion_y=atoi(elemento_imagen->Attribute("align_y"));
                setImagen(variable,Imagen(grafico->getTexture(path),escala,alineacion_x,alineacion_y));
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

                if(imagen!=NULL)
                    agregarBarra(Barra(variable,variable+".max_value",variable+".current_value",variable+".periodic_modifier",variable+".period",video::SColor(alpha,r,g,b),core::rect<s32>(x1,y1,x2,y2),grafico->getTexture(imagen)));
//                else
//                    agregarBarra(Barra(variable,variable+".max_value",variable+".current_value",variable+".periodic_modifier",variable+".period",video::SColor(alpha,r,g,b),core::rect<s32>(x1,y1,x2,y2),NULL));
            }
    }
    for(TiXmlNode* nodo=doc->FirstChild("Move");
            nodo!=NULL;
            nodo=nodo->NextSibling("Move"))
    {
        TiXmlElement *elemento=nodo->ToElement();
        stringw nombre(elemento->Attribute("name"));
        //For each Input
        for(TiXmlNode* nodo_input=nodo->FirstChild("Input");
                nodo_input!=NULL;
                nodo_input=nodo_input->NextSibling("Input"))
        {
            vector<stringw> lista_botones;
            for(TiXmlElement *elemento_boton=nodo_input->FirstChild("button")->ToElement();
                    elemento_boton!=NULL;
                    elemento_boton=elemento_boton->NextSiblingElement("button"))
            {
                stringw boton(elemento_boton->Attribute("value"));
                lista_botones.push_back(boton);
            }
            agregarInput(lista_botones,nombre);
        }
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

                if(nodo_frame->FirstChild("Sprite")!=NULL)
                {
                    for(TiXmlElement *e=nodo_frame->FirstChild("Sprite")->ToElement();
                            e!=NULL;
                            e=e->NextSiblingElement("Sprite"))
                    {
                        stringw str_variable(e->Attribute("variable"));
                        stringw path(e->Attribute("path"));
                        stringw dir("chars/");
                        path=dir+path;
                        int escala=atoi(e->Attribute("scale"));
                        int alineacion_x=atoi(e->Attribute("align_x"));
                        int alineacion_y=atoi(e->Attribute("align_y"));
                        stringw str_contrario(e->Attribute("to_opponent"));
                        bool contrario=(str_contrario=="si");
                        agregarModificador(nombre,frame,str_variable,Imagen(grafico->getTexture(irr::io::path(path)),escala,alineacion_x,alineacion_y),contrario);
                    }
                }
//
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
    //For each Sound
    for(TiXmlNode* nodo_sonido=doc->FirstChild("Sound");
            nodo_sonido!=NULL;
            nodo_sonido=nodo_sonido->NextSibling("Sound"))
    {
        TiXmlElement* elemento_sonido=nodo_sonido->ToElement();
        stringw move(elemento_sonido->Attribute("move"));
        sonido->agregarSonido(move,elemento_sonido->Attribute("file"));
    }
}

void Personaje::cargarDesdeXML(int px,int py,Input* input,char* archivo_xml)
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

void Personaje::logicaProyectiles()
{
    for(int i=0;i<(int)proyectiles_actuales.size();i++)
    {
        Proyectil* proyectil=proyectiles_actuales[i];

        if(getString(proyectil->estado)!=stringw("on"))
            continue;

        setImagen(proyectil->imagen,proyectiles_actuales[i]->sprites[proyectiles_actuales[i]->sprite_actual]);

        Frame* fc=&proyectil->frames[proyectil->frame_actual];
        if(proyectil->tiempo_transcurrido==0)
        {
            aplicarModificadores(fc->modificadores,getString(proyectil->orientacion)=="i");
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
        //proyectiles_actuales[i]->avanzarFrame();
    }
}
