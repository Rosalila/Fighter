#include "IA/Automata.h"
#include <cstdlib>
#include <iostream>

Automata::Automata()
{
    estado_actual="S";
    estados["S"]=new Estado(vector<Transicion*>());
    cargarDesdeXML((char*)"chars/RyuSF2/ai.xml");
}

Estado* Automata::getEstadoInicial()
{
    return estados["S"];
}

stringw Automata::getNextInput()
{
    Estado* e=estados[estado_actual];
    Transicion* t=e->getNextTransicion();
    estado_actual=t->getDestino();
    return t->getInput();
}

void Automata::cargarDesdeXML(char* archivo)
{
    TiXmlDocument doc_t(archivo);
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    for(TiXmlNode* nodo=doc->FirstChild("State");
            nodo!=NULL;
            nodo=nodo->NextSibling("State"))
    {
        vector<Transicion*> transiciones;
        for(TiXmlElement *e_action=nodo->FirstChild("Action")->ToElement();
                e_action!=NULL;
                e_action=e_action->NextSiblingElement("Action"))
        {
            transiciones.push_back(new Transicion(e_action->Attribute("input"),e_action->Attribute("destination")));
        }
        estados[stringw(nodo->ToElement()->Attribute("name"))]=new Estado(transiciones);
    }


//    vector<Transicion*> transiciones;
//    transiciones.push_back(new Transicion("h1","2"));
//    estados["S"]=new Estado(transiciones);
//
//    vector<Transicion*> transiciones2;
//    transiciones2.push_back(new Transicion("h2","6"));
//    estados["h1"]=new Estado(transiciones2);
//
//    vector<Transicion*> transiciones3;
//    transiciones3.push_back(new Transicion("S","6a"));
//    estados["h2"]=new Estado(transiciones3);
}
