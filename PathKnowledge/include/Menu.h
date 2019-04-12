#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>



class Menu
{
    public:
        Menu();
        virtual ~Menu();
        int menuInicio(sf::RenderWindow* window);
        int menuPause(sf::RenderWindow* window);

    protected:

    private:
};

#endif // MENU_H
