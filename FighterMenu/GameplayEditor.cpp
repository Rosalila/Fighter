#include "GameplayEditor.h"

GameplayEditor::GameplayEditor()
{

}

string GameplayEditor::getHp()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("bar");
            move_node!=NULL;
            move_node=move_node->NextSibling("bar"))
    {
        if(strcmp("hp",move_node->ToElement()->Attribute("variable"))==0)
        {
            return move_node->ToElement()->Attribute("max_value");
        }
    }
    return "Error";
}

void GameplayEditor::setHp(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("bar");
            move_node!=NULL;
            move_node=move_node->NextSibling("bar"))
    {
        if(strcmp("hp",move_node->ToElement()->Attribute("variable"))==0)
        {
            for(TiXmlAttribute* bar_attributes = move_node->ToElement()->FirstAttribute();
                bar_attributes!=NULL;
                bar_attributes=bar_attributes->Next()
                )
            {
                if(strcmp(bar_attributes->Name(),"max_value")==0)
                {
                    string hp = toString(value);
                    if(relative)
                    {
                        hp = toString(atoi(move_node->ToElement()->Attribute("max_value"))+value);
                    }
                    bar_attributes->SetValue(hp.c_str());
                }
            }
            for(TiXmlAttribute* bar_attributes = move_node->ToElement()->FirstAttribute();
                bar_attributes!=NULL;
                bar_attributes=bar_attributes->Next()
                )
            {
                if(strcmp(bar_attributes->Name(),"current_value")==0)
                {
                    string hp = toString(value);
                    if(relative)
                    {
                        hp = toString(atoi(move_node->ToElement()->Attribute("current_value"))+value);
                    }
                    bar_attributes->SetValue(hp.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getSpeedBack()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("walk back",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("velocity_x");
        }
    }
    return "Error";
}

void GameplayEditor::setSpeedBack(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("walk back",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"velocity_x")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("velocity_x"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getSpeedForward()
{
    string character="Mole";
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
            return move_node->ToElement()->Attribute("velocity_x");
        }
    }
    return "Error";
}

void GameplayEditor::setSpeedForward(int value, bool relative)
{
    string character="Mole";
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
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"velocity_x")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("velocity_x"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getSpeedOverhead()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("overhead",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("frame_duration");
        }
    }
    return "Error";
}

void GameplayEditor::setSpeedOverhead(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("overhead",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"frame_duration")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("frame_duration"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getSpeedSlash()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("slash",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("frame_duration");
        }
    }
    return "Error";
}

void GameplayEditor::setSpeedSlash(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("slash",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"frame_duration")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("frame_duration"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getSpeedLow()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("low",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("frame_duration");
        }
    }
    return "Error";
}

void GameplayEditor::setSpeedLow(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("low",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"frame_duration")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("frame_duration"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
        if(strcmp("low2",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"frame_duration")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("frame_duration"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getDamageOverhead()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("overhead",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("damage");
        }
    }
    return "Error";
}

void GameplayEditor::setDamageOverhead(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("overhead",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"damage")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("damage"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getDamageSlash()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("slash",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("damage");
        }
    }
    return "Error";
}

void GameplayEditor::setDamageSlash(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("slash",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"damage")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("damage"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getDamageLow()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("low",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("damage");
        }
    }
    return "Error";
}

void GameplayEditor::setDamageLow(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("low",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"damage")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("damage"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getChipDamageOverhead()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("overhead",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("chip_damage");
        }
    }
    return "Error";
}

void GameplayEditor::setChipDamageOverhead(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("overhead",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"chip_damage")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("chip_damage"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getChipDamageSlash()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("slash",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("chip_damage");
        }
    }
    return "Error";
}

void GameplayEditor::setChipDamageSlash(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("slash",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"chip_damage")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("chip_damage"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getChipDamageLow()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("low",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("chip_damage");
        }
    }
    return "Error";
}

void GameplayEditor::setChipDamageLow(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("low",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"chip_damage")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("chip_damage"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getBlockstunOverhead()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("overhead",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("blockstun");
        }
    }
    return "Error";
}

void GameplayEditor::setBlockstunOverhead(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("overhead",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"blockstun")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("blockstun"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getBlockstunSlash()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("slash",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("blockstun");
        }
    }
    return "Error";
}

void GameplayEditor::setBlockstunSlash(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("slash",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"blockstun")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("blockstun"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getBlockstunLow()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("low",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("blockstun");
        }
    }
    return "Error";
}

void GameplayEditor::setBlockstunLow(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("low",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"blockstun")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("blockstun"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}

string GameplayEditor::getHitstun()
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("on_hit.stand",move_node->ToElement()->Attribute("name"))==0)
        {
            return move_node->ToElement()->Attribute("frames");
        }
    }
    return "Error";
}

void GameplayEditor::setHitstun(int value, bool relative)
{
    string character="Mole";
    string xml_path=assets_directory+"chars/"+character+"/main.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    TiXmlNode* declarations_tag=doc.FirstChild("MainFile")->FirstChild("Declarations");
    for(TiXmlNode* move_node=declarations_tag->FirstChild("Move");
            move_node!=NULL;
            move_node=move_node->NextSibling("Move"))
    {
        if(strcmp("on_hit.stand",move_node->ToElement()->Attribute("name"))==0)
        {
            for(TiXmlAttribute* move_attributes = move_node->ToElement()->FirstAttribute();
                move_attributes!=NULL;
                move_attributes=move_attributes->Next()
                )
            {
                if(strcmp(move_attributes->Name(),"frames")==0)
                {
                    string new_value = toString(value);
                    if(relative)
                    {
                        new_value = toString(atoi(move_node->ToElement()->Attribute("frames"))+value);
                    }
                    move_attributes->SetValue(new_value.c_str());
                }
            }
        }
    }
    doc.SaveFile(xml_path.c_str());
}
