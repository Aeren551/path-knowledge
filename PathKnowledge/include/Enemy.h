#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Enemy
{
    public:
        Enemy(int i);
        virtual ~Enemy();
        void drawInMap(sf::RenderWindow* window);
        bool colision(sf::Sprite* jugador);

    protected:

    private:
        sf::Texture *texture;
        sf::Sprite *spriteEnemigo;
        sf::Vector2f posicion;
};

#endif // ENEMY_H
