#include "Mapa.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;

//----------------SINGLETON-----------------------

Mapa * Mapa::pinstance = 0; //Inicializar el puntero

Mapa * Mapa::Instance()
{
    if(pinstance == 0) //¿Es la primera llamada?
    {
        pinstance = new Mapa; //Creamos la instancia
    }
    return pinstance; //Devolvemos la direccion de la instancia
}

Mapa::Mapa()
{
    //ctor
    _width      = 0;    //ancho en numero de tiles
    _height     = 0;    //alto en numero de tiles
    _tileWidth  = 0;    //ancho del tile (en pixeles)
    _tileHeight = 0;    //alto del tile (en pixeles)
    _numLayers  = 0;    //numero de capas del mapa
    _tileCount  = 0;    //numero de tiles totales en la textura
    _tsw        = 0;    //ancho del tile (en pixeles)
    _tsh        = 0;    //alto del tile (en pixeles)
    _imgWidth   = 0;    //anchura en pixeles de la textura
    _imgHeight  = 0;    //altura en pixeles de la textura
    filename    = NULL;
    //doc = NULL; Si pongo esto peta.
}

Mapa::~Mapa()
{
    //dtor

    //==========MATRIZ DE ENTEROS============
    for(int l = 0; l < _numLayers; l++){
        for(int y = 0; y < _height; y++){
            delete [] _tilemap[l][y];
            _tilemap[l][y] = NULL;
        }
        delete [] _tilemap[l];
        _tilemap[l] = NULL;
    }
    delete [] _tilemap;
    _tilemap = NULL;
    //========================================


    //===========ARRAY DE SPRITES=============
    for(int i = 0; i < ((_imgHeight/_tileHeight)*(_imgWidth/_tileWidth));i++){
        delete [] _tilesetSprite[i];
        _tilesetSprite[i] = NULL;
    }
    delete [] _tilesetSprite;
    _tilesetSprite = NULL;
    //========================================


}

void Mapa::leerTMX()
{
    if(doc.LoadFile("resources/prueba1.tmx") != 0)
        cout<<"No existe fichero .tmx"<<endl;

    //Tamaño del mapa y de los tiles
    mapa = doc.FirstChildElement("map");

    //Leemos anchura y altura del mapa
    mapa->QueryIntAttribute("width", &_width);              //30
    mapa->QueryIntAttribute("height", &_height);            //30
    cout<<"==========DIMENSIONES DEL MAPA=========="<<endl;
    cout<<"Anchura en tiles: "<<_width<<endl;
    cout<<"Altura en tiles: "<<_height<<endl;
    //Leemos anchura y altura de los tiles
    mapa->QueryIntAttribute("tilewidth", &_tileWidth);      //16
    mapa->QueryIntAttribute("tileheight", &_tileHeight);    //16
    cout<<"Ancho del tile: "<<_tileWidth<<endl;
    cout<<"Alto del tile: "<<_tileHeight<<endl;
    cout<<"========================================"<<endl<<endl;

    //Obtenemos los tiles (ESTO CREO QUE LO PUEDO BORRAR)
    tileset = mapa->FirstChildElement("tileset");
    tileset->QueryIntAttribute("tilewidth", &_tsw); //_tsw = tileWidth
    tileset->QueryIntAttribute("tileheight", &_tsh); //_tsh = tileHeight

    //Guardar la ruta de laimagen del tileset en la variable filename
    //y cargarlar en _tilesetTexture
    img = mapa->FirstChildElement("tileset")->FirstChildElement("image");
    filename = img->Attribute("source"); //de momento no lo uso
    cargarTextura();

    //Obtengo las dimensiones de la textura
    img->QueryIntAttribute("width", &_imgWidth);
    img->QueryIntAttribute("height", &_imgHeight);
    cout<<"========DIMENSIONES DE LA TEXTURA======="<<endl;
    cout<<"Anchura en pixeles: "<<_imgWidth<<endl;
    cout<<"Altura en pixeles: "<<_imgHeight<<endl;
    cout<<"========================================"<<endl<<endl;

    //Obtener el numero de capas
    layer = mapa->FirstChildElement("layer");
    while(layer)
    {
        _numLayers++;
        //cout<<layer<<endl;
        layer = layer->NextSiblingElement("layer");
    }
    cout<<"Numero de capas del mapa: "<<_numLayers<<endl;

    //Creamos el array de tiles
    creaTileArray();

    //cargamos los GUID's
    cargarGID();

    //Reservamos memoria para la matriz del mapa
    crearMatriz();

    //Rellenamos la matriz3D con los sprites que toque
    rellenaMatriz();

}

