#include "Personaje/Paleta.h"

void Paleta::cargarXML(char* archivo,int num_paleta)
{
    TiXmlDocument doc_t(archivo);
    doc_t.LoadFile();
    TiXmlDocument*doc=&doc_t;
    TiXmlNode* palettes_file=doc->FirstChild("PalettesFile");
    int i=1;
    for(TiXmlNode* palette=palettes_file->FirstChild("Palette");
            palette!=NULL;
            palette=palette->NextSibling("Palette"))
    {
        if(i!=num_paleta)
        {
            i++;
            continue;
        }
        for(TiXmlNode* c_change=palette->FirstChild("ColorChange");
                c_change!=NULL;
                c_change=c_change->NextSibling("ColorChange"))
        {
            TiXmlElement* max_color=c_change->FirstChild("MaxColor")->ToElement();
            TiXmlElement* min_color=c_change->FirstChild("MinColor")->ToElement();
            TiXmlElement* change=c_change->FirstChild("Change")->ToElement();
            CambioColor cambio_color(SColor(atoi(max_color->Attribute("alpha")),atoi(max_color->Attribute("red")),atoi(max_color->Attribute("green")),atoi(max_color->Attribute("blue"))),
                                     SColor(atoi(min_color->Attribute("alpha")),atoi(min_color->Attribute("red")),atoi(min_color->Attribute("green")),atoi(min_color->Attribute("blue"))),
                                     atoi(change->Attribute("alpha")),
                                     atoi(change->Attribute("red")),
                                     atoi(change->Attribute("green")),
                                     atoi(change->Attribute("blue"))
                                     );
            cambios.push_back(cambio_color);
        }
        break;
    }
}

ITexture* Paleta::paintTexture(ITexture* texture)
{
    for(int i=0;i<(int)cambios.size();i++)
    {
        CambioColor cambio=cambios[i];
        int a_min=cambio.color_min.getAlpha();
        int a_max=cambio.color_max.getAlpha();
        int r_min=cambio.color_min.getRed();
        int r_max=cambio.color_max.getRed();
        int g_min=cambio.color_min.getGreen();
        int g_max=cambio.color_max.getGreen();
        int b_min=cambio.color_min.getBlue();
        int b_max=cambio.color_max.getBlue();

        int modificacion_a=cambio.cambio_a;
        int modificacion_r=cambio.cambio_r;
        int modificacion_g=cambio.cambio_g;
        int modificacion_b=cambio.cambio_b;

        if(r_min<0)r_min=0;
        if(r_max>255)r_max=255;
        if(a_min<0)a_min=0;
        if(a_max>255)a_max=255;
        if(g_min<0)g_min=0;
        if(g_max>255)g_max=255;
        if(b_min<0)b_min=0;
        if(b_max>255)b_max=255;

        copia=new s32[texture->getSize().Width*texture->getSize().Height];
        // update texture with color
        s32* p = (s32*)texture->lock();
        for(s32 i=0; i<texture->getSize().Width*texture->getSize().Height; i++)
        {
            copia[i]=p[i];
            //verficacion
            SColor actual(p[i]);

           if(actual.getAlpha()>=a_min && actual.getAlpha()<=a_max
              && actual.getRed()>=r_min && actual.getRed()<=r_max
              && actual.getGreen()>=g_min && actual.getGreen()<=g_max
              && actual.getBlue()>=b_min && actual.getBlue()<=b_max
              )
           {
               int nuevo_a=actual.getAlpha()+modificacion_a;
               int nuevo_r=actual.getRed()+modificacion_r;
               int nuevo_g=actual.getGreen()+modificacion_g;
               int nuevo_b=actual.getBlue()+modificacion_b;
               if(nuevo_a<0)nuevo_a=0;
               if(nuevo_r<0)nuevo_r=0;
               if(nuevo_g<0)nuevo_g=0;
               if(nuevo_b<0)nuevo_b=0;
               if(nuevo_a>255)nuevo_a=255;
               if(nuevo_r>255)nuevo_r=255;
               if(nuevo_g>255)nuevo_g=255;
               if(nuevo_b>255)nuevo_b=255;
               actual.setAlpha(nuevo_a);
               actual.setRed(nuevo_r);
               actual.setGreen(nuevo_g);
               actual.setBlue(nuevo_b);

               p[i]=actual.color;
           }
        }
        texture->unlock();
    }
}

ITexture* Paleta::restoreTexture(ITexture* texture)
{
    s32* p = (s32*)texture->lock();
    p=copia;
    texture->unlock();
}
