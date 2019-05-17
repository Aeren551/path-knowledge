#include "Musica.h"

Musica::Musica()
{
    activo = -1;
    n = 3;
    musica = new sf::Music();
    musica->setLoop(true);
}

Musica::~Musica()
{
    delete musica;
    musica = NULL;
}
void Musica::setActivo(int i)
{

    if(i>-1 && i<n && i!=activo)
    {
        if(activo != -1)
            musica->stop();

        switch (i)
        {
            case 0:
                if(!musica->openFromFile("resources/Sounds/0_menu.ogg"))
                {
                    std::cout << "No se ha cargado la musica de Menu" << std::endl;
                }
                else
                {
                    activo = i;
                    musica->play();
                }
            break;
            case 1:
                if(!musica->openFromFile("resources/Sounds/1_mapa.ogg"))
                {
                    std::cout << "No se ha cargado la musica de Mapa" << std::endl;
                }
                else
                {
                    activo = i;
                    musica->play();
                }
            break;
            case 2:
                if(!musica->openFromFile("resources/Sounds/2_combate.ogg"))
                {
                    std::cout << "No se ha cargado la musica de Combate" << std::endl;
                }
                else
                {
                    activo = i;
                    musica->play();
                }
            break;
        }
    }
}


















