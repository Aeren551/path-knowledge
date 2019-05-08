#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Estados.h"



class Menu
{
    public:
        Menu();
        virtual ~Menu();
        int menuInicio(sf::RenderWindow* window);
        int menuPause(sf::RenderWindow* window);

    protected:

    private:
        int objetoSeleccionado;
        int numObjetos; // numero de objetos en el menu
        sf::Font fuente; // fuente de la letra
        sf::Text* menuObjetos; // objetos del menu

        void moveUp();
        void moveDown();
        void marcarSeleccionado();
        void dibujar(sf::RenderWindow* window);
};

#endif // MENU_H
