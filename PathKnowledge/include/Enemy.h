#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy
{
    public:
        Enemy(sf::Vector2f size);
        void draw(sf::RenderWindow* window);
        void setPosition(int x, int y);

    protected:

    private:
        sf::RectangleShape enemy;
};

#endif // ENEMY_H
