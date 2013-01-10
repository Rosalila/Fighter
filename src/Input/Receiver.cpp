#include "Input/Receiver.h"

Receiver::Receiver()
{
//    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
//        KeyIsDown[i] = false;
      for (int i = 0; i <= KEY_KEY_CODES_COUNT; i++)
      {
         keyState[i] = UP;
      }

    for(int i = 0; i < 322; i++) { // init them all to false
       KEYS[i] = false;
    }

    for(int i = 0; i < max_joystick_inputs; i++) { // init them all to false
       JOYKEYS_player1[i] = false;
    }
    for(int i = 0; i < max_joystick_inputs; i++) { // init them all to false
       JOYKEYS_player2[i] = false;
    }

    joy_up_pressed_player_1=false;
    joy_down_pressed_player_1=false;
    joy_left_pressed_player_1=false;
    joy_right_pressed_player_1=false;
    joy_up_pressed_player_2=false;
    joy_down_pressed_player_2=false;
    joy_left_pressed_player_2=false;
    joy_right_pressed_player_2=false;


    SDL_EnableKeyRepeat(0,0);
}

bool Receiver::OnEvent(const SEvent& event)
{
    // Remember whether each key is down or up
//    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
//        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

      bool eventprocessed = false;

      //////////////////////////////
      // Keyboard Input Event
      //////////////////////////////

//if(event.EventType == EET_MOUSE_INPUT_EVENT)
//{
//    //if (id == 107)
//    //{
//        exit(0);
//    //}
//}


      if (event.EventType == EET_KEY_INPUT_EVENT)
      {
         if (processState == STARTED)
         {
            // if key is Pressed Down
            if (event.KeyInput.PressedDown == true)
            {
               // If key was not down before
               if (keyState[event.KeyInput.Key] != DOWN)
               {
                  keyState[event.KeyInput.Key] = PRESSED; // Set to Pressed
               }
               else
               {
                  // if key was down before
                  keyState[event.KeyInput.Key] = DOWN; // Set to Down
               }
            }
            else
            {

                  // if the key is down
                  if (keyState[event.KeyInput.Key] != UP)
                  {
                     keyState[event.KeyInput.Key] = RELEASED; // Set to Released
                  }
            }
         }


         eventprocessed = true;
      }
    //Joystick
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0)
    {
            JoystickState0 = event.JoystickEvent;
            eventprocessed = true;
    }
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 1)
    {
            JoystickState1 = event.JoystickEvent;
            eventprocessed = true;
    }
    return eventprocessed;
}

const SEvent::SJoystickEvent & Receiver::GetJoystickState(void) const
{
    if(joystick==0)
        return JoystickState0;
    if(joystick==1)
        return JoystickState1;
    return JoystickState0;;
}

//bool Receiver::IsKeyDown(EKEY_CODE keyCode) const
//{
//    return KeyIsDown[keyCode];
//}

bool Receiver::IsKeyPressed(int keycode)
{
  if(KEYS[keycode])
  {
      KEYS[keycode]=false;
      return true;
  }
  return false;
}

bool Receiver::IsKeyDownn(int keycode)
{
  if (keystates[keycode])
  {
     return true;
  }
  else
  {
     return false;
  }
}

