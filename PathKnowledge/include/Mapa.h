#ifndef MAPA_H
#define MAPA_H

#include "tinyxml2.h"
#include <SFML/Graphics.hpp>

using namespace tinyxml2;

class Mapa //SINGLETON
{
    public:
        Mapa();
        virtual ~Mapa();
        void leerTMX();
        void render(sf::RenderWindow *w);
        void setActiveLayer(int layer);


        //para el personaje
        int getTileWidth();
        int getTileHeight();
        int getTilemap(int l, int x, int y);
        bool colision (int x, int y);

    protected:

    private:
        void creaTileArray();
        void cargarGID();
        void cargarTextura();
        void crearMatriz();
        void rellenaMatriz();

        int _width, _height, _tileWidth, _tileHeight, _numLayers,
            _tileCount, _tsw, _tsh, _imgWidth, _imgHeight, _activeLayer;
        const char *filename;
        XMLDocument doc;
        XMLElement * mapa, * img, * layer, * tileset;
        sf::Sprite ****_tilemapSprite;
        int *** _tilemap;
        sf::Sprite ** _tilesetSprite;
        sf::Texture _tilesetTexture;

};

#endif // MAPA_H
