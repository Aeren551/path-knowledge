#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#define MAX_VELOCIDAD   0.1f
#define SPRITE_WIDTH    16
#define SPRITE_HEIGHT   32

class Player
{
    public:
        Player();
        virtual ~Player();
        void draw(sf::RenderWindow* window);
        //movimiento y animacion
        void eventos(); // eventos de teclado
        void actualizarPos (float time);   // cambiar posicion y lastPosicion
        void interpolar (float tick);
        void render (sf::RenderWindow* window);
        void HUD(sf::RenderWindow* window);

        sf::Vector2i* getCoordenadas ();
        sf::Vector2f* getPosition();
        sf::Sprite* getSprite();
        sf::Sprite* getCombatSprite();
        void setCoordenadas (int width, int height);
        void colisionMapa();
        void ganaConocimiento();

    protected:


    private:
        sf::Texture* texture;
        sf::Sprite* sprite;
        sf::Sprite* combatSprite;
        sf::Sprite* spriteBarras;
        sf::Sprite* rellenoEstresSprite;
        sf::Sprite* rellenoConocimientoSprite;

        sf::Vector2f    posicionBarraEstres;
        sf::Vector2f    posicionRellenoEstres;
        sf::Vector2f    posicionRellenoConocimiento;
        sf::Vector2f    posicion;       // hacia donde se dirige (INTERPOLACION)
        sf::Vector2f    lastPosicion;   // desde donde parte (INTERPOLACION)
        sf::Vector2f    velocidad;      // vector de velocidad

        sf::Vector2i    source;         // para construir el rectangulo de recorte (ANIMACION)
        sf::Vector2i    coordenadas;    // posicion en el mapa (COLISIONES)

        int conocimiento = 0, estres = 0;
};

#endif // PLAYER_H