bool Receiver::IsJoyDown(int joyCode,int joystick)
{
    if(joystick==0)
    {
        if(joyCode==-1)
            return joy_down_pressed_player_1 && joy_left_pressed_player_1;
        if(joyCode==-3)
            return joy_down_pressed_player_1 && joy_right_pressed_player_1;
        if(joyCode==-7)
            return joy_up_pressed_player_1 && joy_left_pressed_player_1;
        if(joyCode==-9)
            return joy_up_pressed_player_1 && joy_right_pressed_player_1;
        if(joyCode==-2)
            return joy_down_pressed_player_1;
        if(joyCode==-4)
            return joy_left_pressed_player_1;
        if(joyCode==-6)
            return joy_right_pressed_player_1;
        if(joyCode==-8)
            return joy_up_pressed_player_1;
        if(JOYKEYS_player1[joyCode])
        {
          JOYKEYS_player1[joyCode]=false;
          return true;
        }
        return false;
    }
    if(joystick==1)
    {
        if(joyCode==-1)
            return joy_down_pressed_player_2 && joy_left_pressed_player_2;
        if(joyCode==-3)
            return joy_down_pressed_player_2 && joy_right_pressed_player_2;
        if(joyCode==-7)
            return joy_up_pressed_player_2 && joy_left_pressed_player_2;
        if(joyCode==-9)
            return joy_up_pressed_player_2 && joy_right_pressed_player_2;
        if(joyCode==-2)
            return joy_down_pressed_player_2;
        if(joyCode==-4)
            return joy_left_pressed_player_2;
        if(joyCode==-6)
            return joy_right_pressed_player_2;
        if(joyCode==-8)
            return joy_up_pressed_player_2;
        if(JOYKEYS_player2[joyCode])
        {
          JOYKEYS_player2[joyCode]=false;
          return true;
        }
        return false;
    }
    return false;
//    this->joystick=joystick;
//    const SEvent::SJoystickEvent & joystickData = GetJoystickState();
//    moveHorizontal=(f32)GetJoystickState().Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
//    moveVertical=(f32)GetJoystickState().Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
//    if(moveVertical<0 && joyCode==-2)
//        return true;
//    if(moveHorizontal<0 && joyCode==-4)
//        return true;
//    if(moveHorizontal>0 && joyCode==-6)
//        return true;
//    if(moveVertical>0 && joyCode==-8)
//        return true;
//    if(joystickData.IsButtonPressed(joyCode))
//        return true;
//    return false;
}
       // This is used so that the Key States will not be changed during execution of your Main game loop.
       // Place this at the very START of your Main Loop
       void Receiver::endEventProcess()
       {
          processState = ENDED;
       }

       // This is used so that the Key States will not be changed during execution of your Main game loop.
       // Place this function at the END of your Main Loop.
       void Receiver::startEventProcess()
       {

          processState = STARTED;
          //Keyboard Key States
          for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
          {
             if (keyState[i] == RELEASED)
             {
                keyState[i] = UP;
             }

             if (keyState[i] == PRESSED)
             {
                keyState[i] = DOWN;
             }
          }

       }

void Receiver::updateInputs()
{
    //While there's events to handle
    SDL_Event event;
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            //Quit the program
            //quit = true;
        }
        if( event.type == SDL_KEYDOWN )
        {
            KEYS[event.key.keysym.sym] = true;
        }
        if( event.type == SDL_KEYUP )
        {
            KEYS[event.key.keysym.sym] = false;
        }
        if( event.type == SDL_JOYBUTTONDOWN )
        {
            for(int i=0;i<max_joystick_inputs;i++)
            {
                if ( event.jbutton.button == i )
                {
                    if(event.jbutton.which==0)
                        JOYKEYS_player1[i]=true;
                }else
                {
                    JOYKEYS_player1[i]=false;
                }
            }
            for(int i=0;i<max_joystick_inputs;i++)
            {
                if ( event.jbutton.button == i )
                {
                    if(event.jbutton.which==1)
                        JOYKEYS_player2[i]=true;
                }else
                {
                    JOYKEYS_player2[i]=false;
                }
            }
        }
        if( event.type == SDL_JOYAXISMOTION )
        {
            //If joystick 0 has moved
            if( event.jaxis.which == 0 )
            {
                if( event.jaxis.axis == 0 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_left_pressed_player_1=false;
                        joy_right_pressed_player_1=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_left_pressed_player_1=true;
                        }
                        else
                        {
                            joy_right_pressed_player_1=true;
                        }
                    }
                }
                //If the Y axis changed
                else if( event.jaxis.axis == 1 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_up_pressed_player_1=false;
                        joy_down_pressed_player_1=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_up_pressed_player_1=true;
                        }
                        else
                        {
                            joy_down_pressed_player_1=true;
                        }
                    }
                }
            }




            if( event.jaxis.which == 1 )
            {
                if( event.jaxis.axis == 0 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_left_pressed_player_2=false;
                        joy_right_pressed_player_2=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_left_pressed_player_2=true;
                            joy_right_pressed_player_2=false;
                        }
                        else
                        {
                            joy_left_pressed_player_2=false;
                            joy_right_pressed_player_2=true;
                        }
                    }
                }
                //If the Y axis changed
                else if( event.jaxis.axis == 1 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_up_pressed_player_2=false;
                        joy_down_pressed_player_2=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_up_pressed_player_2=true;
                            joy_down_pressed_player_2=false;
                        }
                        else
                        {
                            joy_up_pressed_player_2=false;
                            joy_down_pressed_player_2=true;
                        }
                    }
                }
            }



        }
    }
    keystates = SDL_GetKeyState( NULL );
}
