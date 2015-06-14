#ifndef INPUTEDITOR_H
#define INPUTEDITOR_H

#include "../Rosalila/RosalilaUtility/RosalilaUtility.h"
#include "../Rosalila/TinyXml/tinyxml.h"
#include "../Rosalila/system.h"
#include "../Rosalila/RosalilaInputs/RosalilaInputs.h"
#include<iostream>
#include<map>
#include<vector>
using namespace std;
class InputEditor
{
public:
    map<string,string> variables_values;
    vector<string> variables;
    InputEditor();

    void editKeyboardInput(string button,
                                    int player,RosalilaInputs* player_input,
                                    string action);
};

#endif
