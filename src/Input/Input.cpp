#include "Input/Input.h"
#include <sstream>

void Input::actualizarBuffer(irr::core::map<stringw,stringw>*strings,
                             irr::core::map<stringw,stringw>*strings_contrario,
                             irr::core::map<stringw,int>*enteros,
                             irr::core::map<stringw,int>*enteros_contrario
                             )
{
    stringw resultado="";
    if(!inteligencia_artificial)
    {
        for(int i=0;i<(int)cruz.size();i++)
            if(cruz[i].estaPresionado())
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
                if(botones[i].estaPresionado())
                    resultado+=botones[i].getMapeo();
        }
        bool flag=false;
        for(int i=0;i<(int)botones.size();i++)
            if(botones[i].estaPresionado())
                flag=true;
        if(!flag)
            tecla_arriba=true;
    }
    else
    {
        resultado=ia->getInput(strings,strings_contrario,enteros,enteros_contrario);
    }
    if(resultado=="")
        resultado="5";

    if(stringw(strings->operator[]("orientation"))==stringw("i"))
    {
        for(int i=0;i<(int)resultado.size();i++)
        {
            if(resultado[i]=='4')resultado[i]='6';
            else if(resultado[i]=='6')resultado[i]='4';
            else if(resultado[i]=='3')resultado[i]='1';
            else if(resultado[i]=='1')resultado[i]='3';
            else if(resultado[i]=='7')resultado[i]='9';
            else if(resultado[i]=='9')resultado[i]='7';
        }
    }
    buffer_inputs.insert(buffer_inputs.begin(),resultado);
    buffer_inputs.pop_back();
}

void Input::actualizarBuffer()
{
    stringw resultado="";

    for(int i=0;i<(int)cruz.size();i++)
        if(cruz[i].estaPresionado())
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
            if(botones[i].estaPresionado())
                resultado+=botones[i].getMapeo();
    }
    bool flag=false;
    for(int i=0;i<(int)botones.size();i++)
        if(botones[i].estaPresionado())
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

std::string stringw_to_stdstring(irr::core::stringw sw)
{
    std::stringstream ss;
        ss << sw.c_str();
        return ss.str();
}


void Input::cargarDesdeXML(int jugador,Receiver* receiver)
{
    this->jugador=jugador;
    this->receiver=receiver;
    this->inteligencia_artificial=false;
    TiXmlDocument doc_t((char*)"misc/inputs.xml");
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    vector<Boton> botones;
    for(TiXmlNode* input=doc->FirstChild("Input");
            input!=NULL;
            input=input->NextSibling("Input"))
    {
        if(jugador==atoi(input->ToElement()->Attribute("player")))
        {
            //Key
            if(strcmp("keyboard",input->ToElement()->Attribute("type"))==0)
            {
                for(TiXmlNode* boton=input->FirstChild("button");
                        boton!=NULL;
                        boton=boton->NextSibling("button"))
                {
                    botones.push_back(Boton(receiver,(irr::EKEY_CODE)boton->ToElement()->Attribute("input")[0],stringw(boton->ToElement()->Attribute("map"))));
                }
            }
            //Joy
            if(strcmp("joystick",input->ToElement()->Attribute("type"))==0)
            {
                for(TiXmlNode* boton=input->FirstChild("button");
                        boton!=NULL;
                        boton=boton->NextSibling("button"))
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
                    botones.push_back(Boton(receiver,int_boton,input->ToElement()->Attribute("joystick_number")[0]-48,boton->ToElement()->Attribute("map")));
                }
            }
        }
    }

    tecla_arriba=true;
    for(int i=0;i<20;i++)
        buffer_inputs.push_back("5");
    for(int i=0;i<(int)botones.size();i++)
    {
        if(botones[i].getMapeo()=="2" || botones[i].getMapeo()=="4" || botones[i].getMapeo()=="6" || botones[i].getMapeo()=="8")
        {
            this->cruz.push_back(botones[i]);
        }
        else
        {
            this->botones.push_back(botones[i]);
        }
    }
}

void Input::cargarIAXML(int jugador,char* archivo,char* archivo_default)
{
    this->jugador=jugador;
    this->inteligencia_artificial=true;
    tecla_arriba=true;
    for(int i=0;i<20;i++)
        buffer_inputs.push_back("5");
    ia=new IA(archivo,archivo_default);
}
TiXmlDocument* Input::getXML(TiXmlDocument *doc)
{
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc->LinkEndChild( decl );

	TiXmlElement * root = new TiXmlElement( "Input" );
	doc->LinkEndChild( root );
	root->SetDoubleAttribute("player",jugador);
	root->SetAttribute("type", "keyboard");

	for(int i=0;i<(int)botones.size();i++)
	{
	    if(botones[i].usaJoystick())
            continue;
        TiXmlElement * cxn = new TiXmlElement( "button" );
        root->LinkEndChild( cxn );
        cxn->SetAttribute("input", (char*)botones[i].getInput().c_str());
        cxn->SetAttribute("map", (char*)botones[i].getMapeo().c_str());
	}
	for(int i=0;i<(int)cruz.size();i++)
	{
	    if(cruz[i].usaJoystick())
            continue;
        TiXmlElement * cxn = new TiXmlElement( "button" );
        root->LinkEndChild( cxn );
        if(cruz[i].getInput()[0]=='d')
            cxn->SetAttribute("input", "down");
        else if(cruz[i].getInput()[0]=='l')
            cxn->SetAttribute("input", "left");
        else if(cruz[i].getInput()[0]=='r')
            cxn->SetAttribute("input", "right");
        else if(cruz[i].getInput()[0]=='u')
            cxn->SetAttribute("input", "up");
        else
            cxn->SetAttribute("input", (char*)cruz[i].getInput().c_str());
        cxn->SetAttribute("map", (char*)cruz[i].getMapeo().c_str());
	}


    //Joystick
	root = new TiXmlElement( "Input" );
	doc->LinkEndChild( root );
	root->SetDoubleAttribute("player",jugador);
	root->SetAttribute("type", "joystick");

	for(int i=0;i<(int)botones.size();i++)
	{
	    if(!botones[i].usaJoystick())
            continue;
        root->SetDoubleAttribute("joystick_number",botones[i].getNumJoystick());
        TiXmlElement * cxn = new TiXmlElement( "button" );
        root->LinkEndChild( cxn );
        cxn->SetAttribute("input", (char*)botones[i].getInput().c_str());
        cxn->SetAttribute("map", (char*)botones[i].getMapeo().c_str());
	}
	for(int i=0;i<(int)cruz.size();i++)
	{
	    if(!cruz[i].usaJoystick())
            continue;
        TiXmlElement * cxn = new TiXmlElement( "button" );
        root->LinkEndChild( cxn );
        if(cruz[i].getInput()[0]=='d')
            cxn->SetAttribute("input", "down");
        else if(cruz[i].getInput()[0]=='l')
            cxn->SetAttribute("input", "left");
        else if(cruz[i].getInput()[0]=='r')
            cxn->SetAttribute("input", "right");
        else if(cruz[i].getInput()[0]=='u')
            cxn->SetAttribute("input", "up");
        else
            cxn->SetAttribute("input", (char*)cruz[i].getInput().c_str());
        cxn->SetAttribute("map", (char*)cruz[i].getMapeo().c_str());
	}

	return doc;
	//doc->SaveFile( "appsettings.xml" );
}
