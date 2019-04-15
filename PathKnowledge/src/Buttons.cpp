#include "Buttons.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Buttons::Buttons(sf::Vector2f size)
{
    turn = true;
    font.loadFromFile("Pixeled.ttf");
    text[0].setFont(font);
    text[1].setFont(font);
    text[2].setFont(font);
    text[3].setFont(font);
    opt=1;
    attack.setSize(size);
    attack.setOutlineThickness(1);
    attack.setFillColor(sf::Color::Transparent);
    attack.setOutlineColor(sf::Color::Red);
    attack.setPosition(80,400);
    text[0].setString("Atk.");
    text[0].setCharacterSize(18);
    text[0].setColor(sf::Color::White);
    text[0].setPosition(85,430);

    skill.setSize(size);
    skill.setOutlineThickness(1);
    skill.setFillColor(sf::Color::Transparent);
    skill.setOutlineColor(sf::Color::White);
    skill.setPosition(190,400);
    text[1].setString("Skill");
    text[1].setCharacterSize(18);
    text[1].setColor(sf::Color::White);
    text[1].setPosition(195,430);

    items.setSize(size);
    items.setOutlineThickness(1);
    items.setFillColor(sf::Color::Transparent);
    items.setOutlineColor(sf::Color::White);
    items.setPosition(300,400);
    text[2].setString("Items");
    text[2].setCharacterSize(18);
    text[2].setColor(sf::Color::White);
    text[2].setPosition(305,430);

    flee.setSize(size);
    flee.setOutlineThickness(1);
    flee.setFillColor(sf::Color::Transparent);
    flee.setOutlineColor(sf::Color::White);
    flee.setPosition(410,400);
    text[3].setString("Flee");
    text[3].setCharacterSize(18);
    text[3].setColor(sf::Color::White);
    text[3].setPosition(415,430);
}

void Buttons::draw(sf::RenderWindow* window){
    window->draw(attack);
    window->draw(skill);
    window->draw(items);
    window->draw(flee);
    window->draw(text[0]);
    window->draw(text[1]);
    window->draw(text[2]);
    window->draw(text[3]);
}


void Buttons::cursor(int x){
    opt+=x;
    if(opt<=0)
        opt=4;
    else if(opt>=5)
        opt=1;
    switch(opt){
        case 1:
            attack.setOutlineColor(sf::Color::Red);
            skill.setOutlineColor(sf::Color::White);
            items.setOutlineColor(sf::Color::White);
            flee.setOutlineColor(sf::Color::White);
            break;
        case 2:
            attack.setOutlineColor(sf::Color::White);
            skill.setOutlineColor(sf::Color::Red);
            items.setOutlineColor(sf::Color::White);
            flee.setOutlineColor(sf::Color::White);
            break;
        case 3:
            attack.setOutlineColor(sf::Color::White);
            skill.setOutlineColor(sf::Color::White);
            items.setOutlineColor(sf::Color::Red);
            flee.setOutlineColor(sf::Color::White);
            break;
        case 4:
            attack.setOutlineColor(sf::Color::White);
            skill.setOutlineColor(sf::Color::White);
            items.setOutlineColor(sf::Color::White);
            flee.setOutlineColor(sf::Color::Red);
            break;
    }
}

void Buttons::cursoren(){
    if(opt<=0)
        opt=4;
    else if(opt>=5)
        opt=1;
    switch(opt){
        case 1:
            attack.setOutlineColor(sf::Color::Black);
            skill.setOutlineColor(sf::Color::White);
            items.setOutlineColor(sf::Color::White);
            flee.setOutlineColor(sf::Color::White);
            break;
        case 2:
            attack.setOutlineColor(sf::Color::White);
            skill.setOutlineColor(sf::Color::Black);
            items.setOutlineColor(sf::Color::White);
            flee.setOutlineColor(sf::Color::White);
            break;
        case 3:
            attack.setOutlineColor(sf::Color::White);
            skill.setOutlineColor(sf::Color::White);
            items.setOutlineColor(sf::Color::Black);
            flee.setOutlineColor(sf::Color::White);
            break;
        case 4:
            attack.setOutlineColor(sf::Color::White);
            skill.setOutlineColor(sf::Color::White);
            items.setOutlineColor(sf::Color::White);
            flee.setOutlineColor(sf::Color::Black);
            break;
    }
}

int Buttons::getOption(){
    return opt;
}
bool Buttons::getTurn(){
    return turn;
}
void Buttons::changeTurn(){
    if(turn)
        turn = false;
    else
        turn = true;
}
