#include "Enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Enemy::Enemy(sf::Vector2f size){
    enemy.setSize(size);
    enemy.setFillColor(sf::Color::Red);
}

void Enemy::draw(sf::RenderWindow* window){
    window->draw(enemy);
}

void Enemy::setPosition(int x, int y){
    enemy.setPosition(x,y);
}
