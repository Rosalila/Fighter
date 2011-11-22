#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

//#include "Input/Input.h"
#include "include/Fighter.h"

#include <iostream>
using namespace std;

int main()
{
    Fighter *fighter=new Fighter();
    fighter->mainLoop();
    return 0;
}
