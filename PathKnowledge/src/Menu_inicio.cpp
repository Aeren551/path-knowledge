#include "menu_inicio.h"
#include <iostream>
#include <string>

menu_inicio::menu_inicio(float width, float height)
{
    menuObjetos[0].setString("JUGAR");
    menuObjetos[1].setString("Ayuda");
    menuObjetos[2].setString("Creditos");
    menuObjetos[3].setString("SALIR");

    fuente.loadFromFile("fonts/Triforce.ttf");
    for (int i=0; i<MAX_ITEM_NUM; i++)
    {
        menuObjetos[i].setFont(fuente);
        menuObjetos[i].setColor(sf::Color::Green);
        menuObjetos[i].setPosition(sf::Vector2f((width/2)-(menuObjetos[i].getLocalBounds().width/2), height/(MAX_ITEM_NUM+1)*(i+1)));
    }

    objetoSeleccionado = 0;
    marcarSeleccionado();
}

menu_inicio::~menu_inicio()
{
    //dtor
}

void menu_inicio::marcarSeleccionado()
{
    menuObjetos[objetoSeleccionado].setColor(sf::Color::Red);
}

void menu_inicio::dibujar(sf::RenderWindow &window)
{
    for (int i=0; i<MAX_ITEM_NUM; i++)
    {
        window.draw(menuObjetos[i]);
    }
}

void menu_inicio::moveUp()
{
    if(objetoSeleccionado > 0)
    {
        menuObjetos[objetoSeleccionado].setColor(sf::Color::Green);
        --objetoSeleccionado;
        menuObjetos[objetoSeleccionado].setColor(sf::Color::Red);
    }
}

void menu_inicio::moveDown()
{
    if(objetoSeleccionado < MAX_ITEM_NUM-1)
    {
        menuObjetos[objetoSeleccionado].setColor(sf::Color::Green);
        ++objetoSeleccionado;
        menuObjetos[objetoSeleccionado].setColor(sf::Color::Red);
    }
}

int menu_inicio::getSeleccionado()
{
    return objetoSeleccionado;
}

std::string menu_inicio::getSeleccionado_texto()
{
    return menuObjetos[objetoSeleccionado].getString();
}

int menu_inicio::gestorEventos(int tecla)
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
            salida=-1;
            break;
    }
    return salida;
}
