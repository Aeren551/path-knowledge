#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player(sf::Vector2f size);
        void draw(sf::RenderWindow* window);
        void setPosition(int x, int y);
        void setPositionC(int x, int y);
        void setPositionE(int x, int y);
        void updatC(float x);
        void updatE(float x);

    protected:

    private:
        sf::RectangleShape player;
        sf::RectangleShape estres;
        sf::RectangleShape bordere;
        float vale;
        float valem;
        sf::RectangleShape conocimiento;
        sf::RectangleShape borderc;
        float valc;
        float valcm;
};

#endif // PLAYER_H
