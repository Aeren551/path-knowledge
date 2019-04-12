#include "menu_pause.h"

#include <iostream>
#include <string>

menu_pause::menu_pause(float width, float height)
{
    menuObjetos[0].setString("CONTINUAR");
    menuObjetos[1].setString("SALIR");

    fuente.loadFromFile("fonts/Triforce.ttf");
    for (int i=0; i<MAX_ITEM_NUM; i++)
    {
        menuObjetos[i].setFont(fuente);
        menuObjetos[i].setColor(sf::Color::Green);
        menuObjetos[i].setPosition(sf::Vector2f((width/2)-(menuObjetos[i].getLocalBounds().width/2), height/(MAX_ITEM_NUM+1)*(i+1)));
    }

    objetoSeleccionado = 0;
    marcarSeleccionado();
    operativo = false;
}

menu_pause::~menu_pause()
{
    //dtor
}

void menu_pause::marcarSeleccionado()
{
    for(int i = 0; i<MAX_ITEM_NUM; i++)
    {
        menuObjetos[i].setColor(sf::Color::White);
        menuObjetos[i].setStyle(sf::Text::Regular);
    }
    menuObjetos[objetoSeleccionado].setColor(sf::Color::Green);
    menuObjetos[objetoSeleccionado].setStyle(sf::Text::Bold);
    menuObjetos[objetoSeleccionado].setStyle(sf::Text::Italic);
}

void menu_pause::dibujar(sf::RenderWindow &window)
{
    if (operativo)
    {
        for (int i=0; i<MAX_ITEM_NUM; i++)
        {
            window.draw(menuObjetos[i]);
        }
    }
}

void menu_pause::moveUp()
{
    if(operativo && objetoSeleccionado > 0)
    {
        --objetoSeleccionado;
        marcarSeleccionado();
    }
}

void menu_pause::moveDown()
{
    if(operativo && objetoSeleccionado < MAX_ITEM_NUM-1)
    {
        ++objetoSeleccionado;
        marcarSeleccionado();
    }
}

int menu_pause::getSeleccionado()
{
    return objetoSeleccionado;
}

std::string menu_pause::getSeleccionado_texto()
{
    return menuObjetos[objetoSeleccionado].getString();
}

int menu_pause::gestorEventos(int tecla)
{
    int salida = 0;
    switch(tecla)
    {
        case sf::Keyboard::Up:
            moveUp();
            break;
        case sf::Keyboard::Down:
            moveDown();
            break;
        case sf::Keyboard::Return:
            std::cout << "Accediendo al menu: " << getSeleccionado() << " -> " << getSeleccionado_texto() << std::endl;
            break;
        case sf::Keyboard::Escape:
            setOperativo();
            break;
    }
    return salida;
}

void menu_pause::setOperativo ()
{
    if(operativo)
    {
        reiniciar();
    }
    else
        operativo = true;
}
void menu_pause::reiniciar ()
{
    objetoSeleccionado = 0;
    marcarSeleccionado();
    operativo = false;
}

