#ifndef COMBATE_H
#define COMBATE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Buttons.h"
#include "Estados.h"

#define UPDATE_TICK_TIME 1000/15

class Combate
{
    public:
        Combate(Player* p,Enemy e);
        virtual ~Combate();
        void start(sf::RenderWindow* window);
        void render(sf::RenderWindow* window);
    protected:

    private:
        Player* player;
        Enemy enemy;
        int turno;
        Buttons buttons;
        sf::Font font;
        sf::Text text;
        sf::Text hp;
        sf::Text exp;
        int anima=0;
};

#endif // COMBATE_H
