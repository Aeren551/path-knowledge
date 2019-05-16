#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Combate.h"
#include "Enemy.h"
#include "Buttons.h"
#include "Mapa.h"
#include "Estados.h"
#include "Menu.h"
#include <vector>

using namespace std;

#define UPDATE_TICK_TIME 1000/15
int main()
{

    // Create the main window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Path of Knowledge");
    window->setFramerateLimit(60);

    // Process events
    sf::Event event;
    //Reloj del juego
    sf::Clock clock;

    Menu* menu = new Menu();
    //maquina de estados (0 menu principal)
    Estados * estado = Estados::Instance();
    //creamos personaje
    Player* jugador = new Player();
    Combate * combate;
    vector<Enemy*> enemigos;
    for(int i = 0; i < 5; i++)
    {
        Enemy *enemiguito = new Enemy(i);
        enemigos.push_back(enemiguito);
    }

    //Combate* combate = new Combate(jugador,enemy);
    float percentTick = 1000/15;
    bool entroCombate = true;

    Mapa * mapa = new Mapa();
    mapa->leerTMX();

    // creacion de vistas
    sf::View player_view(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
    sf::View battle(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
    player_view.zoom(0.5f);

	// Start the game loop
    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                    window->close();
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

                    //se mantiene la vista centrada en el personaje
                    player_view.setCenter(jugador->getPosition()->x, jugador->getPosition()->y);
                    window->setView(player_view);

                    //==============================Movimiento================================
                    jugador->eventos();
                    jugador->actualizarPos(clock.getElapsedTime().asMilliseconds());
                    jugador->setCoordenadas(mapa->getTileWidth(), mapa->getTileHeight());

                    if(mapa->colision(jugador->getCoordenadas()->x, jugador->getCoordenadas()->y))
                    {
                        jugador->colisionMapa();
                        jugador->setCoordenadas(mapa->getTileWidth(), mapa->getTileHeight());
                    }
                    jugador->interpolar(percentTick);
                    for(int i = 0; i < enemigos.size(); i++)
                    {
                        if(enemigos[i]->colision(jugador->getSprite()))
                        {
                            combate = new Combate(jugador, enemigos[i]);
                            enemigos.erase(enemigos.begin()+i);
                            estado->setEstado(2);
                        }
                    }
                    //=========================================================================

                    //==============================Cambiar estados============================
                    // MENU PAUSE
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        //std::cout << "entrar en el menu pause" << std::endl;
                        estado->setEstado(3);
                    }
                    //=========================================================================

                    //==================================Render(sacarlo fuera)=================================
                    window->clear();
                    mapa->setActiveLayer(0);
                    mapa->render(window);

                    mapa->setActiveLayer(1);
                    mapa->render(window);

                    mapa->setActiveLayer(2);
                    mapa->render(window);

                    jugador->render(window);
                    for(int i = 0; i < enemigos.size(); i++)
                        enemigos[i]->drawInMap(window);

                    mapa->setActiveLayer(3);
                    mapa->render(window);
                    mapa->setActiveLayer(4);
                    mapa->render(window);

                    jugador->HUD(window);

                    window->display();

                break;

                case 2:
                    //COMBATE
                    window->setView(battle);
                    combate->compruebaFin();
                    combate->input(window);

                    //sacar fuera el render
                    window->clear();
                    combate->render(window);
                    window->display();


                break;

                case 3:
                    window->setView(battle);
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


