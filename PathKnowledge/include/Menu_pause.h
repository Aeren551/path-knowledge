#ifndef MENU_PAUSE_H
#define MENU_PAUSE_H


#include <SFML/Graphics.hpp>
#include <string>

#define MAX_ITEM_NUM 2


class menu_pause
{
    public:
        menu_pause(float width, float height);
        virtual ~menu_pause();

        void dibujar(sf::RenderWindow &window); // no se si ponerlo aqui o en el main (supongo que mejor aqui...)

        int getSeleccionado();
        std::string getSeleccionado_texto();

        int gestorEventos(int tecla);
    protected:
    private:
        bool operativo;
        int objetoSeleccionado;
        sf::Font fuente;
        sf::Text menuObjetos [MAX_ITEM_NUM];

        void marcarSeleccionado();
        void moveUp ();
        void moveDown ();
        void setOperativo();
        void reiniciar();
};

#endif // MENU_PAUSE_H
