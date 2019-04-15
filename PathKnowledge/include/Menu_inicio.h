#ifndef MENU_INICIO_H
#define MENU_INICIO_H

#include <SFML/Graphics.hpp>
#include <string>

#define MAX_ITEM_NUM 4


class menu_inicio
{
    public:
        menu_inicio(float width, float height);
        virtual ~menu_inicio();

        void dibujar(sf::RenderWindow &window); // ponerlo aqui o en el main...

        void moveUp ();
        void moveDown ();
        int getSeleccionado();
        std::string getSeleccionado_texto();

        int gestorEventos(int tecla);
    protected:
    private:

        int objetoSeleccionado;
        sf::Font fuente;
        sf::Text menuObjetos [MAX_ITEM_NUM];

        void marcarSeleccionado();

};

#endif // MENU_INICIO_H