void Mapa::creaTileArray()
{
    /*Divido la altura y anchura de la textura entre el alto y ancho de cada tile para obtener el numero total
    de tiles que tiene*/
    int filas = _imgHeight/_tileHeight;
    //cout<<filas<<endl;
    int columnas = _imgWidth/_tileWidth;
    //cout<<columnas<<endl;
    int pos = 0;

    /*Multiplico el numero de filas y de columnas para obtener las dimensiones que debe tener el array para
    poder almacenar todos los tiles*/
    _tilesetSprite = new sf::Sprite*[filas*columnas];

    /*Doble bucle for para asignar en cada posicion del array el sprite que le corresponderia de la textura*/
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++)
        {
            _tilesetSprite[pos] = new sf::Sprite;
            _tilesetSprite[pos]->setTexture(_tilesetTexture);
            _tilesetSprite[pos]->setTextureRect(sf::IntRect(j * _tileHeight, i * _tileWidth, _tileHeight, _tileWidth));
            pos++;
        }
    }
    cout<<"Bucle terminado -> Creado array de Sprites de "<<pos<<" posiciones"<<endl;
    cout<<"Filas"<<filas<<endl;
    cout<<"Columnas"<<filas<<endl;
    cout<<"tilemap["<<_numLayers<<"]["<<_height<<"]["<<_width<<"]"<<endl;

}

void Mapa::cargarGID()
{
    //creo una matriz de enteros en la que guardare los ID de cada tile para luego rellenar la matriz de sprites
    _tilemap = new int **[_numLayers];
    for(int l = 0; l < _numLayers; l++){
        _tilemap[l] = new int * [_height];
    }
    for(int l = 0; l < _numLayers; l++){
        for(int y = 0; y < _height; y++)
        {
            _tilemap[l][y] = new int[_width];
        }
    }

    XMLElement * data[_numLayers];
    data[0] = mapa->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    layer = mapa->FirstChildElement("layer");
    //cout<<layer<<endl;

    //Recorro todos los GID's y los voy guardando en la matriz creada
    for(int l = 0; l < _numLayers; l++){
        for(int y = 0; y < _height; y++){
            for(int x = 0; x < _width; x++)
            {
                data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                data[l] = data[l]->NextSiblingElement("tile");

            }
        }
        //CAMBIAR CAPA
        if(data[l] == 0 && l < _numLayers-1)
        {
            data[l+1] = layer->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
            layer = layer->NextSiblingElement("layer");
            //cout<<layer<<endl;
        }
    }
    cout<<"Matriz de GID's creada y rellenada"<<endl<<endl;
    /*for(int l = 0; l < _numLayers; l++)
    {
        for(int y = 0; y < _height; y++)
        {
            for(int x = 0; x < _width; x++)
            {
                cout<<_tilemap[l][y][x]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }*/
}

void Mapa::cargarTextura()
{
    if(!_tilesetTexture.loadFromFile("resources/Overworld.png"))
    {
        cout<<"Error textura"<<endl;
        exit(0);
    }
    cout<<"Textura cargada"<<endl<<endl;
}

void Mapa::crearMatriz()
{
    _tilemapSprite = new sf::Sprite *** [_numLayers];
    for(int l = 0; l < _numLayers; l++)
    {
        _tilemapSprite[l] = new sf::Sprite**[_height];
    }
    for(int l = 0; l < _numLayers; l++){
        for(int y = 0; y < _height; y++)
        {
            _tilemapSprite[l][y] = new sf::Sprite*[_width];
            for(int x = 0; x < _width; x++)
            {
                _tilemapSprite[l][y][x] = new sf::Sprite;
            }
        }
    }
    cout<<"Matriz 3D de Sprites creada con exito"<<endl;
}

void Mapa::rellenaMatriz()
{
    int gid;
    for(int l = 0; l < _numLayers; l++){
        for(int y = 0; y < _height; y++){
            for(int x = 0; x < _width; x++)
            {
                gid = _tilemap[l][y][x]-1;

                if(gid > -1)
                {
                    _tilemapSprite[l][y][x] = new sf::Sprite(_tilesetTexture,_tilesetSprite[gid]->getTextureRect());
                    _tilemapSprite[l][y][x]->setPosition(x*_tileWidth, y*_tileHeight);
                }
                else
                {
                    _tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }
    cout<<"Matriz de Sprites rellenada con exito"<<endl;
}

void Mapa::setActiveLayer(int layer)
{
    _activeLayer = layer;
}

void Mapa::render(sf::RenderWindow *w)
{

    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++)
        {
            if(_tilemapSprite[_activeLayer][y][x] != NULL)
                w->draw(*(_tilemapSprite[_activeLayer][y][x]));
        }
    }
}
