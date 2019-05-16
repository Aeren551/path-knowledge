#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Estados.h"

using namespace std;

class Menu
{
    public:
        Menu();
        virtual ~Menu();
        int menuInicio(sf::RenderWindow* w);
        int menuPause(sf::RenderWindow* w);

    protected:

    private:
        sf::RenderWindow* window;
        int width, height;

        sf::Texture t_fondo;
        sf::Texture t_marco;
        sf::Texture t_fondo_b1;
        sf::Texture t_fondo_b2;

        sf::Sprite marco;
        sf::Sprite fondo;

        int objetoSeleccionado;
        int numObjetos; // numero de objetos en el menu
        sf::Font fuente; // fuente de la letra
        sf::Text* menuObjetos; // objetos del menu
        sf::Text titulo;
        sf::Text titulo_sombra;

        void moveUp();
        void moveDown();
        void marcarSeleccionado();
        void dibujar();

        void creditos();
        void ayuda();
};

#endif // MENU_H
