#include "Enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Enemy::Enemy(int i)
{
    texture = new sf::Texture();
    if(!texture->loadFromFile("resources/enemigos.png"))
    {
        cout<<"Error con la textura del enemigo"<<endl;
    }
    spriteEnemigo = new sf::Sprite();
    spriteEnemigo->setTexture(*texture);
    spriteEnemigo->setTextureRect(sf::IntRect(0,0,ENEMY_SPRITE_WIDTH,ENEMY_SPRITE_HEIGHT));
    spriteEnemigo->setOrigin(ENEMY_SPRITE_WIDTH/2, ENEMY_SPRITE_HEIGHT/2);

    combatSpriteEnemigo = new sf::Sprite();
    combatSpriteEnemigo->setTexture(*texture);
    combatSpriteEnemigo->setTextureRect(sf::IntRect(0,0,ENEMY_SPRITE_WIDTH,ENEMY_SPRITE_HEIGHT));
    combatSpriteEnemigo->setOrigin(ENEMY_SPRITE_WIDTH/2, ENEMY_SPRITE_HEIGHT/2);
    combatSpriteEnemigo->setPosition(825,425);
    combatSpriteEnemigo->scale(-8, 8);

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
            spriteEnemigo->scale(-1, 1);

        break;

        case 3:
            posicion = sf::Vector2f(16*43, 16*28);
            spriteEnemigo->scale(-1, 1);

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
        cout<<"Soy enemigo y detecto combate"<<endl;
        return true;
    }
    return false;
}

int Enemy::getVida()
{
    return vida;
}

void Enemy::sumaVida()
{
    vida += 2;
}

void Enemy::restaVida()
{
    vida -= 2;
}

sf::Sprite* Enemy::getCombatSprite()
{
    return combatSpriteEnemigo;
}

void Enemy::drawInMap(sf::RenderWindow* window)
{
    window->draw(*spriteEnemigo);
}
