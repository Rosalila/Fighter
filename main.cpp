#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "include/Input.h"
#include "include/Fighter.h"

#include "include/TinyXml/tinyxml.h"
#include <iostream>
using namespace std;

class RyuXml : Personaje
{
public:
    TiXmlDocument abrirXml(char* archivo)
    {
        TiXmlDocument doc( archivo );
        doc.LoadFile();
        return doc;
    }

    void cargarDesdeXml(char* archivo_xml)
    {
        //Desde Xml
		//Abrir personaje.xml
		TiXmlDocument doc_t=abrirXml(archivo_xml);
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

    RyuXml(int px,int py,Grafico* grafico,Input* input,char* archivo_xml)
    {
        this->input=input;
        this->grafico=grafico;

        cargarDesdeXml(archivo_xml);

        setEntero("posicion_x",px);
        setEntero("posicion_y",py);

		TiXmlDocument doc_t=abrirXml(archivo_xml);
        TiXmlDocument *doc;
        doc=&doc_t;
		//for each Movimiento
		TiXmlNode *archivos=doc->FirstChild("Archivos");
		for(TiXmlNode* nodo=archivos->FirstChild("archivo");
                nodo!=NULL;
                nodo=nodo->NextSibling("archivo"))
        {
            char* str_archivo=(char*)nodo->ToElement()->Attribute("nombre");
            cargarDesdeXml(str_archivo);
        }
    }
};

class InputXml : Input
{
public:
    TiXmlDocument abrirXml(char* archivo)
    {
        TiXmlDocument doc( archivo );
        doc.LoadFile();
        return doc;
    }
    InputXml(int jugador,Receiver* receiver)
    {
		TiXmlDocument doc_t=abrirXml((char*)"config.xml");
        TiXmlDocument *doc;
        doc=&doc_t;

        vector<Boton> botones;
		for(TiXmlNode* input=doc->FirstChild("Input");
                input!=NULL;
                input=input->NextSibling("Input"))
        {
            if(jugador==atoi(input->ToElement()->Attribute("jugador")))
            {
                //Key
                if(strcmp("keyboard",input->ToElement()->Attribute("tipo"))==0)
                for(TiXmlNode* boton=input->FirstChild("boton");
                        boton!=NULL;
                        boton=boton->NextSibling("boton"))
                {
                    botones.push_back(Boton((irr::EKEY_CODE)boton->ToElement()->Attribute("input")[0],boton->ToElement()->Attribute("mapeo")));
                }
                //Joy
                if(strcmp("joystick",input->ToElement()->Attribute("tipo"))==0)
                for(TiXmlNode* boton=input->FirstChild("boton");
                        boton!=NULL;
                        boton=boton->NextSibling("boton"))
                {
                    int int_boton;
                    if(strcmp(boton->ToElement()->Attribute("input"),"up")==0)
                        int_boton=-8;
                    else if(strcmp(boton->ToElement()->Attribute("input"),"down")==0)
                        int_boton=-2;
                    else if(strcmp(boton->ToElement()->Attribute("input"),"left")==0)
                        int_boton=-4;
                    else if(strcmp(boton->ToElement()->Attribute("input"),"right")==0)
                        int_boton=-6;
                    else
                        int_boton=boton->ToElement()->Attribute("input")[0]-48;
                    botones.push_back(Boton(int_boton,input->ToElement()->Attribute("numero_joystick")[0]-48,boton->ToElement()->Attribute("mapeo")));
                }
            }
        }

        //Map
        this->receiver=receiver;
        tecla_arriba=true;
        for(int i=0;i<20;i++)
            buffer_inputs.push_back("5");
        for(int i=0;i<(int)botones.size();i++)
            if(botones[i].getMapeo()=="2" || botones[i].getMapeo()=="4" || botones[i].getMapeo()=="6" || botones[i].getMapeo()=="8")
                this->cruz.push_back(botones[i]);
            else
                this->botones.push_back(botones[i]);
    }
};
class StageXml:Stage
{
public:
    TiXmlDocument abrirXml(char* archivo)
    {
        TiXmlDocument doc( archivo );
        doc.LoadFile();
        return doc;
    }
    StageXml(Grafico* grafico,char* archivo)
    {
        this->grafico=grafico;

		TiXmlDocument doc_t=abrirXml((char*)archivo);
        TiXmlDocument *doc;
        doc=&doc_t;

        TiXmlNode *nodo_back=doc->FirstChild("Back");
        for(TiXmlNode* layer=nodo_back->FirstChild("layer");
                layer!=NULL;
                layer=layer->NextSibling("layer"))
        {
            back.push_back(grafico->getTexture(layer->ToElement()->Attribute("imagen")));
        }

        TiXmlNode *nodo_front=doc->FirstChild("Front");
        for(TiXmlNode* layer=nodo_front->FirstChild("layer");
                layer!=NULL;
                layer=layer->NextSibling("layer"))
        {
            front.push_back(grafico->getTexture(layer->ToElement()->Attribute("imagen")));
        }
    }
};
int main()
{
    Receiver* receiver=new Receiver();
    Input *inputa=(Input*)new InputXml(1,receiver);
    Input *inputb=(Input*)new InputXml(2,receiver);
    Grafico *grafico=new Grafico(receiver);
    Sonido *sonido = new Sonido();
    Stage *stage=(Stage*)new StageXml(grafico,(char*)"stages/Stage1/Stage1.xml");
    Personaje *pa=(Personaje*)new RyuXml(300,370,grafico,inputa,(char *)"chars/RyuSF2/RyuSF2.xml");
    Personaje *pb=(Personaje*)new RyuXml(524,370,grafico,inputb,(char *)"chars/RyuSF2/RyuSF2.xml");
    //Menu m(stage,pa,pb,sonido,grafico,receiver);
    //m.loopMenu();

    Fighter fighter(stage,pa,pb,grafico,sonido);
    return 0;
}
