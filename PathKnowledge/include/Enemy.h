#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <SFML/Graphics.hpp>

#define ENEMY_SPRITE_WIDTH    24
#define ENEMY_SPRITE_HEIGHT   32

using namespace std;

class Enemy
{
    public:
        Enemy(int i);
        virtual ~Enemy();
        void drawInMap(sf::RenderWindow* window);
        bool colision(sf::Sprite* jugador);
        sf::Sprite* getCombatSprite();
        int getVida();
        void sumaVida();
        void restaVida();
    protected:

    private:
        sf::Texture* texture;
        sf::Sprite* spriteEnemigo;
        sf::Sprite* combatSpriteEnemigo;
        sf::Vector2f posicion;

        int vida = 52;
};

#endif // ENEMY_H
