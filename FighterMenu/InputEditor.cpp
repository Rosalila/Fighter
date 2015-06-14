#include "InputEditor.h"

InputEditor::InputEditor()
{

}

void InputEditor::editKeyboardInput(string button,
                                    int player,RosalilaInputs* player_input,
                                    string action)
{
//    if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Boton")
//    {
//        MenuBoton*mb=((MenuBoton*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
        if(player==1)
        {
            if(action=="Player1.KeyboardConfig:a")
            {
                player_input->editKeyboardInput(player,button,"a");
//                reloadInputs();
            }
            if(action=="Player1.KeyboardConfig:b")
            {
                player_input->editKeyboardInput(player,button,"b");
            }
            if(action=="Player1.KeyboardConfig:c")
            {
                player_input->editKeyboardInput(player,button,"c");
            }
        }
        if(player==2)
        {
            if(action=="Player2.KeyboardConfig:a")
            {
                player_input->editKeyboardInput(player,button,"a");
            }
            if(action=="Player2.KeyboardConfig:b")
            {
                player_input->editKeyboardInput(player,button,"b");
            }
            if(action=="Player2.KeyboardConfig:c")
            {
                player_input->editKeyboardInput(player,button,"c");
            }
        }
//    }
}
