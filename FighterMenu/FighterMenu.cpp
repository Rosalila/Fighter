#include "FighterMenu.h"
Menu::Menu(RosalilaGraphics* painter,Receiver* receiver,Sound* sonido,std::string archivo)
{
    writeLogLine("loading menu: "+archivo);
    this->painter=painter;
    this->receiver=receiver;
    this->sonido=sonido;
    this->exit_signal=false;
    this->save_inputs_signal=false;
    this->char_select=NULL;
    this->player1_wins_count = 0;
    this->player2_wins_count = 0;

    vs_screen=painter->getTexture(assets_directory+"misc/vs_screen.png");

    string configxml_path=assets_directory+"config.xml";
    TiXmlDocument doc_t(configxml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    std::vector<std::string> chars,stages;
    for(TiXmlNode* node_chars=doc->FirstChild("Chars");
            node_chars!=NULL;
            node_chars=node_chars->NextSibling("Chars"))
    {
        for(TiXmlNode* node_chars2=node_chars->FirstChild("char");
                node_chars2!=NULL;
                node_chars2=node_chars2->NextSibling("char"))
        {
            chars.push_back(std::string(node_chars2->ToElement()->Attribute("nombre")));
        }
    }

    for(TiXmlNode* node_chars=doc->FirstChild("Stages");
            node_chars!=NULL;
            node_chars=node_chars->NextSibling("Stages"))
    {
        for(TiXmlNode* node_chars2=node_chars->FirstChild("stage");
                node_chars2!=NULL;
                node_chars2=node_chars2->NextSibling("stage"))
        {
            stages.push_back(std::string(node_chars2->ToElement()->Attribute("nombre")));
        }
    }

    cargarDesdeXml(archivo,chars,stages);

    writeLogLine("menu loaded: "+archivo);
}

void Menu::iniciarJuego(int num_personajes,bool inteligencia_artificial,bool is_training)
{
    writeLogLine("Initializing game.");
    if(inteligencia_artificial)
        char_select->lockPB(0);
    printVsScreen(char_select->getLockedPreviewsPA(),char_select->getLockedPreviewsPB());

    pa.clear();
    pb.clear();

    writeLogLine("Initializing stage.");

    stage=new Stage(painter,sonido);

    stage->loadFromXML(getStage());

    for(int i=0;i<num_personajes;i++)
    {
        Personaje* p1a=getPersonajeA(i,false);
        Personaje* p1b=getPersonajeB(i,inteligencia_artificial);
        p1a->personaje_contrario=p1b;
        p1b->personaje_contrario=p1a;
        pa.push_back(p1a);
        pb.push_back(p1b);
    }

    sonido->stopMusic();
    //sonido->playMusic(stage->music_path);
    Fighter*fighter=NULL;

    int pa_victories=0;
    int pb_victories=0;

    for(int current_round=0;;current_round++)
    {
        fighter = new Fighter(sonido,painter,receiver,pa,pb,stage,pa_victories,pb_victories,is_training,player1_wins_count,player2_wins_count);

        if(fighter->game_over_a && fighter->game_over_b)
        {
            pa_victories++;
            pb_victories++;
        }
        else if(fighter->game_over_a)
            pb_victories++;
        else if(fighter->game_over_b)
            pa_victories++;
        else//salir en el menu de pausa
        {
            delete fighter;
            fighter=NULL;
            break;
        }

        delete fighter;
        fighter=NULL;

        for(int i=0;i<num_personajes;i++)
        {
            Personaje* p1a=pa[i];
            Personaje* p1b=pb[i];
            p1a->resetPersonaje();
            p1b->resetPersonaje();
        }
        //Finish game
        if(pa_victories>=rounds && pb_victories>=rounds)
        {
            Menu *temp=new Menu(painter,receiver,sonido,assets_directory+"menu/draw.svg");
            temp->loopMenu();
            //reloadInputs();
            delete temp;
            break;
        }
        else if(pa_victories>=rounds)
        {
            Menu *temp=new Menu(painter,receiver,sonido,assets_directory+"menu/pa_wins.svg");
            temp->loopMenu();
            //reloadInputs();
            player1_wins_count++;
            //player2_wins_count=0;
            delete temp;
            break;
        }
        else if(pb_victories>=rounds)
        {
            Menu *temp=new Menu(painter,receiver,sonido,assets_directory+"menu/pb_wins.svg");
            temp->loopMenu();
            reloadInputs();
            player2_wins_count++;
            //player1_wins_count=0;
            delete temp;
            break;
        }
    }

    if(fighter!=NULL)
        delete fighter;

    for(int i=0;i<(int)pa.size();i++)
        delete pa[i];
    for(int i=0;i<(int)pb.size();i++)
        delete pb[i];

    delete stage;

    char_select->clearLocks();

    sonido->stopMusic();

    sonido->playMusic(assets_directory+"menu/audio/music.ogg");
}

void Menu::loopMenu()
{
    llenarInputsBotones();
    input_player1=new RosalilaInputs();
    input_player2=new RosalilaInputs();
    input_player1->loadFromXML(1,receiver);
    input_player2->loadFromXML(2,receiver);
    keyup_player1=false;
    keyup_player2=false;
    //inicio
    input_player1->limpiarBuffer();
    input_player2->limpiarBuffer();
    reloadInputs();

	for (;;)
	{
	    dibujarMenu();

	    applyGraphicEffects();

	    updateKeyUpCheck();

	    renderGallery();

	    characterSelectControl();

        if(receiver->isKeyPressed(SDLK_ESCAPE)
            || (input_player1->getBufferRosalilaInputs()[0]=="b" && keyup_player1)
            || (input_player2->getBufferRosalilaInputs()[0]=="b" && keyup_player2)
           )
        {
            bool is_input_config_menu=false;
            if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Boton")
            {
                MenuBoton*mb=((MenuBoton*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                if(mb->getAccion().size()>18
                   || mb->getAccion().substr(0,18)=="Player1.KeyConfig:"
                   || mb->getAccion().substr(0,18)=="Player2.KeyConfig:"
                   )
                {
                    is_input_config_menu=true;
                }
            }

            if(!is_input_config_menu)
            {
                sonido->playSound(std::string("Menu.back"));
                break;
            }
        }

        if(receiver->isKeyPressed(SDL_SCANCODE_DOWN)
            || (input_player1->getBufferRosalilaInputs()[0]=="2" && keyup_player1)
            || (input_player2->getBufferRosalilaInputs()[0]=="2" && keyup_player2)
           )
        {
            sonido->playSound(std::string("Menu.move"));
            ((MenuContenedor*)selectables_container)->avanzar();
            keyup_player1=false;
            keyup_player2=false;
        }
        else if(receiver->isKeyPressed(SDL_SCANCODE_UP)
            || (input_player1->getBufferRosalilaInputs()[0]=="8" && keyup_player1)
            || (input_player2->getBufferRosalilaInputs()[0]=="8" && keyup_player2)
                )
        {
            sonido->playSound(std::string("Menu.move"));
            ((MenuContenedor*)selectables_container)->retroceder();
            keyup_player1=false;
            keyup_player2=false;
        }
        else if(receiver->isKeyDown(SDL_SCANCODE_RIGHT)
                    || input_player1->getBufferRosalilaInputs()[0]=="6"
                    || input_player2->getBufferRosalilaInputs()[0]=="6"
                )
        {
            sonido->playSound(std::string("Menu.move"));
            if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Lista")
            {
                MenuLista* ml=((MenuLista*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                ml->avanzar();
            }
            if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Barra")
            {
                MenuBarra* mb=((MenuBarra*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                mb->avanzar();
                if(mb->getAccion()==0)
                {
                    ai_level=mb->actual;
                }
            }
        }
        else if(receiver->isKeyDown(SDL_SCANCODE_LEFT)
                    || input_player1->getBufferRosalilaInputs()[0]=="4"
                    || input_player2->getBufferRosalilaInputs()[0]=="4"
                )
        {
            sonido->playSound(std::string("Menu.move"));
            if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Lista")
            {
                MenuLista* ml=((MenuLista*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                ml->retroceder();
            }
            if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Barra")
            {
                MenuBarra* mb=((MenuBarra*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                mb->retroceder();
                if(mb->getAccion()==0)
                {
                    ai_level=mb->actual;
                }
            }
        }else if(receiver->isKeyPressed(SDLK_RETURN)
                    || (input_player1->getBufferRosalilaInputs()[0]=="a" && keyup_player1)
                    || (input_player2->getBufferRosalilaInputs()[0]=="a" && keyup_player2)
                 )
        {
            sonido->playSound(std::string("Menu.select"));
            if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Lista")
            {
                MenuLista*ml=((MenuLista*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                if(ml->getAccion()=="1v1")
                    if(char_select->listo())
                        iniciarJuego(1,false,false);//iniciarJuego(1,true);
                if(ml->getAccion()=="2v2")
                    if(char_select->listo())
                        iniciarJuego(2,false,false);
                if(ml->getAccion()=="3v3")
                    if(char_select->listo())
                        iniciarJuego(3,false,false);
                if(ml->getAccion()=="1v1-cpu")
                    if(char_select->listoPA())
                        iniciarJuego(1,true,false);
                if(ml->getAccion()=="2v2-cpu")
                    if(char_select->listoPA())
                        iniciarJuego(2,true,false);
                if(ml->getAccion()=="3v3-cpu")
                    if(char_select->listoPA())
                        iniciarJuego(3,true,false);

                if(ml->getAccion()=="1v1-training")
                    if(char_select->listo())
                        iniciarJuego(1,false,true);//iniciarJuego(1,true);
                if(ml->getAccion()=="2v2-training")
                    if(char_select->listo())
                        iniciarJuego(2,false,true);
                if(ml->getAccion()=="3v3-training")
                    if(char_select->listo())
                        iniciarJuego(3,false,true);
                if(ml->getAccion()=="1v1-cpu-training")
                    if(char_select->listoPA())
                        iniciarJuego(1,true,true);
                if(ml->getAccion()=="2v2-cpu-training")
                    if(char_select->listoPA())
                        iniciarJuego(2,true,true);
                if(ml->getAccion()=="3v3-cpu-training")
                    if(char_select->listoPA())
                        iniciarJuego(3,true,true);

                keyup_player1=false;
                keyup_player2=false;
            }
            if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Boton")
            {
                MenuBoton*mb=((MenuBoton*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                if(mb->getAccion()=="exit")
                {
                    exit_signal = true;
                    break;
                }
                if(mb->getAccion()=="resume")
                {
                    break;
                }
                if(mb->getAccion()=="quit")
                {
                    exit(0);
                    break;
                }
                if(mb->getAccion()=="load")
                {
                    Menu *temp=new Menu(painter,receiver,sonido,assets_directory+mb->load_menu);
                    temp->loopMenu();
                    keyup_player1=false;
                    keyup_player2=false;
                    reloadInputs();
                }
                if(mb->getAccion()=="save config")//save config
                {
                    TiXmlDocument *doc=new TiXmlDocument();
                    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
                    doc->LinkEndChild( decl );

                    TiXmlElement * root = new TiXmlElement("ConfigFile");
                    TiXmlElement * ai = new TiXmlElement("AILevel");
                    ai->SetDoubleAttribute("level",ai_level);
                    TiXmlElement * mt = new TiXmlElement("MatchTime");
                    mt->SetDoubleAttribute("seconds",time);
                    TiXmlElement * r = new TiXmlElement("Rounds");
                    r->SetDoubleAttribute("rounds",rounds);
                    root->LinkEndChild(ai);
                    root->LinkEndChild(mt);
                    root->LinkEndChild(r);
                    doc->LinkEndChild(root);

                    string miscconfigxml_path=assets_directory+"/misc/config.xml";
                    doc->SaveFile(miscconfigxml_path.c_str());
                }

                //Hp
                if(mb->getAccion()=="GameplayEdit.Mole.Hp:+10")
                {
                    gameplay_editor.setHp(10, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.Hp:-10")
                {
                    gameplay_editor.setHp(-10, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowHp")
                {
                    gameplay_editor.setHp(1000, false);
                    reloadInputs();
                }

                //SpeedForward
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedForward:-1")
                {
                    gameplay_editor.setSpeedForward(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedForward:+1")
                {
                    gameplay_editor.setSpeedForward(1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowSpeedForward")
                {
                    gameplay_editor.setSpeedForward(9, false);
                    reloadInputs();
                }

                //Speed Back
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedBack:-1")
                {
                    gameplay_editor.setSpeedBack(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedBack:+1")
                {
                    gameplay_editor.setSpeedBack(1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowSpeedBack")
                {
                    gameplay_editor.setSpeedBack(-9, false);
                    reloadInputs();
                }

                //Speed Overhead
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedOverhead:-1")
                {
                    gameplay_editor.setSpeedOverhead(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedOverhead:+1")
                {
                    gameplay_editor.setSpeedOverhead(1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowSpeedOverhead")
                {
                    gameplay_editor.setSpeedOverhead(6, false);
                    reloadInputs();
                }

                //Speed Slash
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedSlash:-1")
                {
                    gameplay_editor.setSpeedSlash(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedSlash:+1")
                {
                    gameplay_editor.setSpeedSlash(1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowSpeedSlash")
                {
                    gameplay_editor.setSpeedSlash(6, false);
                    reloadInputs();
                }

                //Speed Low
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedLow:-1")
                {
                    gameplay_editor.setSpeedLow(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.SpeedLow:+1")
                {
                    gameplay_editor.setSpeedLow(1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowSpeedLow")
                {
                    gameplay_editor.setSpeedLow(6, false);
                    reloadInputs();
                }

                //Damage overhead
                if(mb->getAccion()=="GameplayEdit.Mole.DamageOverhead:-1")
                {
                    gameplay_editor.setDamageOverhead(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.DamageOverhead:+1")
                {
                    gameplay_editor.setDamageOverhead(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowDamageOverhead")
                {
                    gameplay_editor.setDamageOverhead(80, false);
                    reloadInputs();
                }

                //Damage slash
                if(mb->getAccion()=="GameplayEdit.Mole.DamageSlash:-1")
                {
                    gameplay_editor.setDamageSlash(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.DamageSlash:+1")
                {
                    gameplay_editor.setDamageSlash(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowDamageSlash")
                {
                    gameplay_editor.setDamageSlash(80, false);
                    reloadInputs();
                }

                //Damage low
                if(mb->getAccion()=="GameplayEdit.Mole.DamageLow:-1")
                {
                    gameplay_editor.setDamageLow(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.DamageLow:+1")
                {
                    gameplay_editor.setDamageLow(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowDamageLow")
                {
                    gameplay_editor.setDamageLow(80, false);
                    reloadInputs();
                }

                //Chip damage overhead
                if(mb->getAccion()=="GameplayEdit.Mole.ChipDamageOverhead:-1")
                {
                    gameplay_editor.setChipDamageOverhead(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ChipDamageOverhead:+1")
                {
                    gameplay_editor.setChipDamageOverhead(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowChipDamageOverhead")
                {
                    gameplay_editor.setChipDamageOverhead(5, false);
                    reloadInputs();
                }

                //Chip damage slash
                if(mb->getAccion()=="GameplayEdit.Mole.ChipDamageSlash:-1")
                {
                    gameplay_editor.setChipDamageSlash(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ChipDamageSlash:+1")
                {
                    gameplay_editor.setChipDamageSlash(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowChipDamageSlash")
                {
                    gameplay_editor.setChipDamageSlash(5, false);
                    reloadInputs();
                }

                //Chip damage low
                if(mb->getAccion()=="GameplayEdit.Mole.ChipDamageLow:-1")
                {
                    gameplay_editor.setChipDamageLow(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ChipDamageLow:+1")
                {
                    gameplay_editor.setChipDamageLow(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowChipDamageLow")
                {
                    gameplay_editor.setChipDamageLow(5, false);
                    reloadInputs();
                }

                //Blockstun overhead
                if(mb->getAccion()=="GameplayEdit.Mole.BlockstunOverhead:-1")
                {
                    gameplay_editor.setBlockstunOverhead(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.BlockstunOverhead:+1")
                {
                    gameplay_editor.setBlockstunOverhead(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowBlockstunOverhead")
                {
                    gameplay_editor.setBlockstunOverhead(10, false);
                    reloadInputs();
                }

                //Blockstun slash
                if(mb->getAccion()=="GameplayEdit.Mole.BlockstunSlash:-1")
                {
                    gameplay_editor.setBlockstunSlash(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.BlockstunSlash:+1")
                {
                    gameplay_editor.setBlockstunSlash(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowBlockstunSlash")
                {
                    gameplay_editor.setBlockstunSlash(10, false);
                    reloadInputs();
                }

                //Blockstun low
                if(mb->getAccion()=="GameplayEdit.Mole.BlockstunLow:-1")
                {
                    gameplay_editor.setBlockstunLow(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.BlockstunLow:+1")
                {
                    gameplay_editor.setBlockstunLow(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowBlockstunLow")
                {
                    gameplay_editor.setBlockstunLow(6, false);
                    reloadInputs();
                }

                //Hitstun
                if(mb->getAccion()=="GameplayEdit.Mole.Hitstun:-1")
                {
                    gameplay_editor.setHitstun(-1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.Hitstun:+1")
                {
                    gameplay_editor.setHitstun(+1, true);
                    reloadInputs();
                }
                if(mb->getAccion()=="GameplayEdit.Mole.ShowHitstun")
                {
                    gameplay_editor.setHitstun(24, false);
                    reloadInputs();
                }
            }
        }
        editInputCheck();
	}
}

void Menu::dibujarMenu()
{
    for(int i=0;i<(int)elementos.size();i++)
        elementos[i]->dibujar();

    receiver->updateInputs();
    painter->updateScreen();
}

void Menu::cargarConfig()
{
    string miscconfigxml_path=assets_directory+"/misc/config.xml";
    TiXmlDocument doc_t(miscconfigxml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;
    TiXmlNode* node=doc->FirstChild("ConfigFile");
    TiXmlElement* ai_elem=node->FirstChild("AILevel")->ToElement();
    TiXmlElement* time_elem=node->FirstChild("MatchTime")->ToElement();
    TiXmlElement* rounds_elem=node->FirstChild("Rounds")->ToElement();

    ai_level=atoi(ai_elem->Attribute("level"));
    time=atoi(time_elem->Attribute("seconds"));
    rounds=atoi(rounds_elem->Attribute("rounds"));
}

void Menu::cargarDesdeXml(std::string archivo,vector<std::string> chars,vector<std::string> stages)
{
    music_path=assets_directory+"menu/audio/music.ogg";

    cargarConfig();

    TiXmlDocument doc_t(archivo.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    sonido->addSound("Menu.select",assets_directory+"menu/audio/select.ogg");
    sonido->addSound("Menu.select_char",assets_directory+"menu/audio/select_char.ogg");
    sonido->addSound("Menu.move",assets_directory+"menu/audio/move.ogg");
    sonido->addSound("Menu.move_char",assets_directory+"menu/audio/move_char.ogg");
    sonido->addSound("Menu.back",assets_directory+"menu/audio/back.ogg");

    TiXmlNode* elemento=doc->FirstChild("svg");
    TiXmlNode* g_node=elemento->FirstChild("g");

    writeLogLine("loading menu elements");

    std::vector<Elemento*>elementos_contenedor;
    for(TiXmlNode* image_node=g_node->FirstChild("image");
            image_node!=NULL;
            image_node=image_node->NextSibling("image"))
    {
        TiXmlElement* e=image_node->ToElement();

        if(e->Attribute("type")==NULL)
        {
            std::string path(e->Attribute("xlink:href"));

            std::string dir("menu/");
            path=dir+path;
            int displacement_x=0;
            int displacement_y=0;
            int stop_displacement_x_at=0;
            int stop_displacement_y_at=0;
            int fade_in_initial=-1;
            int fade_in_speed=0;

            if(e->Attribute("displacement_x")!=NULL)
                displacement_x=atoi(e->Attribute("displacement_x"));
            if(e->Attribute("displacement_y")!=NULL)
                displacement_y=atoi(e->Attribute("displacement_y"));
            if(e->Attribute("stop_displacement_x_at")!=NULL)
                stop_displacement_x_at=atoi(e->Attribute("stop_displacement_x_at"));
            if(e->Attribute("stop_displacement_y_at")!=NULL)
                stop_displacement_y_at=atoi(e->Attribute("stop_displacement_y_at"));
            if(e->Attribute("fade_in_initial")!=NULL)
                fade_in_initial=atoi(e->Attribute("fade_in_initial"));
            if(e->Attribute("fade_in_speed")!=NULL)
                fade_in_speed=atoi(e->Attribute("fade_in_speed"));
            Image* image=painter->getTexture(assets_directory+path);

            elementos.push_back((Elemento*)new MenuImagen(painter,atoi(e->Attribute("x")),atoi(e->Attribute("y")),displacement_x,displacement_y,stop_displacement_x_at,stop_displacement_y_at,fade_in_initial,fade_in_speed,
                                                          atoi(e->Attribute("width")),atoi(e->Attribute("height")),image,""
                                                          ));
        }else if(strcmp(e->Attribute("type"),"button")==0)
        {
            std::string action="";
            if(e->Attribute("action")!=NULL)
               action=e->Attribute("action");

            string menu_load="";
            if(action=="load")
            {
                menu_load="menu/";
                menu_load+=e->Attribute("load_menu");
            }

            int x=atoi(e->Attribute("x"));
            int y=atoi(e->Attribute("y"));
            int width=atoi(e->Attribute("width"));
            int height=atoi(e->Attribute("height"));
            std::string path=e->Attribute("xlink:href");

            int text_x=0;
            if(e->Attribute("text_x")!=NULL)
                text_x=atoi(e->Attribute("text_x"));

            int text_y=0;
            if(e->Attribute("text_y")!=NULL)
                text_y=atoi(e->Attribute("text_y"));

            std::string text="";
            if(e->Attribute("text")!=NULL)
                text=e->Attribute("text");

            std::string path_selected=path;
            if(e->Attribute("image_selected")!=NULL)
                path_selected=e->Attribute("image_selected");

            int text_x_selected=text_x;
            if(e->Attribute("text_x_selected")!=NULL)
                text_x_selected=atoi(e->Attribute("text_x_selected"));

            int text_y_selected=text_y;
            if(e->Attribute("text_y_selected")!=NULL)
                text_y_selected=atoi(e->Attribute("text_y_selected"));

            std::string text_selected=text;
            if(e->Attribute("text_selected")!=NULL)
                text_selected=e->Attribute("text_selected");


            elementos_contenedor.push_back((Elemento*)new MenuBoton(painter,
                                                                    x,y,
                                                                    width,height,
                                                                    painter->getTexture(assets_directory+"menu/"+path),
                                                                    text_x,text_y,text,
                                                                    painter->getTexture(assets_directory+"menu/"+path_selected),
                                                                    text_x_selected,text_y_selected,text_selected,
                                                                    action,menu_load
                                                                    ));

        }else if(strcmp(e->Attribute("type"),"bar")==0)
        {
            int accion=-1;
            int default_value=0;
            if(e->Attribute("default_value")!=NULL)
                atoi(e->Attribute("default_value"));
            if(e->Attribute("action")!=NULL)
            {
                if(strcmp(e->Attribute("action"),"AI level")==0)
                {
                    accion=0;
                    default_value=ai_level;
                }
                accion=atoi(e->Attribute("action"));
            }

            int x=atoi(e->Attribute("x"));
            int y=atoi(e->Attribute("y"));
            int width=atoi(e->Attribute("width"));
            int height=atoi(e->Attribute("height"));

            std::string path(e->Attribute("xlink:href"));

            std::string background=path;
            if(e->Attribute("background")!=NULL)
                background=e->Attribute("background");

            int bar_x=x;
            if(e->Attribute("bar_x")!=NULL)
                bar_x=atoi(e->Attribute("bar_x"));

            int bar_y=y;
            if(e->Attribute("bar_y")!=NULL)
                bar_y=atoi(e->Attribute("bar_y"));

            std::string background_selected=background;
            if(e->Attribute("background_selected")!=NULL)
                background_selected=e->Attribute("background_selected");

            int bar_x_selected=bar_x;
            if(e->Attribute("bar_x_selected")!=NULL)
                bar_x_selected=atoi(e->Attribute("bar_x_selected"));

            int bar_y_selected=bar_y;
            if(e->Attribute("bar_y_selected")!=NULL)
                bar_y_selected=atoi(e->Attribute("bar_y_selected"));

            std::string image_selected=path;
            if(e->Attribute("image_selected")!=NULL)
                image_selected=e->Attribute("image_selected");

            int max=9999;
            if(e->Attribute("max")!=NULL)
                max=atoi(e->Attribute("max"));

            elementos_contenedor.push_back((Elemento*)new MenuBarra(painter,
                                                                    x,y,
                                                                    width,height,
                                                                    painter->getTexture(assets_directory+"menu/"+background),
                                                                    bar_x,bar_y,
                                                                    painter->getTexture(assets_directory+"menu/"+path),
                                                                    painter->getTexture(assets_directory+"menu/"+background_selected),
                                                                    bar_x_selected,bar_y_selected,
                                                                    painter->getTexture(assets_directory+"menu/"+image_selected),
                                                                    max,default_value,accion
                                                                    )
                                           );
        }
    }

    if(g_node->FirstChild("rect")!=NULL)
    for(TiXmlNode* rect_node=g_node->FirstChild("rect");
            rect_node!=NULL;
            rect_node=rect_node->NextSibling("rect"))
    {
        TiXmlElement* e=rect_node->ToElement();
        if(e->Attribute("type")!=NULL)
        {
            if(strcmp(e->Attribute("type"),"char_select")==0)
            {
                int x=atoi(e->Attribute("x"));
                int y=atoi(e->Attribute("y"));
                int size_x=3;
                if(e->Attribute("size_x")!=NULL)
                    size_x=atoi(e->Attribute("size_x"));

                int size_y=3;
                if(e->Attribute("size_y")!=NULL)
                    size_y=atoi(e->Attribute("size_y"));

                int box_size_x=100;
                if(e->Attribute("box_size_x")!=NULL)
                    box_size_x=atoi(e->Attribute("box_size_x"));

                int box_size_y=100;
                if(e->Attribute("box_size_y")!=NULL)
                    box_size_y=atoi(e->Attribute("box_size_y"));

                int box_separation_x=0;
                if(e->Attribute("box_separation_x")!=NULL)
                    box_separation_x=atoi(e->Attribute("box_separation_x"));

                int box_separation_y=0;
                if(e->Attribute("box_separation_y")!=NULL)
                    box_separation_y=atoi(e->Attribute("box_separation_y"));

                int chars_player1=1;
                if(e->Attribute("chars_player1")!=NULL)
                    chars_player1=atoi(e->Attribute("chars_player1"));

                int chars_player2=1;
                if(e->Attribute("chars_player2")!=NULL)
                    chars_player2=atoi(e->Attribute("chars_player2"));

                int preview_player1_x=0;
                if(e->Attribute("preview_player1_x")!=NULL)
                    preview_player1_x=atoi(e->Attribute("preview_player1_x"));

                int preview_player1_y=0;
                if(e->Attribute("preview_player1_y")!=NULL)
                    preview_player1_y=atoi(e->Attribute("preview_player1_y"));

                int preview_player2_x=0;
                if(e->Attribute("preview_player2_x")!=NULL)
                    preview_player2_x=atoi(e->Attribute("preview_player2_x"));

                int preview_player2_y=0;
                if(e->Attribute("preview_player2_y")!=NULL)
                    preview_player2_y=atoi(e->Attribute("preview_player2_y"));

                int player1_cursor_x=0;
                if(e->Attribute("player1_cursor_x")!=NULL)
                    player1_cursor_x=atoi(e->Attribute("player1_cursor_x"));

                int player1_cursor_y=0;
                if(e->Attribute("player1_cursor_y")!=NULL)
                    player1_cursor_y=atoi(e->Attribute("player1_cursor_y"));

                int player2_cursor_x=0;
                if(e->Attribute("player2_cursor_x")!=NULL)
                    player2_cursor_x=atoi(e->Attribute("player2_cursor_x"));

                int player2_cursor_y=0;
                if(e->Attribute("player2_cursor_y")!=NULL)
                    player2_cursor_y=atoi(e->Attribute("player2_cursor_y"));

                char_select=new MenuCharSelect(painter,x,y,
                                               size_x,size_y,
                                               box_size_x,box_size_y,
                                               box_separation_x,box_separation_y,
                                               chars_player1,chars_player2,
                                               preview_player1_x,preview_player1_y,
                                               preview_player2_x,preview_player2_y,
                                               chars,
                                               player1_cursor_x,player1_cursor_y,
                                               player2_cursor_x,player2_cursor_y
                                               );
                elementos.push_back((Elemento*)char_select);

            }else if(strcmp(e->Attribute("type"),"stage_select")==0)
            {
                pos_stage=elementos_contenedor.size();
                std::vector<Elemento*>elem_lista;
                for(int i=0;i<(int)stages.size();i++)
                {
                    int displacement_x=0;
                    int displacement_y=0;
                    int stop_displacement_x_at=0;
                    int stop_displacement_y_at=0;
                    int fade_in_initial=-1;
                    int fade_in_speed=0;
                    if(e->Attribute("displacement_x")!=NULL)
                        displacement_x=atoi(e->Attribute("displacement_x"));
                    if(e->Attribute("displacement_y")!=NULL)
                        displacement_y=atoi(e->Attribute("displacement_y"));
                    if(e->Attribute("stop_displacement_x_at")!=NULL)
                        stop_displacement_x_at=atoi(e->Attribute("stop_displacement_x_at"));
                    if(e->Attribute("stop_displacement_y_at")!=NULL)
                        stop_displacement_y_at=atoi(e->Attribute("stop_displacement_y_at"));
                    if(e->Attribute("fade_in_initial")!=NULL)
                        fade_in_initial=atoi(e->Attribute("fade_in_initial"));
                    if(e->Attribute("fade_in_speed")!=NULL)
                        fade_in_speed=atoi(e->Attribute("fade_in_speed"));

                    Image*image=painter->getTexture(assets_directory+"stages/"+stages[i]+std::string("/images/preview.png"));


                    elem_lista.push_back((Elemento*)new MenuImagen(painter,
                                                                   atoi(e->Attribute("x")),atoi(e->Attribute("y")),
                                                                   displacement_x,displacement_y,stop_displacement_x_at,stop_displacement_y_at,fade_in_initial,fade_in_speed,
                                                                   atoi(e->Attribute("width")),atoi(e->Attribute("height")),
                                                                   image,stages[i]
                                                                   ));
                }

                int x=atoi(e->Attribute("x"));
                int y=atoi(e->Attribute("y"));

                int arrow_left_x=x;
                if(e->Attribute("arrow_left_x"))
                    atoi(e->Attribute("arrow_left_x"));

                int arrow_left_y=y;
                if(e->Attribute("arrow_left_y"))
                    atoi(e->Attribute("arrow_left_y"));

                Image*path_left=NULL;
                if(e->Attribute("path_left")!=NULL)
                    path_left=painter->getTexture(assets_directory+"menu/"+std::string(e->Attribute("path_left")));

                int arrow_right_x=x;
                if(e->Attribute("arrow_right_x"))
                    atoi(e->Attribute("arrow_right_x"));

                int arrow_right_y=y;
                if(e->Attribute("arrow_right_y"))
                    atoi(e->Attribute("arrow_right_y"));

                Image*path_right=NULL;
                if(e->Attribute("path_right")!=NULL)
                    path_right=painter->getTexture(assets_directory+"menu/"+std::string(e->Attribute("path_right")));

                int arrow_left_x_selected=x;
                if(e->Attribute("arrow_left_x_selected"))
                    atoi(e->Attribute("arrow_left_x_selected"));

                int arrow_left_y_selected=y;
                if(e->Attribute("arrow_left_y_selected"))
                    atoi(e->Attribute("arrow_left_y_selected"));

                Image*path_left_selected=path_left;
                if(e->Attribute("path_left_selected")!=NULL)
                    path_left_selected=painter->getTexture(assets_directory+"menu/"+std::string(e->Attribute("path_left_selected")));

                int arrow_right_x_selected=x;
                if(e->Attribute("arrow_right_x_selected"))
                    atoi(e->Attribute("arrow_right_x_selected"));

                int arrow_right_y_selected=y;
                if(e->Attribute("arrow_right_y_selected"))
                    atoi(e->Attribute("arrow_right_y_selected"));

                Image*path_right_selected=path_right;
                if(e->Attribute("path_right_selected")!=NULL)
                    path_right_selected=painter->getTexture(assets_directory+"menu/"+std::string(e->Attribute("path_right_selected")));

                string action="1v1";
                if(e->Attribute("action"))
                    action=e->Attribute("action");

                elementos_contenedor.push_back((Elemento*)new MenuLista(painter,x,y,
                                                                        arrow_left_x,arrow_left_y,
                                                                        path_left,
                                                                        arrow_right_x,arrow_right_y,
                                                                        path_right,
                                                                        arrow_left_x_selected,arrow_left_y_selected,
                                                                        path_left_selected,
                                                                        arrow_right_x_selected,arrow_right_y_selected,
                                                                        path_right_selected,
                                                                        elem_lista,
                                                                        action
                                                                        )
                                               );

            }else if(strcmp(e->Attribute("type"),"gallery")==0)
            {
                int x=atoi(e->Attribute("x"));
                int y=atoi(e->Attribute("y"));
                int size_x=3;
                if(e->Attribute("size_x")!=NULL)
                    size_x=atoi(e->Attribute("size_x"));

                int size_y=3;
                if(e->Attribute("size_y")!=NULL)
                    size_y=atoi(e->Attribute("size_y"));

                int box_size_x=100;
                if(e->Attribute("box_size_x")!=NULL)
                    box_size_x=atoi(e->Attribute("box_size_x"));

                int box_size_y=100;
                if(e->Attribute("box_size_y")!=NULL)
                    box_size_y=atoi(e->Attribute("box_size_y"));

                int box_separation_x=0;
                if(e->Attribute("box_separation_x")!=NULL)
                    box_separation_x=atoi(e->Attribute("box_separation_x"));

                int box_separation_y=0;
                if(e->Attribute("box_separation_y")!=NULL)
                    box_separation_y=atoi(e->Attribute("box_separation_y"));

                int preview_player1_x=0;
                if(e->Attribute("preview_player1_x")!=NULL)
                    preview_player1_x=atoi(e->Attribute("preview_player1_x"));

                int preview_player1_y=0;
                if(e->Attribute("preview_player1_y")!=NULL)
                    preview_player1_y=atoi(e->Attribute("preview_player1_y"));

                int player1_cursor_x=0;
                if(e->Attribute("player1_cursor_x")!=NULL)
                    player1_cursor_x=atoi(e->Attribute("player1_cursor_x"));

                int player1_cursor_y=0;
                if(e->Attribute("player1_cursor_y")!=NULL)
                    player1_cursor_y=atoi(e->Attribute("player1_cursor_y"));

                int image_amount=0;
                if(e->Attribute("image_amount")!=NULL)
                    image_amount=atoi(e->Attribute("image_amount"));


                MenuGallery* menu_gallery=new MenuGallery(painter,x,y,
                                               size_x,size_y,
                                               box_size_x,box_size_y,
                                               box_separation_x,box_separation_y,
                                               preview_player1_x,preview_player1_y,
                                               image_amount,
                                               player1_cursor_x,player1_cursor_y
                                               );
                elementos_contenedor.push_back((Elemento*)menu_gallery);
            }
        }
    }

    selectables_container=new MenuContenedor(painter,elementos_contenedor);
    elementos.push_back((Elemento*)selectables_container);

    for(TiXmlNode* text_node=g_node->FirstChild("text");
            text_node!=NULL;
            text_node=text_node->NextSibling("text"))
    {
        TiXmlElement* e=text_node->ToElement();

        TiXmlElement* text_span_elem=text_node->FirstChild("tspan")->ToElement();

        elementos.push_back((Elemento*)new MenuTexto(painter,atoi(e->Attribute("x")),atoi(e->Attribute("y")),
                                                     text_span_elem->GetText()
                                                     ));
    }
    writeLogLine("menu elements loaded");
}

Personaje* Menu::getPersonajeA(int num,bool ia)
{
    writeLogLine("Initializing player's 1 character #"+toString(num)+".");
    //get string
    std::string char_name=char_select->getLockedNamesPA()[num];
    int num_paleta=char_select->getLockedPalettesPA()[num];

    //get cadena
    string path_a=char_name;

    if(ia)
    {
        writeLogLine("Loading AI.");
        input_player1=new RosalilaInputs();
        string xml_path=assets_directory+"chars/"+char_name+"/ia.xml";
        input_player1->cargarRosalilaAIXML(2,xml_path,"");
    }else
    {
        writeLogLine("Loading inputs.");
        input_player1=new RosalilaInputs();
        input_player1->loadFromXML(1,receiver);
    }

    //get char
    Personaje* p=new Personaje(painter,sonido,1,num_paleta);
    p->loadFromXML(input_player1,(char *)path_a.c_str());
    writeLogLine("Loaded successfully.");
    return p;
}

Personaje* Menu::getPersonajeB(int num,bool ia)
{
    writeLogLine("Initializing player's 1 character #"+toString(num)+".");
    //get string
    std::string char_name=char_select->getLockedNamesPB()[num];
    int num_paleta=char_select->getLockedPalettesPB()[num];

    if(ia)
    {
        writeLogLine("Loading AI.");
        input_player2=new RosalilaInputs();

        string xml_path_default=assets_directory+"chars/"+char_name+"/ai/default.xml";
        string xml_path=assets_directory+"chars/"+char_name;

        if(ai_level==1)
            xml_path+="/ai/level 1.xml";
        if(ai_level==2)
            xml_path+="/ai/level 2.xml";
        if(ai_level==3)
            xml_path+="/ai/level 3.xml";
        if(ai_level==4)
            xml_path+="/ai/level 4.xml";
        if(ai_level==5)
            xml_path+="/ai/level 5.xml";
        input_player2->cargarRosalilaAIXML(2,xml_path,xml_path_default);
    }else
    {
        writeLogLine("Loading inputs.");
        input_player2=new RosalilaInputs();
        input_player2->loadFromXML(2,receiver);
    }

    //get char
    Personaje* p=new Personaje(painter,sonido,2,num_paleta);
    string xml_path=assets_directory+char_name;
    p->loadFromXML(input_player2,(char*)char_name.c_str());
    writeLogLine("Loaded successfully.");
    return p;
}

std::string Menu::getStage()
{
    //!
    MenuContenedor *mc=((MenuContenedor*)selectables_container);
    MenuLista *ml=(MenuLista*)mc->elementos[pos_stage];
    MenuImagen *mt=(MenuImagen*)ml->getElementoActual();
    std::string str=mt->value;

    return str;
}

bool Menu::getExitSignal()
{
    bool temp=exit_signal;
    exit_signal=false;
    return temp;
}

bool Menu::getSaveRosalilaInputssSignal()
{
    bool temp=save_inputs_signal;
    save_inputs_signal=false;
    return temp;
}

void Menu::escribirRosalilaInputssXML(RosalilaInputs* ia,RosalilaInputs* ib)
{
    TiXmlDocument *doc=new TiXmlDocument();
    ib->getXML(ia->getXML(doc));
    string xml_path = assets_directory+"misc/inputs.xml";
    doc->SaveFile( xml_path.c_str() );
}

std::string Menu::getRosalilaInputsPressed()
{
    while(true)
    {

        dibujarMenu();
        if(receiver->isKeyDown(SDLK_q))
            return "Q";
        if(receiver->isKeyDown(SDLK_w))
            return "W";
        if(receiver->isKeyDown(SDLK_e))
            return "E";
        if(receiver->isKeyDown(SDLK_r))
            return "R";
        if(receiver->isKeyDown(SDLK_t))
            return "T";
        if(receiver->isKeyDown(SDLK_y))
            return "Y";
        if(receiver->isKeyDown(SDLK_u))
            return "U";
        if(receiver->isKeyDown(SDLK_i))
            return "I";
        if(receiver->isKeyDown(SDLK_o))
            return "O";
        if(receiver->isKeyDown(SDLK_p))
            return "P";
        if(receiver->isKeyDown(SDLK_a))
            return "A";
        if(receiver->isKeyDown(SDLK_s))
            return "S";
        if(receiver->isKeyDown(SDLK_d))
            return "D";
        if(receiver->isKeyDown(SDLK_f))
            return "F";
        if(receiver->isKeyDown(SDLK_g))
            return "G";
        if(receiver->isKeyDown(SDLK_h))
            return "H";
        if(receiver->isKeyDown(SDLK_j))
            return "J";
        if(receiver->isKeyDown(SDLK_k))
            return "K";
        if(receiver->isKeyDown(SDLK_l))
            return "L";
        if(receiver->isKeyDown(SDLK_z))
            return "Z";
        if(receiver->isKeyDown(SDLK_x))
            return "X";
        if(receiver->isKeyDown(SDLK_c))
            return "C";
        if(receiver->isKeyDown(SDLK_v))
            return "V";
        if(receiver->isKeyDown(SDLK_b))
            return "B";
        if(receiver->isKeyDown(SDLK_n))
            return "N";
        if(receiver->isKeyDown(SDLK_m))
            return "M";

        if(receiver->isJoyDown(0,0))
            return "j0-0";
        if(receiver->isJoyDown(1,0))
            return "j0-1";
        if(receiver->isJoyDown(2,0))
            return "j0-2";
        if(receiver->isJoyDown(3,0))
            return "j0-3";
        if(receiver->isJoyDown(4,0))
            return "j0-4";
        if(receiver->isJoyDown(5,0))
            return "j0-5";
        if(receiver->isJoyDown(6,0))
            return "j0-6";
        if(receiver->isJoyDown(7,0))
            return "j0-7";
        if(receiver->isJoyDown(8,0))
            return "j0-8";
        if(receiver->isJoyDown(9,0))
            return "j0-9";
        if(receiver->isJoyDown(10,0))
            return "j0-10";
        if(receiver->isJoyDown(-2,0))
            return "j0-d";
        if(receiver->isJoyDown(-4,0))
            return "j0-l";
        if(receiver->isJoyDown(-6,0))
            return "j0-r";
        if(receiver->isJoyDown(-8,0))
            return "j0-u";

        if(receiver->isJoyDown(0,1))
            return "j1-0";
        if(receiver->isJoyDown(1,1))
            return "j1-1";
        if(receiver->isJoyDown(2,1))
            return "j1-2";
        if(receiver->isJoyDown(3,1))
            return "j1-3";
        if(receiver->isJoyDown(4,1))
            return "j1-4";
        if(receiver->isJoyDown(5,1))
            return "j1-5";
        if(receiver->isJoyDown(6,1))
            return "j1-6";
        if(receiver->isJoyDown(7,1))
            return "j1-7";
        if(receiver->isJoyDown(8,1))
            return "j1-8";
        if(receiver->isJoyDown(9,1))
            return "j1-9";
        if(receiver->isJoyDown(10,1))
            return "j1-10";
        if(receiver->isJoyDown(-2,1))
            return "j1-d";
        if(receiver->isJoyDown(-4,1))
            return "j1-l";
        if(receiver->isJoyDown(-6,1))
            return "j1-r";
        if(receiver->isJoyDown(-8,1))
            return "j1-u";
    }
}

int Menu::toKeyCode(std::string str)
{
    if(str==std::string("Q"))
        return SDLK_q;
    if(str==std::string("W"))
        return SDLK_w;
    if(str==std::string("E"))
        return SDLK_e;
    if(str==std::string("R"))
        return SDLK_r;
    if(str==std::string("T"))
        return SDLK_t;
    if(str==std::string("Y"))
        return SDLK_y;
    if(str==std::string("U"))
        return SDLK_u;
    if(str==std::string("I"))
        return SDLK_i;
    if(str==std::string("O"))
        return SDLK_o;
    if(str==std::string("P"))
        return SDLK_p;
    if(str==std::string("A"))
        return SDLK_a;
    if(str==std::string("S"))
        return SDLK_s;
    if(str==std::string("D"))
        return SDLK_d;
    if(str==std::string("F"))
        return SDLK_f;
    if(str==std::string("G"))
        return SDLK_g;
    if(str==std::string("H"))
        return SDLK_h;
    if(str==std::string("J"))
        return SDLK_j;
    if(str==std::string("K"))
        return SDLK_k;
    if(str==std::string("L"))
        return SDLK_l;
    if(str==std::string("Z"))
        return SDLK_z;
    if(str==std::string("X"))
        return SDLK_x;
    if(str==std::string("C"))
        return SDLK_c;
    if(str==std::string("V"))
        return SDLK_v;
    if(str==std::string("B"))
        return SDLK_b;
    if(str==std::string("N"))
        return SDLK_n;
    if(str==std::string("M"))
        return SDLK_m;
    return SDLK_ESCAPE;
}


void Menu::llenarInputsBotones()
{
    for(int i=0;i<(int)selectables_container->elementos.size();i++)
    {
        if(((MenuContenedor*)selectables_container)->elementos[i]->getTipo()=="Boton")
        {
//            MenuBoton*mb=(MenuBoton*)selectables_container->elementos[i];
//            if(mb->getAccion()>=10 && mb->getAccion()<=29)
//            {
//                int player;
//                std::string mapeo="";
//                int accion=mb->getAccion();
//                if(accion>=10 && accion<=19)
//                    player=1;
//                else
//                    player=2;
//                RosalilaInputs* temp=new RosalilaInputs();
//                RosalilaInputs* temp2=new RosalilaInputs();
//                if(player==1)
//                {
//                    temp->loadFromXML(1,receiver);
//                    temp2->loadFromXML(2,receiver);
//                }else
//                {
//                    temp->loadFromXML(2,receiver);
//                    temp2->loadFromXML(1,receiver);
//                }
//                if(accion==10||accion==20)mapeo="8";
//                if(accion==11||accion==21)mapeo="2";
//                if(accion==12||accion==22)mapeo="4";
//                if(accion==13||accion==23)mapeo="6";
//                if(accion==14||accion==24)mapeo="a";
//                if(accion==15||accion==25)mapeo="b";
//                if(accion==16||accion==26)mapeo="c";
//                if(accion==17||accion==27)mapeo="d";
//                if(accion==18||accion==28)mapeo="e";
//                if(accion==19||accion==29)mapeo="f";
//
//                //key
//                mb->input_config="";
//                int pos=-1,posc=-1;
//                for(int j=0;j<(int)temp->botones.size();j++)
//                    if(temp->botones[j].getMapeo()==mapeo && !temp->botones[j].usaJoystick())
//                        pos=j;
//
//                for(int j=0;j<(int)temp->cruz.size();j++)
//                    if(temp->cruz[j].getMapeo()==mapeo && !temp->cruz[j].usaJoystick())
//                        posc=j;
//
//                if(pos!=-1)
//                    mb->input_config=temp->botones[pos].keyToString();
//
//                if(posc!=-1)
//                    mb->input_config=temp->cruz[posc].keyToString();
//
//                //joy
//                pos=-1;
//                for(int j=0;j<(int)temp->botones.size();j++)
//                    if(temp->botones[j].getMapeo()==mapeo && temp->botones[j].usaJoystick())
//                        pos=j;
//                posc=-1;
//                for(int j=0;j<(int)temp->cruz.size();j++)
//                    if(temp->cruz[j].getMapeo()==mapeo && temp->cruz[j].usaJoystick())
//                        posc=j;
//
//                if(pos!=-1)
//                {
//                    mb->input_config+=" j";
//                    mb->input_config+=toString((int)temp->botones[pos].getNumJoystick());
//                    mb->input_config+=toString((int)temp->botones[pos].joystick);
//                }
//
//                if(posc!=-1)
//                {
//                    mb->input_config+=" j";
//                    mb->input_config+=toString((int)temp->cruz[posc].getNumJoystick());
//                    mb->input_config+="-";
//                    if(temp->cruz[posc].joystick==-8)
//                        mb->input_config+=std::string("up");
//                    else if(temp->cruz[posc].joystick==-2)
//                        mb->input_config+=std::string("down");
//                    else if(temp->cruz[posc].joystick==-4)
//                        mb->input_config+=std::string("left");
//                    else if(temp->cruz[posc].joystick==-6)
//                        mb->input_config+=std::string("right");
//                    else
//                        mb->input_config+=toString((int)temp->cruz[posc].joystick);
//                }
//            }
        }
    }
}

void Menu::printVsScreen(vector<Image*>pa_previews,vector<Image*>pb_previews)
{
    painter->draw2DImage
    (   vs_screen,
        vs_screen->getWidth(),vs_screen->getHeight(),
        0,0,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        0,0,
        false);

    for(int i=0;i<(int)pa_previews.size();i++)
    {
        Image*texture=pa_previews[i];
        painter->draw2DImage
        (   texture,
            texture->getWidth(),texture->getHeight(),
            i*200,painter->screen_height-texture->getHeight(),
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false);
    }

    for(int i=0;i<(int)pb_previews.size();i++)
    {
        Image*texture=pb_previews[i];
        painter->draw2DImage
        (   texture,
            texture->getWidth(),texture->getHeight(),
            painter->screen_width-(i+1)*texture->getWidth()-50,painter->screen_height-texture->getHeight(),
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false);
    }
    painter->updateScreen();
}

void Menu::joyPressedEditInput(int button,int joystick_number,int player)
{
    if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Boton")
    {
        MenuBoton*mb=((MenuBoton*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
        if(player==1)
        {
            if(mb->getAccion()=="Player1.KeyConfig:a")
            {
                input_player1->editInput(player,joystick_number,toString(button),"a");
                reloadInputs();
            }
            if(mb->getAccion()=="Player1.KeyConfig:b")
            {
                input_player1->editInput(player,joystick_number,toString(button),"b");
                reloadInputs();
            }
            if(mb->getAccion()=="Player1.KeyConfig:c")
            {
                input_player1->editInput(player,joystick_number,toString(button),"c");
                reloadInputs();
            }
            if(mb->getAccion()=="Player1.KeyConfig:d")
            {
                input_player1->editInput(player,joystick_number,toString(button),"d");
                reloadInputs();
            }
            if(mb->getAccion()=="Player1.KeyConfig:e")
            {
                input_player1->editInput(player,joystick_number,toString(button),"e");
                reloadInputs();
            }
            if(mb->getAccion()=="Player1.KeyConfig:f")
            {
                input_player1->editInput(player,joystick_number,toString(button),"f");
                reloadInputs();
            }
        }
        if(player==2)
        {
            if(mb->getAccion()=="Player2.KeyConfig:a")
            {
                input_player2->editInput(player,joystick_number,toString(button),"a");
                reloadInputs();
            }
            if(mb->getAccion()=="Player2.KeyConfig:b")
            {
                input_player2->editInput(player,joystick_number,toString(button),"b");
                reloadInputs();
            }
            if(mb->getAccion()=="Player2.KeyConfig:c")
            {
                input_player2->editInput(player,joystick_number,toString(button),"c");
                reloadInputs();
            }
            if(mb->getAccion()=="Player2.KeyConfig:d")
            {
                input_player2->editInput(player,joystick_number,toString(button),"d");
                reloadInputs();
            }
            if(mb->getAccion()=="Player2.KeyConfig:e")
            {
                input_player2->editInput(player,joystick_number,toString(button),"e");
                reloadInputs();
            }
            if(mb->getAccion()=="Player2.KeyConfig:f")
            {
                input_player2->editInput(player,joystick_number,toString(button),"f");
                reloadInputs();
            }
        }
    }
}

void Menu::editInputCheck()
{
    if(receiver->isJoyPressed(0,0))
    {
        joyPressedEditInput(0,0,1);
    }
    if(receiver->isJoyPressed(1,0))
    {
        joyPressedEditInput(1,0,1);
    }
    if(receiver->isJoyPressed(2,0))
    {
        joyPressedEditInput(2,0,1);
    }
    if(receiver->isJoyPressed(3,0))
    {
        joyPressedEditInput(3,0,1);
    }
    if(receiver->isJoyPressed(4,0))
    {
        joyPressedEditInput(4,0,1);
    }
    if(receiver->isJoyPressed(5,0))
    {
        joyPressedEditInput(5,0,1);
    }
    if(receiver->isJoyPressed(6,0))
    {
        joyPressedEditInput(6,0,1);
    }


    if(receiver->isJoyPressed(0,1))
    {
        joyPressedEditInput(0,1,2);
    }
    if(receiver->isJoyPressed(1,1))
    {
        joyPressedEditInput(1,1,2);
    }
    if(receiver->isJoyPressed(2,1))
    {
        joyPressedEditInput(2,1,2);
    }
    if(receiver->isJoyPressed(3,1))
    {
        joyPressedEditInput(3,1,2);
    }
    if(receiver->isJoyPressed(4,1))
    {
        joyPressedEditInput(4,1,2);
    }
    if(receiver->isJoyPressed(5,1))
    {
        joyPressedEditInput(5,1,2);
    }
    if(receiver->isJoyPressed(6,1))
    {
        joyPressedEditInput(6,1,2);
    }
}

void Menu::reloadInputs()
{
    delete input_player1;
    input_player1=new RosalilaInputs();
    input_player1->loadFromXML(1,receiver);

    delete input_player2;
    input_player2=new RosalilaInputs();
    input_player2->loadFromXML(2,receiver);

    //Change menu printed inputs
    for(int i=0;i<(int)elementos.size();i++)
    {
        Elemento*e=elementos[i];
        if(e->getTipo()=="Imagen")//Is MenuImagen
        {
            MenuImagen* mi=(MenuImagen*)e;
            if(mi->fade_in_current!=-1)
            {
                mi->fade_in_current+=mi->fade_in_speed;
                if(mi->fade_in_current>255)
                    mi->fade_in_current=255;
            }
        }
        if(e->current_displacement_x<e->stop_displacement_x_at)
        {
            e->x+=e->displacement_x;
            e->current_displacement_x++;
        }
        if(e->current_displacement_y<e->stop_displacement_y_at)
        {
            e->y+=e->displacement_y;
            e->current_displacement_y++;
        }

        if(e->getTipo()=="Contenedor")
        {
            MenuContenedor* container = (MenuContenedor*)e;
            for(int j=0;j<(int)container->elementos.size();j++)
            {
                if(container->elementos[j]->getTipo()=="Boton")
                {
                    MenuBoton* button = (MenuBoton*)container->elementos[j];
                    string action = button->getAccion();
                    //

                    if(action=="GameplayEdit.Mole.ShowHp")
                    {
                        button->texto = "Hp:" + gameplay_editor.getHp();
                        button->texto_sel = "Hp:" + gameplay_editor.getHp();
                        //button->alineacion_texto_x = 500;
                    }
                    if(action=="GameplayEdit.Mole.ShowSpeedForward")
                    {
                        button->texto = "Speed:" + gameplay_editor.getSpeedForward();
                        button->texto_sel = "Speed:" + gameplay_editor.getSpeedForward();
                    }
                    if(action=="GameplayEdit.Mole.ShowSpeedBack")
                    {
                        button->texto = "Speed:" + gameplay_editor.getSpeedBack();
                        button->texto_sel = "Speed:" + gameplay_editor.getSpeedBack();
                    }
                    if(action=="GameplayEdit.Mole.ShowSpeedOverhead")
                    {
                        button->texto = "Speed:" + gameplay_editor.getSpeedOverhead();
                        button->texto_sel = "Speed:" + gameplay_editor.getSpeedOverhead();
                    }
                    if(action=="GameplayEdit.Mole.ShowSpeedSlash")
                    {
                        button->texto = "Speed:" + gameplay_editor.getSpeedSlash();
                        button->texto_sel = "Speed:" + gameplay_editor.getSpeedSlash();
                    }
                    if(action=="GameplayEdit.Mole.ShowSpeedLow")
                    {
                        button->texto = "Speed:" + gameplay_editor.getSpeedLow();
                        button->texto_sel = "Speed:" + gameplay_editor.getSpeedLow();
                    }

                    if(action=="GameplayEdit.Mole.ShowDamageOverhead")
                    {
                        button->texto = "Damage:" + gameplay_editor.getDamageOverhead();
                        button->texto_sel = "Damage:" + gameplay_editor.getDamageOverhead();
                    }
                    if(action=="GameplayEdit.Mole.ShowDamageSlash")
                    {
                        button->texto = "Damage:" + gameplay_editor.getDamageSlash();
                        button->texto_sel = "Damage:" + gameplay_editor.getDamageSlash();
                    }
                    if(action=="GameplayEdit.Mole.ShowDamageLow")
                    {
                        button->texto = "Damage:" + gameplay_editor.getDamageLow();
                        button->texto_sel = "Damage:" + gameplay_editor.getDamageLow();
                    }
                    if(action=="GameplayEdit.Mole.ShowChipDamageOverhead")
                    {
                        button->texto = "Chip damage:" + gameplay_editor.getChipDamageOverhead();
                        button->texto_sel = "Chip damage:" + gameplay_editor.getChipDamageOverhead();
                    }
                    if(action=="GameplayEdit.Mole.ShowChipDamageSlash")
                    {
                        button->texto = "Chip damage:" + gameplay_editor.getChipDamageSlash();
                        button->texto_sel = "Chip damage:" + gameplay_editor.getChipDamageSlash();
                    }
                    if(action=="GameplayEdit.Mole.ShowChipDamageLow")
                    {
                        button->texto = "Chip damage:" + gameplay_editor.getChipDamageLow();
                        button->texto_sel = "Chip damage:" + gameplay_editor.getChipDamageLow();
                    }

                    if(action=="GameplayEdit.Mole.ShowBlockstunOverhead")
                    {
                        button->texto = "Blockstun:" + gameplay_editor.getBlockstunOverhead();
                        button->texto_sel = "Blockstun:" + gameplay_editor.getBlockstunOverhead();
                    }
                    if(action=="GameplayEdit.Mole.ShowBlockstunSlash")
                    {
                        button->texto = "Blockstun:" + gameplay_editor.getBlockstunSlash();
                        button->texto_sel = "Blockstun:" + gameplay_editor.getBlockstunSlash();
                    }
                    if(action=="GameplayEdit.Mole.ShowBlockstunLow")
                    {
                        button->texto = "Blockstun:" + gameplay_editor.getBlockstunLow();
                        button->texto_sel = "Blockstun:" + gameplay_editor.getBlockstunLow();
                    }

                    if(action=="GameplayEdit.Mole.ShowHitstun")
                    {
                        button->texto = "Hitstun:" + gameplay_editor.getHitstun();
                        button->texto_sel = "Hitstun:" + gameplay_editor.getHitstun();
                    }

                    if(action.size()>=18
                       &&
                        (action.substr(0,18)=="Player1.KeyConfig:"
                        || action.substr(0,18)=="Player2.KeyConfig:")
                       )
                    {
                        RosalilaInputs* input = input_player1;
                        int joystick_num = 0;
                        if(action.substr(0,18)=="Player2.KeyConfig:")
                        {
                            input = input_player2;
                            joystick_num = 1;
                        }
                        if(action[action.size()-1]=='a')
                        {
                            button->texto = input->getJoystickInput("a",joystick_num);
                            button->texto_sel = input->getJoystickInput("a",joystick_num);
                        }
                        if(action[action.size()-1]=='b')
                        {
                            button->texto = input->getJoystickInput("b",joystick_num);
                            button->texto_sel = input->getJoystickInput("b",joystick_num);
                        }
                        if(action[action.size()-1]=='c')
                        {
                            button->texto = input->getJoystickInput("c",joystick_num);
                            button->texto_sel = input->getJoystickInput("c",joystick_num);
                        }
                        if(action[action.size()-1]=='d')
                        {
                            button->texto = input->getJoystickInput("d",joystick_num);
                            button->texto_sel = input->getJoystickInput("d",joystick_num);
                        }
                        if(action[action.size()-1]=='e')
                        {
                            button->texto = input->getJoystickInput("e",joystick_num);
                            button->texto_sel = input->getJoystickInput("e",joystick_num);
                        }
                        if(action[action.size()-1]=='f')
                        {
                            button->texto = input->getJoystickInput("f",joystick_num);
                            button->texto_sel = input->getJoystickInput("f",joystick_num);
                        }
                    }
                }
            }
        }
    }
}

void Menu::applyGraphicEffects()
{
    for(int i=0;i<(int)elementos.size();i++)
    {
        Elemento*e=elementos[i];
        if(e->getTipo()=="Imagen")//Is MenuImagen
        {
            MenuImagen* mi=(MenuImagen*)e;
            if(mi->fade_in_current!=-1)
            {
                mi->fade_in_current+=mi->fade_in_speed;
                if(mi->fade_in_current>255)
                    mi->fade_in_current=255;
            }
        }
        if(e->current_displacement_x<e->stop_displacement_x_at)
        {
            e->x+=e->displacement_x;
            e->current_displacement_x++;
        }
        if(e->current_displacement_y<e->stop_displacement_y_at)
        {
            e->y+=e->displacement_y;
            e->current_displacement_y++;
        }
    }
}

void Menu::updateKeyUpCheck()
{
    input_player1->actualizarBuffer();
    if(input_player1->getBufferRosalilaInputs()[0]!="6"
       && input_player1->getBufferRosalilaInputs()[0]!="4"
       && input_player1->getBufferRosalilaInputs()[0]!="2"
       && input_player1->getBufferRosalilaInputs()[0]!="8"
       && input_player1->getBufferRosalilaInputs()[0]!="a"
       && input_player1->getBufferRosalilaInputs()[0]!="b"
       && input_player1->getBufferRosalilaInputs()[0]!="c"
       )
    {
        keyup_player1=true;
    }

    input_player2->actualizarBuffer();
    if(input_player2->getBufferRosalilaInputs()[0]!="6"
       && input_player2->getBufferRosalilaInputs()[0]!="4"
       && input_player2->getBufferRosalilaInputs()[0]!="2"
       && input_player2->getBufferRosalilaInputs()[0]!="8"
       && input_player2->getBufferRosalilaInputs()[0]!="a"
       && input_player2->getBufferRosalilaInputs()[0]!="b"
       && input_player2->getBufferRosalilaInputs()[0]!="c"
       )
    {
        keyup_player2=true;
    }
}

void Menu::renderGallery()
{
    if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Gallery")
    {
        if(input_player1->getBufferRosalilaInputs()[0]=="2" && keyup_player1)
        {
            MenuGallery*mg = ((MenuGallery*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
            mg->fullscreen_on=false;
            mg->select_p1_y++;
            if(mg->select_p1_y>=mg->size_y)
                mg->select_p1_y=0;
            keyup_player1=false;
        }
        if(input_player1->getBufferRosalilaInputs()[0]=="4" && keyup_player1)
        {
            MenuGallery*mg = ((MenuGallery*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
            mg->fullscreen_on=false;
            mg->select_p1_x--;
            if(mg->select_p1_x<0)
                mg->select_p1_x=mg->size_x-1;
            keyup_player1=false;
        }
        if(input_player1->getBufferRosalilaInputs()[0]=="6" && keyup_player1)
        {
            MenuGallery*mg = ((MenuGallery*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
            mg->fullscreen_on=false;
            mg->select_p1_x++;
            if(mg->select_p1_x>=mg->size_x)
                mg->select_p1_x=0;
            keyup_player1=false;
        }
        if(input_player1->getBufferRosalilaInputs()[0]=="8" && keyup_player1)
        {
            MenuGallery*mg = ((MenuGallery*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
            mg->fullscreen_on=false;
            mg->select_p1_y--;
            if(mg->select_p1_y<0)
                mg->select_p1_y=mg->size_y-1;
            keyup_player1=false;
        }
        if(input_player1->getBufferRosalilaInputs()[0]=="a" && keyup_player1)
        {
            MenuGallery*mg = ((MenuGallery*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
            mg->select();
            keyup_player1=false;
        }
    }
}

void Menu::characterSelectControl()
{
    if(char_select!=NULL && keyup_player1)
    {
        if(char_select->listoPA())
        {
            if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Lista")
            {
                MenuLista*ml=((MenuLista*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                if(ml->getAccion()=="1v1-cpu"
                    || ml->getAccion()=="1v1-training"
                   )
                {
                    if(input_player1->getBufferRosalilaInputs()[0]=="6")
                    {
                        sonido->playSound(std::string("Menu.move_char"));
                        char_select->select_p2_x++;
                        if(char_select->select_p2_x>=char_select->size_x)
                            char_select->select_p2_x=0;
                        keyup_player1=false;
                    }else if(input_player1->getBufferRosalilaInputs()[0]=="4")
                    {
                        sonido->playSound(std::string("Menu.move_char"));
                        char_select->select_p2_x--;
                        if(char_select->select_p2_x<0)
                            char_select->select_p2_x=char_select->size_x-1;
                        keyup_player1=false;
                    }
                    else if(input_player1->getBufferRosalilaInputs()[0]=="2")
                    {
                        sonido->playSound(std::string("Menu.move_char"));
                        char_select->select_p2_y++;
                        if(char_select->select_p2_y>=char_select->size_y)
                            char_select->select_p2_y=0;
                        keyup_player1=false;
                    }
                    else if(input_player1->getBufferRosalilaInputs()[0]=="8")
                    {
                        sonido->playSound(std::string("Menu.move_char"));
                        char_select->select_p2_y--;
                        if(char_select->select_p2_y<0)
                            char_select->select_p2_y=char_select->size_y-1;
                        keyup_player1=false;
                    }
                    else if(input_player1->getBufferRosalilaInputs()[0]=="a")
                    {
                        sonido->playSound(std::string("Menu.select_char"));
                        char_select->lockPB(0);
                        //keyup_player1=false;
                    }
                }
            }
        }else if(input_player1->getBufferRosalilaInputs()[0]=="6")
        {
            sonido->playSound(std::string("Menu.move_char"));
            char_select->select_p1_x++;
            if(char_select->select_p1_x>=char_select->size_x)
                char_select->select_p1_x=0;
            keyup_player1=false;
        }else if(input_player1->getBufferRosalilaInputs()[0]=="4")
        {
            sonido->playSound(std::string("Menu.move_char"));
            char_select->select_p1_x--;
            if(char_select->select_p1_x<0)
                char_select->select_p1_x=char_select->size_x-1;
            keyup_player1=false;
        }
        else if(input_player1->getBufferRosalilaInputs()[0]=="2")
        {
            sonido->playSound(std::string("Menu.move_char"));
            char_select->select_p1_y++;
            if(char_select->select_p1_y>=char_select->size_y)
                char_select->select_p1_y=0;
            keyup_player1=false;
        }
        else if(input_player1->getBufferRosalilaInputs()[0]=="8")
        {
            sonido->playSound(std::string("Menu.move_char"));
            char_select->select_p1_y--;
            if(char_select->select_p1_y<0)
                char_select->select_p1_y=char_select->size_y-1;
            keyup_player1=false;
        }
        else if(input_player1->getBufferRosalilaInputs()[0]=="a")
        {
            sonido->playSound(std::string("Menu.select_char"));
            char_select->lockPA(0);
            //keyup_player1=false;
        }
    }

    if(char_select!=NULL && keyup_player2)
    {
        if(char_select->listoPB())
        {
        }else if(input_player2->getBufferRosalilaInputs()[0]=="6")
        {
            sonido->playSound(std::string("Menu.move_char"));
            char_select->select_p2_x++;
            if(char_select->select_p2_x>=char_select->size_x)
                char_select->select_p2_x=0;
            keyup_player2=false;
        }else if(input_player2->getBufferRosalilaInputs()[0]=="4")
        {
            sonido->playSound(std::string("Menu.move_char"));
            char_select->select_p2_x--;
            if(char_select->select_p2_x<0)
                char_select->select_p2_x=char_select->size_x-1;
            keyup_player2=false;
        }
        else if(input_player2->getBufferRosalilaInputs()[0]=="2")
        {
            sonido->playSound(std::string("Menu.move_char"));
            char_select->select_p2_y++;
            if(char_select->select_p2_y>=char_select->size_y)
                char_select->select_p2_y=0;
            keyup_player2=false;
        }
        else if(input_player2->getBufferRosalilaInputs()[0]=="8")
        {
            sonido->playSound(std::string("Menu.move_char"));
            char_select->select_p2_y--;
            if(char_select->select_p2_y<0)
                char_select->select_p2_y=char_select->size_y-1;
            keyup_player2=false;
        }
        else if(input_player2->getBufferRosalilaInputs()[0]=="a")
        {
            sonido->playSound(std::string("Menu.select_char"));
            char_select->lockPB(0);
            //keyup_player2=false;
        }
    }
}

void Menu::gameplayEdit(string character, string variable, int value, bool relative)
{
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("walk forward",move_node->ToElement()->Attribute("name"))==0)
        {
            int velocity_x = atoi(move_node->ToElement()->Attribute("velocity_x"));
            velocity_x++;
            for(TiXmlAttribute* move_attribute = move_node->ToElement()->FirstAttribute();
                move_attribute!=NULL;
                move_attribute=move_attribute->Next()
                )
            {
                if(strcmp(move_attribute->Name(),"velocity_x")==0)
                {
                    move_attribute->SetValue(toString(velocity_x).c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}
