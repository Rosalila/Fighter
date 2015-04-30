#ifndef GAMEPLAYEDITOR_H
#define GAMEPLAYEDITOR_H

#include "../Rosalila/RosalilaUtility/RosalilaUtility.h"
#include "../Rosalila/TinyXml/tinyxml.h"
#include "../Rosalila/system.h"
#include<iostream>
#include<map>
#include<vector>
using namespace std;
class GameplayEditor
{
public:
    map<string,string> variables_values;
    vector<string> variables;
    GameplayEditor();

    //Hardcoded Mole
    string getHp();
    void setHp(int value, bool relative);

    string getSpeedBack();
    void setSpeedBack(int value, bool relative);

    string getSpeedForward();
    void setSpeedForward(int value, bool relative);

    string getDamageOverhead();
    void setDamageOverhead(int value, bool relative);

    string getDamageSlash();
    void setDamageSlash(int value, bool relative);

    string getDamageLow();
    void setDamageLow(int value, bool relative);

    string getChipDamageOverhead();
    void setChipDamageOverhead(int value, bool relative);

    string getChipDamageSlash();
    void setChipDamageSlash(int value, bool relative);

    string getChipDamageLow();
    void setChipDamageLow(int value, bool relative);

    string getBlockstunOverhead();
    void setBlockstunOverhead(int value, bool relative);

    string getBlockstunSlash();
    void setBlockstunSlash(int value, bool relative);

    string getBlockstunLow();
    void setBlockstunLow(int value, bool relative);

    string getHitstun();
    void setHitstun(int value, bool relative);
};

#endif
