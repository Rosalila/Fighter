#include "IA/IA.h"

IA::IA(char* archivo,char* archivo_default)
{
    automata=new Automata(archivo,archivo_default);
    //transicion_a_recompenzar=automata->getEstadoInicial()->transiciones[0];
}

stringw IA::getInput(irr::core::map<stringw,stringw>*strings,
                     irr::core::map<stringw,stringw>*strings_contrario,
                     irr::core::map<stringw,int>*enteros,
                     irr::core::map<stringw,int>*enteros_contrario
                     )
{
    stringw res=automata->getNextInput(strings,strings_contrario,enteros,enteros_contrario);
    transicion_a_recompenzar=automata->transicion_a_recompenzar;
    return res;
}

void IA::darRecompensa()
{
    if(transicion_a_recompenzar!=NULL)
    {
        transicion_a_recompenzar->setRecompensa(transicion_a_recompenzar->getRecompensa()+1);
        //cout<<(char*)transicion_a_recompenzar->getInput().c_str()<<transicion_a_recompenzar->getRecompensa()<<endl;
    }else
    {
        //cout<<"NULLL"<<endl;
    }
}

void IA::quitarRecompensa()
{
    if(transicion_a_recompenzar!=NULL)
    {
        transicion_a_recompenzar->setRecompensa(transicion_a_recompenzar->getRecompensa()-1);
        //cout<<(char*)transicion_a_recompenzar->getInput().c_str()<<transicion_a_recompenzar->getRecompensa()<<endl;
    }else
    {
        //cout<<"NULLL"<<endl;
    }
}
