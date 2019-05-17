#ifndef MUSICA_H
#define MUSICA_H

#include <SFML/Audio.hpp>
#include <iostream>


class Musica
{
    public:
        Musica();
        virtual ~Musica();

        void setActivo(int i);

    protected:
    private:
        sf::Music* musica;
        int n;
        int activo;
};

#endif // MUSICA_H
