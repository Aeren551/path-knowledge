#ifndef COMBATE_H
#define COMBATE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Estados.h"

#define UPDATE_TICK_TIME 1000/15

class Combate
{
    public:
        Combate(Player* p,Enemy *e);
        virtual ~Combate();
        void input(sf::RenderWindow* window);
        void render(sf::RenderWindow* window);
        void marcarSeleccionado();
    protected:

    private:
        //VARIABLES
        Player* player;
        Enemy* enemy;

        sf::Clock relojInput;
        sf::Sprite* spriteJugador;
        sf::Sprite* spriteEnemigo;

        sf::Texture* textura;
        sf::Sprite* barraVidaEnemigo;
        sf::Sprite* vidaEnemigo;

        sf::Texture* texturaFondo;
        sf::Sprite* spriteFondo;

        sf::Font* fuenteCombate;
        sf::Text* menuCombate;

        int objetoSeleccionado = 0;

        //FUNCIONES
        void moveRight();
        void moveLeft();
        void ejecutarAccion();


};

#endif // COMBATE_H
