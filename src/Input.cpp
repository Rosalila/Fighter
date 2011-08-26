#include "../include/Input.h"

Input::Input(vector<Boton> botones,Receiver* receiver)
{
    this->receiver=receiver;
    tecla_arriba=true;
///
    std::string line; //this will contain the data read from the file
    ifstream myfile ("input"); //opening the file.
    bool teclado=true;
    if (myfile.is_open()) //if the file is open
    {
        while (! myfile.eof() ) //while the end of file is NOT reached
        {
            getline (myfile,line); //get one line from the file
            if(myfile.eof())
                break;
            //cout << line << endl; //and output it
            vector <std::string> paramentros;
            for(int i=0;i<line.length();i++)
            {
                std::string token="";
                for(;(line[i]>=65 && line[i]<=90)||(line[i]>=97 && line[i]<=122)||(line[i]>=48 && line[i]<=57);i++)
                    token+=line[i];
                if(token!="")
                    paramentros.push_back(token);
            }
            cout<<"->";
            cout.flush();
            cout<<paramentros[0]<<"##"<<paramentros[1]<<endl;
            cout.flush();
            if(paramentros[0]=="joystick")
                teclado=false;
            else if (paramentros[0]=="keyboard")
                teclado=true;
            else
            {
                if(teclado)
                {
                    stringw str(paramentros[1].c_str());
                    botones.push_back(Boton((irr::EKEY_CODE)paramentros[0][0],str));
                }
                else
                {
                }
            }
        }
        myfile.close(); //closing the file
    }
    else
        cout << "Unable to open file"; //if the file is not open output <--
///
    for(int i=0;i<20;i++)
        buffer_inputs.push_back("5");
    for(int i=0;i<(int)botones.size();i++)
        if(botones[i].getMapeo()=="2" || botones[i].getMapeo()=="4" || botones[i].getMapeo()=="6" || botones[i].getMapeo()=="8")
            this->cruz.push_back(botones[i]);
        else
            this->botones.push_back(botones[i]);
}

stringw Input::getInput()
{
    stringw resultado="";
    for(int i=0;i<(int)cruz.size();i++)
        if(cruz[i].estaPresionado(receiver))
            resultado+=cruz[i].getMapeo();
    if(tecla_arriba)
    {
        tecla_arriba=false;
        for(int i=0;i<(int)botones.size();i++)
            if(botones[i].estaPresionado(receiver))
                resultado+=botones[i].getMapeo();
    }
    bool flag=false;
    for(int i=0;i<(int)botones.size();i++)
        if(botones[i].estaPresionado(receiver))
            flag=true;
    if(!flag)
        tecla_arriba=true;
    if(resultado=="")
        resultado="5";
    buffer_inputs.insert(buffer_inputs.begin(),resultado);
    buffer_inputs.pop_back();
    return resultado;
}

vector<stringw> Input::getBufferInputs()
{
    return buffer_inputs;
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

Receiver::Receiver()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

bool Receiver::OnEvent(const SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    //Joystick
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0)
    {
            JoystickState = event.JoystickEvent;
    }
    return false;
}

const SEvent::SJoystickEvent & Receiver::GetJoystickState(void) const
{
    return JoystickState;
}

bool Receiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool Receiver::IsJoyDown(int joyCode)
{
    const SEvent::SJoystickEvent & joystickData = GetJoystickState();
    moveHorizontal=(f32)JoystickState.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
    moveVertical=(f32)JoystickState.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
    if(moveVertical<0 && joyCode==-2)
        return true;
    if(moveHorizontal<0 && joyCode==-4)
        return true;
    if(moveHorizontal>0 && joyCode==-6)
        return true;
    if(moveVertical>0 && joyCode==-8)
        return true;
    if(joystickData.IsButtonPressed(joyCode))
        return true;
    return false;
}
