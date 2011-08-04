#include "../include/Input.h"

Input::Input(int i,Receiver* receiver)
{
    this->receiver=receiver;
    tecla_arriba=true;
    tecla_arriba2=true;
    usando_joystick=false;

    for(int i=0;i<10;i++)
        buffer_inputs.push_back("5");

    teclas_cruz.push_back(irr::KEY_KEY_S);
    inputs[irr::KEY_KEY_S]="2";
    teclas_cruz.push_back(irr::KEY_KEY_A);
    inputs[irr::KEY_KEY_A]="4";
    teclas_cruz.push_back(irr::KEY_KEY_D);
    inputs[irr::KEY_KEY_D]="6";
    teclas_cruz.push_back(irr::KEY_KEY_W);
    inputs[irr::KEY_KEY_W]="8";

    teclas_botones.push_back(irr::KEY_KEY_U);
    inputs[irr::KEY_KEY_U]="a";
    teclas_botones.push_back(irr::KEY_KEY_I);
    inputs[irr::KEY_KEY_I]="b";
    teclas_botones.push_back(irr::KEY_KEY_J);
    inputs[irr::KEY_KEY_J]="c";
    teclas_botones.push_back(irr::KEY_KEY_K);
    inputs[irr::KEY_KEY_K]="d";
}

Input::Input(stringw str,Receiver* receiver)
{
    this->receiver=receiver;
    tecla_arriba=true;
    tecla_arriba2=true;
    usando_joystick=true;

    for(int i=0;i<10;i++)
        buffer_inputs.push_back("5");

    joystick_botones.push_back(0);
    inputs_joystick[0]="a";
    joystick_botones.push_back(1);
    inputs_joystick[1]="b";
    joystick_botones.push_back(2);
    inputs_joystick[2]="c";
    joystick_botones.push_back(3);
    inputs_joystick[3]="d";
}

Input::Input()
{
    receiver=new Receiver();
    tecla_arriba=true;
    tecla_arriba2=true;

    //inicio inputs
    teclas_cruz.push_back(irr::KEY_KEY_S);
    inputs[irr::KEY_KEY_S]="2";
    teclas_cruz.push_back(irr::KEY_KEY_A);
    inputs[irr::KEY_KEY_A]="4";
    teclas_cruz.push_back(irr::KEY_KEY_D);
    inputs[irr::KEY_KEY_D]="6";
    teclas_cruz.push_back(irr::KEY_KEY_W);
    inputs[irr::KEY_KEY_W]="8";

    teclas_botones.push_back(irr::KEY_KEY_U);
    inputs[irr::KEY_KEY_U]="a";
    teclas_botones.push_back(irr::KEY_KEY_I);
    inputs[irr::KEY_KEY_I]="b";
    teclas_botones.push_back(irr::KEY_KEY_J);
    inputs[irr::KEY_KEY_J]="c";
    teclas_botones.push_back(irr::KEY_KEY_K);
    inputs[irr::KEY_KEY_K]="d";


    joystick_botones.push_back(0);
    inputs_joystick[0]="a";
    joystick_botones.push_back(1);
    inputs_joystick[1]="b";
    joystick_botones.push_back(2);
    inputs_joystick[2]="c";
    joystick_botones.push_back(3);
    inputs_joystick[3]="d";


    //fin inputs
}

stringw Input::getInputJoystick()
{
    stringw input=getInputJoystickCruz()+getInputJoystickBotones();
    if(input=="")
        return "5";
    return input;
}

stringw Input::getInputJoystickCruz()
{
    stringw input="";
    f32 moveHorizontal;
    f32 moveVertical;
    const SEvent::SJoystickEvent & joystickData = receiver->GetJoystickState();
    moveHorizontal =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
    moveVertical =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;

    if(moveVertical<0)
        input+="2";
    if(moveHorizontal<0)
        input+="4";
    if(moveHorizontal>0)
        input+="6";
    if(moveVertical>0)
        input+="8";
    return input;
}

stringw Input::getInputJoystickBotones()
{
    const SEvent::SJoystickEvent & joystickData = receiver->GetJoystickState();
    stringw input="";
    if(tecla_arriba2)
    {
        tecla_arriba2=false;
        for(int i=0;i<(int)joystick_botones.size();i++)
            if(joystickData.IsButtonPressed(joystick_botones[i]))
                input+=inputs_joystick[joystick_botones[i]];
    }
    bool flag=false;
    for(int i=0;i<(int)joystick_botones.size();i++)
        if(joystickData.IsButtonPressed(joystick_botones[i]))
            flag=true;
    if(flag)
        tecla_arriba2=true;
    return input;
}

stringw Input::getInputKeyboardCruz()
{
    stringw input="";
    for(int i=0;i<(int)teclas_cruz.size();i++)
        if(receiver->IsKeyDown(teclas_cruz[i]))
            input+=inputs[teclas_cruz[i]];
    return input;
}

stringw Input::getInputKeyboardBotones()
{
    stringw input="";
    if(tecla_arriba)
    {
        tecla_arriba=false;
        for(int i=0;i<(int)teclas_botones.size();i++)
            if(receiver->IsKeyDown(teclas_botones[i]))
                input+=inputs[teclas_botones[i]];
    }
    bool flag=false;
    for(int i=0;i<(int)teclas_botones.size();i++)
        if(receiver->IsKeyDown(teclas_botones[i]))
            flag=true;
    if(flag)
        tecla_arriba=true;
    return input;
}

stringw Input::getInputKeyboard()
{
    stringw input=getInputKeyboardCruz()+getInputKeyboardBotones();
    if(input=="")
        return "5";
    return input;
}

stringw Input::getInputCruz()
{
    if(usando_joystick)
        return getInputJoystickCruz();
    return getInputKeyboardCruz();
}

stringw Input::getInputBotones()
{
    if(usando_joystick)
        return getInputJoystickBotones();
    return getInputKeyboardBotones();
}

stringw Input::getInput()
{
    stringw resultado;
    if(usando_joystick)
        resultado=getInputJoystick();
    else
        resultado=getInputKeyboard();
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

bool Receiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
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
