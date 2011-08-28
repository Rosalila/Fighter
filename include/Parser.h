class Archivo
{
public:
    ifstream* myfile;
    int iterador;
    std::string linea;
    Archivo(std::string path)
    {
        myfile=new ifstream(path.c_str()); //opening the file.
        iterador=0;
        getline (*myfile,linea);
    }
    char getChar()
    {
        if (myfile->is_open() && !myfile->eof()) //if the file is open
        {
            if(iterador>=(int)linea.length())
            {
                getline (*myfile,linea);
                iterador=0;
                return '\n';
            }
            return linea[iterador++];
        }
        return '\0';
    }
};

class Token
{
public:
    std::string tipo;
    std::string lexema;
    Token(std::string tipo,std::string lexema)
    {
        this->tipo=tipo;
        this->lexema=lexema;
    }
};

class Lexer
{
public:
    vector<Token> tokens;
    int iterador;
    Lexer()
    {
        iterador=0;
    }
    bool quedanTokens()
    {
        return iterador<(int)tokens.size();
    }
    int getIterador()
    {
        return iterador;
    }
    Token getToken()
    {
        if(!quedanTokens())
            return Token("","");
        return tokens[iterador];
    }
    Token nextToken()
    {
        iterador++;
        if(!quedanTokens())
            return Token("","");
        return tokens[iterador];
    }
    void setIterador(int iterador)
    {
        this->iterador=iterador;
    }
    bool esCaracterAscii(char c)
    {
        if((c>=65&&c<=90) || (c>=97&&c<=122))
            return true;
        return false;
    }

    bool esNumeroAscii(char c)
    {
        if(c>=48&&c<=57)
            return true;
        return false;
    }
    void printTokens()
    {
        for(int i=0;i<(int)tokens.size();i++)
            cout<<tokens[i].tipo<<","<<tokens[i].lexema<<endl;
    }
    void tokenizarInput()
    {
        Archivo archivo("input");
        int estado=0;
        std::string lexema="";
        char c=archivo.getChar();
        for(;estado!=-1;)
        {
            switch(estado)
            {
                case 0:
                    lexema+=c;
                    if (c==' ' || c=='\t' || c=='\n')
                        lexema="";
                    else if(esNumeroAscii(c))
                        estado=1;
                    else if(esCaracterAscii(c))
                        estado=2;
                    else if(c=='=')
                        estado=3;
                    else if(c==':')
                        estado=5;
                    else if(c=='\0')
                        estado=-1;
                    else
                        estado=6;
                    c=archivo.getChar();
                break;
                case 1:
                    if(!esNumeroAscii(c))
                    {
                        tokens.push_back(Token("numero",lexema));
                        estado=0;
                        lexema="";
                    }else
                    {
                        lexema+=c;
                        c=archivo.getChar();
                    }
                break;
                case 2:
                    if(!esCaracterAscii(c))
                    {
                        tokens.push_back(Token("id",lexema));
                        estado=0;
                        lexema="";
                    }else
                    {
                        lexema+=c;
                        c=archivo.getChar();
                    }
                break;
                case 3:
                    if(c=='>')
                    {
                        estado=4;
                        lexema+=c;
                        c=archivo.getChar();
                    }
                    else
                        estado=6;
                break;
                case 4:
                    tokens.push_back(Token("puntuacion",lexema));
                    lexema="";
                    estado=0;
                break;
                case 5:
                    tokens.push_back(Token("puntuacion",lexema));
                    lexema="";
                    estado=0;
                break;
                case 6:
                    cout<<"Error lexico";
                    estado=-1;
                break;
            }
        }
    }
};

class Parser
{
public:
    Receiver *receiver;
    Lexer lexer;
    vector<Input*> inputs;
    vector<Boton> botones_temp;
    Boton boton_temp;
    std::string dispositivo;
    Parser()
    {
    }
    bool parseInput(Receiver* receiver)
    {
        this->receiver=receiver;
        lexer.tokenizarInput();
        vector<Boton> botones;
        return S();
//                    botones.push_back(Boton((irr::EKEY_CODE)paramentros[0][0],str));
    }

    bool S()
    {
        Token t=lexer.getToken();
        int iterador=lexer.getIterador();
        if(jugador())
        {
            t=lexer.nextToken();
            if(S())
                return true;
        }
        lexer.setIterador(iterador);
        t=lexer.getToken();
        if(!jugador())
            return false;
        t=lexer.nextToken();
        return !lexer.quedanTokens();
    }

    bool jugador()
    {
        Token t=lexer.getToken();
        if(!tipo())
            return false;
        t=lexer.nextToken();
        if(t.tipo!="puntuacion" || t.lexema!=":")
            return false;
        t=lexer.nextToken();
        botones_temp.clear();
        if(!listaDeDefiniciones())
            return false;
        inputs.push_back(new Input(botones_temp,receiver));
        return true;
    }
    bool tipo()
    {
        Token t=lexer.getToken();
        dispositivo=t.lexema;
        if(t.tipo=="id" && t.lexema=="joystick")
            return true;
        if(t.tipo=="id" && t.lexema=="keyboard")
            return true;
        return false;
    }
    bool listaDeDefiniciones()
    {
        int iterador=lexer.getIterador();
        Token t=lexer.getToken();
        if(definicion())
        {
            Boton boton_temp_aux=boton_temp;
            t=lexer.nextToken();
            if(listaDeDefiniciones())
            {
                botones_temp.push_back(boton_temp_aux);
                return true;
            }
        }
        lexer.setIterador(iterador);
        t=lexer.getToken();
        if(definicion())
            return true;
        botones_temp.push_back(boton_temp);
        return false;
    }
    bool definicion()
    {
        Token t=lexer.getToken();
        std::string mapeado=t.lexema;
        if(t.tipo!="id" && t.tipo!="numero")
            return false;
        t=lexer.nextToken();
        if(t.tipo!="puntuacion" || t.lexema!="=>")
            return false;
        t=lexer.nextToken();
        std::string mapeador=t.lexema;
        if(t.tipo!="id" && t.tipo!="numero")
            return false;
        if(dispositivo=="keyboard")
        {
            boton_temp=Boton((irr::EKEY_CODE)mapeado[0],mapeador.c_str());
        }else if(dispositivo=="joystick")
        {
            if(mapeado=="up")
                boton_temp=Boton(-8,mapeador.c_str());
            else if(mapeado=="down")
                boton_temp=Boton(-2,mapeador.c_str());
            else if(mapeado=="left")
                boton_temp=Boton(-4,mapeador.c_str());
            else if(mapeado=="right")
                boton_temp=Boton(-6,mapeador.c_str());
            else
                boton_temp=Boton(mapeado[0]-48,mapeador.c_str());
        }
        return true;
    }
};
