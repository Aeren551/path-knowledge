#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Combate.h"
#include "Enemy.h"
#include "Buttons.h"
#include "Mapa.h"
#include "Estados.h"

using namespace std;

#define UPDATE_TICK_TIME 1000/15
int main()
{

    //=============ESTO HAY QUE BORRARLO DE AQUI=============
    //Creamos una ventana
    Player player(sf::Vector2f(75,75));//Cambiar por Sprite
    Enemy enemy(sf::Vector2f(100,100));//Cambiar por Sprite
    //=======================================================







    // Create the main window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(640, 480), "Path of Knowledge");
    window->setFramerateLimit(60);
    //Player player();

    // Process events
    sf::Event event;
    //Reloj del juego
    sf::Clock clock;
    Combate* combate = new Combate(player,enemy);
    //maquina de estados (0 menu principal)
    Estados * estado = Estados::Instance();

    Mapa * mapa = Mapa::Instance();
    mapa->leerTMX();

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
            switch (estado->getEstado())
            {
                case 0:
                //MENU INICIO
                break;

                case 1:
                //EN JUEGO
                window->clear();
                mapa->setActiveLayer(0);
                mapa->render(window);
                mapa->setActiveLayer(1);
                mapa->render(window);

                //PERSONAJE

                mapa->setActiveLayer(2);
                mapa->render(window);
                mapa->setActiveLayer(3);
                mapa->render(window);
                window->display();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    estado->setEstado(2);
                }

                break;

                case 2:
                combate->start(window);
                //combate->render(window);
                break;
            }
         clock.restart();
        }
    }

    return EXIT_SUCCESS;
}


