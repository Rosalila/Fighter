#include "Input/Input.h"

Input::Input(vector<Boton> botones,Receiver* receiver)
{
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

void Input::actualizarBuffer()
{
    stringw resultado="";
    for(int i=0;i<(int)cruz.size();i++)
        if(cruz[i].estaPresionado(receiver))
            resultado+=cruz[i].getMapeo();
    if(resultado=="24" || resultado=="42")
        resultado="1";
    if(resultado=="26" || resultado=="62")
        resultado="3";
    if(resultado=="84" || resultado=="48")
        resultado="7";
    if(resultado=="68" || resultado=="86")
        resultado="9";
    if(tecla_arriba)
    {
        tecla_arriba=false;
        for(int i=0;i<(int)botones.size();i++)
            if(botones[i].estaPresionado(receiver))
                resultado+=botones[i].getMapeo();
    }
    bool flag=false;
    for(int i=0;i<(int)botones.size();i++)
        if(botones[i].estaPresionado(receiver))
            flag=true;
    if(!flag)
        tecla_arriba=true;
    if(resultado=="")
        resultado="5";
    buffer_inputs.insert(buffer_inputs.begin(),resultado);
    buffer_inputs.pop_back();
}

vector<stringw> Input::getBufferInputs()
{
    return buffer_inputs;
}

void Input::cargarDesdeXML(int jugador,Receiver* receiver)
{

    TiXmlDocument doc_t((char*)"config.xml");
    doc_t.LoadFile();
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
