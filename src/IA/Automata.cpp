#include "IA/Automata.h"

Automata::Automata()
{
    estado_actual="S";
    estados["S"]=new Estado(vector<Transicion*>());
    cargarDesdeXML((char*)"chars/RyuSF2/ai.xml");
    transicion_a_recompenzar=NULL;
}

Estado* Automata::getEstadoInicial()
{
    return estados["S"];
}

stringw Automata::getNextInput(irr::core::map<stringw,stringw>*strings,irr::core::map<stringw,stringw>*strings_contrario)
{
    if(wait>0)
    {
        wait--;
        //transicion_a_recompenzar=NULL;
        return "5";
    }else
    {
        Estado* e=estados[estado_actual];
        Transicion* t=e->getNextTransicion(strings,strings_contrario);
        if(t->recompensable)
        {
            transicion_a_recompenzar=t;
        }
        estado_actual=t->getDestino();
        wait=t->getWait();
        return t->getInput();
    }
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
            Transicion *transicion;
            if(e_action->Attribute("rewardable")!=NULL)
                transicion=new Transicion(e_action->Attribute("input"),e_action->Attribute("destination"),strcmp(e_action->Attribute("rewardable"),"yes")==0);
            else
                transicion=new Transicion(e_action->Attribute("input"),e_action->Attribute("destination"),false);
            if(e_action->Attribute("reward")!=NULL)
                transicion->setRecompensa(atoi(e_action->Attribute("reward")));
            if(e_action->Attribute("wait")!=NULL)
                transicion->setWait(atoi(e_action->Attribute("wait")));




            if(e_action->FirstChild("condition")!=NULL)
            {
                for(TiXmlElement *elemento_condicion=e_action->FirstChild("condition")->ToElement();
                        elemento_condicion!=NULL;
                        elemento_condicion=elemento_condicion->NextSiblingElement("condition"))
                {
                    stringw exp_i(elemento_condicion->Attribute("left_exp"));
                    stringw op(elemento_condicion->Attribute("relational_op"));
                    stringw exp_d(elemento_condicion->Attribute("right_exp"));
                    stringw str_contrario(elemento_condicion->Attribute("to_opponent"));
                    bool contrario=(str_contrario=="yes");
                    transicion->agregarCondicion(Condicion2(exp_i,op,exp_d,contrario));
                }
            }


            transiciones.push_back(transicion);
        }
        estados[stringw(nodo->ToElement()->Attribute("name"))]=new Estado(transiciones);
    }
}
