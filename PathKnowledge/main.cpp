#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Combate.h"
#include "Enemy.h"
#include "Buttons.h"
#include "Mapa.h"
#include "Estados.h"
#include "Menu.h"

using namespace std;

#define UPDATE_TICK_TIME 1000/15
int main()
{

    //=============ESTO HAY QUE BORRARLO DE AQUI=============
    //Creamos una ventana
    Player player(0,0);//Cambiar por Sprite
    Enemy enemy(sf::Vector2f(100,100));//Cambiar por Sprite
    //=======================================================

    // Create the main window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Path of Knowledge");
    window->setFramerateLimit(60);
    //Player player();

    // Process events
    sf::Event event;
    //Reloj del juego
    sf::Clock clock;
    Combate* combate = new Combate(player,enemy);
    Menu* menu = new Menu();
    //maquina de estados (0 menu principal)
    Estados * estado = Estados::Instance();

    //creamos personaje
    // boorrar el vector mas adelante
    Player* jugador = new Player(304.0,288.0);
    float percentTick = 1000/15;

    Mapa * mapa = Mapa::Instance();
    mapa->leerTMX();

    // creacion de la vista del personaje con el zoom
    sf::View player_view(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
    sf::View battle(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
    player_view.zoom(0.4f);

	// Start the game loop
    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                    window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code== sf::Keyboard::Escape)
            {
                // para evitar que se cierre, escape tiene que llevar al menu pause
                //window->close();
            }

        }

        if(clock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
        {
            switch (estado->getEstado())
            {
                case 0:
                //MENU INICIO
                menu->menuInicio(window);
                break;

                case 1:
                //EN JUEGO

                window->clear();

                //se mantiene la vista centrada en el personaje
                player_view.setCenter(jugador->getPosition()->x, jugador->getPosition()->y);
                window->setView(player_view);

                mapa->setActiveLayer(0);
                mapa->render(window);
                mapa->setActiveLayer(1);
                mapa->render(window);



                //PERSONAJE

                //movimiento
                jugador->eventos(event.key.code);
                jugador->actualizarPos(clock.getElapsedTime().asMilliseconds());
                jugador->setCoordenadas(mapa->getTileWidth(), mapa->getTileHeight());

                if(mapa->colision(jugador->getCoordenadas()->x, jugador->getCoordenadas()->y))
                {
                    jugador->colisionMapa();
                    jugador->setCoordenadas(mapa->getTileWidth(), mapa->getTileHeight());
                }



                jugador->interpolar(percentTick);



                mapa->setActiveLayer(2);
                mapa->render(window);
                jugador->render(window);
                mapa->setActiveLayer(3);
                mapa->render(window);
                window->display();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                {
                    estado->setEstado(2);
                    window->setView(battle);
                }
                // MENU PAUSE
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    //std::cout << "entrar en el menu pause" << std::endl;
                    estado->setEstado(3);
                    window->setView(battle);
                }

                break;

                case 2:
                combate->start(window);
                //combate->render(window);
                break;
                case 3:
                menu->menuPause(window);
                break;
            }
         clock.restart();
        }
        percentTick = clock.getElapsedTime().asMilliseconds()/UPDATE_TICK_TIME;
        if (percentTick > 1.0f)
            percentTick = 1.0f;
    }


    return EXIT_SUCCESS;
}


