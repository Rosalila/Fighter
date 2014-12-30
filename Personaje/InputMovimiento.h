#ifndef INPUTMOVIMIENTO_H
#define INPUTMOVIMIENTO_H

#include <vector>
#include "../Rosalila/RosalilaGraphics/RosalilaGraphics.h"

class InputMovimiento
{
public:
    std::vector<std::string> input;
    std::string movimiento;
    InputMovimiento(std::vector<std::string> input,std::string movimiento);
};

#endif
