#ifndef MAPA_H
#define MAPA_H

#include "tinyxml2.h"
#include <SFML/Graphics.hpp>

using namespace tinyxml2;

class Mapa //SINGLETON
{
    public:
        static Mapa * Instance();
        void leerTMX();
        void render(sf::RenderWindow *w);
        void setActiveLayer(int layer);
        virtual ~Mapa();

        //para el personaje
         int getTileWidth();
        int getTileHeight();
        int getTilemap(int l, int x, int y);
        bool colision (int x, int y);

    protected:
        Mapa();
        Mapa(const Mapa & );
        Mapa &operator= (const Mapa & );

    private:

        static Mapa * pinstance;
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
