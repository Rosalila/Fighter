#ifndef MODIFICADORPORVARRosalilaAIBLE_H
#define MODIFICADORPORVARRosalilaAIBLE_H

#include "Personaje/Modificador.h"

class ModificadorPorVariable : public Modificador
{
    public:
    ModificadorPorVariable(std::string tipo,std::string variable,std::string variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
};

#endif
