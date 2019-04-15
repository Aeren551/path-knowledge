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
        Player(sf::Vector2f size, float x, float y);
        virtual ~Player();//
        void draw(sf::RenderWindow* window);
        void setPosition(int x, int y);
        void setPositionC(int x, int y);
        void setPositionE(int x, int y);
        void updatC(float x);
        void updatE(float x);
        //movimiento y animacion

        void eventos (int tecla);       // eventos de teclado
        void actualizarPos (float time);   // cambiar posicion y lastPosicion
        void interpolar (float tick);
        void render (sf::RenderWindow* window);

        sf::Vector2i* getCoordenadas ();
        void setCoordenadas (int width, int height);
        void colisionMapa ();

    protected:
        sf::Vector2f    posicion;       // hacia donde se dirige (INTERPOLACION)
        sf::Vector2f    lastPosicion;   // desde donde parte (INTERPOLACION)
        sf::Vector2f    velocidad;      // vector de velocidad

        sf::Vector2i    source;         // para construir el rectangulo de recorte (ANIMACION)
        sf::Vector2i    coordenadas;    // posicion en el mapa (COLISIONES)
        int cont;

        sf::Texture*    texture;
        sf::Sprite*     sprite;

    private:
        sf::RectangleShape player;
        sf::RectangleShape estres;
        sf::RectangleShape bordere;
        float vale;
        float valem;
        sf::RectangleShape conocimiento;
        sf::RectangleShape borderc;
        float valc;
        float valcm;
};

#endif // PLAYER_H
