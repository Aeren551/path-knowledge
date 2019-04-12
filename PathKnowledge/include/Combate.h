#ifndef COMBATE_H
#define COMBATE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Buttons.h"

#define UPDATE_TICK_TIME 1000/15

class Combate
{
    public:
        Combate();
        virtual ~Combate();
        int start(sf::RenderWindow* window);

    protected:

    private:
};

#endif // COMBATE_H
