#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Combate.h"
#include "Enemy.h"
#include "Buttons.h"

using namespace std;

#define UPDATE_TICK_TIME 1000/15


int Combate(sf::RenderWindow* window){
    sf::Clock textti;
    sf::Clock clock;//Reloj de juego
    sf::Time time = textti.getElapsedTime();
    int turno=0;
    //Creamos una ventana
    sf::Font font;
    sf::Text text;
    sf::Text hp;
    sf::Text exp;
    font.loadFromFile("Pixeled.ttf");
    text.setFont(font);
    hp.setFont(font);
    exp.setFont(font);
    text.setColor(sf::Color::White);
    hp.setColor(sf::Color::Red);
    exp.setColor(sf::Color::Blue);
    text.setCharacterSize(25);
    text.setPosition(200,100);
    Player player(sf::Vector2f(75,75));//Cambiar por Sprite
    Enemy enemy(sf::Vector2f(100,100));//Cambiar por Sprite
    Buttons buttons(sf::Vector2f(90,125));
    player.setPosition(100,200);
    enemy.setPosition(480,187);
    player.setPositionE(50,100);
    hp.setPosition(5,100);
    hp.setCharacterSize(10);
    player.setPositionC(50,150);
    exp.setPosition(5,150);
    exp.setCharacterSize(10);
    hp.setString("Est.");
    exp.setString("Con.");



    //Bucle del juego
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if(clock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
        {
            if(turno==0){
            if(sf::Event::Closed)
                window->close();
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {

            }

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {

            }

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                buttons.cursor(-1);
            }

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                buttons.cursor(1);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window->close();
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                window->close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && turno==0){
                int act = buttons.getOption();
               switch(act){
                    case 1:
                        text.setString("Has atacado");
                        player.updatC(5.f);
                        textti.restart();
                        turno=3;
                        buttons.changeTurn();
                        break;
                    case 2:
                        text.setString("Has usado Skill");
                        textti.restart();
                        turno=2;
                        buttons.changeTurn();
                        break;
                    case 3:
                        text.setString("Has usado Items");
                        player.updatE(-20.f);
                        textti.restart();
                        turno=3;
                        buttons.changeTurn();
                        break;
                    case 4:
                        text.setString("Has usado Flee");
                        textti.restart();
                        turno=3;
                        buttons.changeTurn();
                        break;
                }
                }
            }
           else if(turno==2){
                time = textti.getElapsedTime();
                text.setString("Menu Skills");
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    turno=3;
                    textti.restart();
                }

            }
            else if(turno==3){
                time = textti.getElapsedTime();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    text.setString("Te Estresas");
                    player.updatE(10.f);
                    turno=4;
                    textti.restart();
                }

            }
            else if(turno==4){
                time = textti.getElapsedTime();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    text.setString("");
                    buttons.changeTurn();
                    turno=0;
                    textti.restart();
                }

            }
        }
        clock.restart();

        }
        window->clear();
        time = textti.getElapsedTime();
        if(turno==0)
            text.setString("");
        player.draw(window);
        enemy.draw(window);
        window->draw(text);
        window->draw(hp);
        window->draw(exp);
        if(buttons.getTurn()){
            buttons.draw(window);
        }
        window->display();
    }

    return 0;
}


int main()
{
    // Create the main window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(640, 480), "Path of Knowledge");
    window->setFramerateLimit(60);
    Player player();

    // Process events
    sf::Event event;
    //Reloj del juego
    sf::Clock clock;

	// Start the game loop
    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                    window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code== sf::Keyboard::Escape)
                window->close();

        }

        if(clock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
        {
            if(true){
                Combate(window);
            }
            clock.restart();
        }

        window->clear();
        window->display();
    }

    return EXIT_SUCCESS;
}


