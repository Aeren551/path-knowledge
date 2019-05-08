#ifndef BUTTONS_H
#define BUTTONS_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Buttons
{
    public:
        Buttons(sf::Vector2f size);
        void draw(sf::RenderWindow* window);
        void skills(sf::RenderWindow* window);
        void setPosition(int x, int y);
        void cursor(int x);
        int getOption();
        bool getTurn();
        void changeTurn();
        void cursoren();

    protected:

    private:
        sf::RectangleShape attack;
        sf::RectangleShape skill;
        sf::RectangleShape items;
        sf::RectangleShape flee;
        sf::Font font;
        sf::Text text[4];
        int opt;
        bool turn;
};

#endif // BUTTONS_H
