#include <iostream>
#include "Player.h"

Player::Player(sf::Vector2f size){
    player.setSize(size);
    player.setFillColor(sf::Color::White);

    //Conocimiento
    valc =0;
    valcm=100;
    borderc.setSize(sf::Vector2f(5,5));
    conocimiento.setSize(sf::Vector2f(5,5));
    borderc.setOutlineThickness(0.3);
    borderc.setScale(20,2);
    conocimiento.setScale(0,2);
    conocimiento.setFillColor(sf::Color::Blue);
    borderc.setOutlineColor(sf::Color::White);
    borderc.setFillColor(sf::Color::Transparent);

    //Estres
    vale =0;
    valem = 200;
    bordere.setSize(sf::Vector2f(5,5));
    estres.setSize(sf::Vector2f(5,5));
    bordere.setOutlineThickness(0.3);
    bordere.setScale(20,2);
    estres.setScale(0,2);
    estres.setFillColor(sf::Color::Red);
    bordere.setOutlineColor(sf::Color::White);
    bordere.setFillColor(sf::Color::Transparent);
}

void Player::draw(sf::RenderWindow* window){
    window->draw(player);
    window->draw(conocimiento);
    window->draw(estres);
    window->draw(bordere);
    window->draw(borderc);
}

void Player::setPosition(int x, int y){
    player.setPosition(x,y);
}
void Player::setPositionE(int x, int y){
    estres.setPosition(x,y);
    bordere.setPosition(x,y);
}


void Player::setPositionC(int x, int y){
    conocimiento.setPosition(x,y);
    borderc.setPosition(x,y);
}

void Player::updatE(float x){
    if(x+vale>=valem)
        estres.setScale(20,2);
    else if(x+vale<=0){
            estres.setScale(0,2);
    }else{
        estres.setScale(((x+vale)/valem)*20.f,2);
        vale=x+vale;
        std::cout<<vale<<std::endl;
        }
}

void Player::updatC(float x){
    if(x+valc>=valcm)
        conocimiento.setScale(20,2);
    else if(x+valc<=0){
            conocimiento.setScale(0,2);
    }else{
        conocimiento.setScale(((x+valc)/valcm)*20.f,2);
        valc=x+valc;
        std::cout<<valc<<std::endl;
        }
}


