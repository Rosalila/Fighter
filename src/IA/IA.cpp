#include "IA/IA.h"

IA::IA()
{
    automata=new Automata();
}

stringw IA::getInput()
{
    return automata->getNextInput();
}
