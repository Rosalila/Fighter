#include "ModificadorHitboxes.h"

ModificadorHitboxes::ModificadorHitboxes(std::string variable,std::vector <HitBox*> modificador,bool aplicar_a_contrario)
{
    tipo="hitboxes";
    this->variable=variable;
    this->modificador_hitbox=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
