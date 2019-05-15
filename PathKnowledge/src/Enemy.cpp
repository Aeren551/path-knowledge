#include "Enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Enemy::Enemy(int i)
{
    texture = new sf::Texture();
    if(!texture->loadFromFile("resources/log.png"))
    {
        cout<<"Error con la textura del enemigo"<<endl;
    }
    spriteEnemigo = new sf::Sprite();
    spriteEnemigo->setTexture(*texture);
    spriteEnemigo->setTextureRect(sf::IntRect(0,0,32,32));
    spriteEnemigo->setOrigin(16,16);

    switch(i)
    {
        case 0:
            posicion = sf::Vector2f(16*35, 16*20);
        break;

        case 1:
            posicion = sf::Vector2f(16*26, 16*40);
        break;

        case 2:
            posicion = sf::Vector2f(16*25, 16*18);
        break;

        case 3:
            posicion = sf::Vector2f(16*43, 16*28);
        break;

        case 4:
            posicion = sf::Vector2f(16*60, 16*15);
        break;
    }

    spriteEnemigo->setPosition(posicion);
}

Enemy::~Enemy()
{
    delete spriteEnemigo;
    spriteEnemigo = NULL;
    delete texture;
    texture = NULL;
}

bool Enemy::colision(sf::Sprite* jugador)
{
    if(spriteEnemigo->getGlobalBounds().intersects(jugador->getGlobalBounds()))
    {
        cout<<"COMBATE!!"<<endl;
        return true;
    }
    return false;
}

void Enemy::drawInMap(sf::RenderWindow* window)
{
    window->draw(*spriteEnemigo);
}
