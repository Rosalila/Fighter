#include "irrKlang/irrKlang.h"
using namespace irrklang;

class Reproduccion
{
public:
    Reproduccion(ISoundSource* source);
    ISound* sonido;
    ISoundSource* source;
};
