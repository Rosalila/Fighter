#include "IA/IA.h"

IA::IA()
{
}

string IA::getInput()
{
    int r=std::rand()%5;
    std::string arr[5];
    arr[0]="2";
    arr[1]="4";
    arr[2]="6";
    arr[3]="8";
    arr[4]="a";
    return arr[r];
}
