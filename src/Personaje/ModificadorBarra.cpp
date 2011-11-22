#include "Personaje/ModificadorBarra.h"

ModificadorBarra::ModificadorBarra(stringw variable,Barra modificador,bool aplicar_a_contrario)
{
    tipo="barra";
    this->variable=variable;
    this->modificador_barra=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
