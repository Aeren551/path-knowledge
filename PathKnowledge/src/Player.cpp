#include <iostream>
#include "Player.h"

Player::Player(sf::Vector2f size, float x,float y){
    player.setSize(size);
    player.setFillColor(sf::Color::White);

    //Parte de animacion y movimiento
    int cont=0;
    source= sf::Vector2i (0, 0);
    coordenadas = sf::Vector2i(0,0);

    posicion = sf::Vector2f(x,y);
    lastPosicion = sf::Vector2f(x,y);
    velocidad = sf::Vector2f(0,0);

    texture = new sf::Texture();
    sprite = new sf::Sprite();

    //Carga la textura y si da error lanza un mensaje
    if(!texture->loadFromFile("resources/character.png"))
    {
        std::cerr << "Error cargando la imagen character.png";
        exit(0);
    }
    //Crea el sprite y le asigna la textura
    sprite->setTexture(*texture);

    //Cojo el sprite inicial del spritesheet
    sprite->setTextureRect(sf::IntRect(source.x*SPRITE_WIDTH,source.y*SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    //Elegir el origen de coordenadas del sprite
    sprite->setOrigin(SPRITE_WIDTH/2,SPRITE_HEIGHT);
    //Coloco el sprite en su posicion inicial
    sprite->setPosition(posicion);
    ////////////////////////////////////////////////////////////////////////////////////fin

    //Conocimiento
    valc =0;
    valcm=100;
    borderc.setSize(sf::Vector2f(5,5));
    conocimiento.setSize(sf::Vector2f(5,5));
    borderc.setOutlineThickness(0.3);
    borderc.setScale(20,2);
    conocimiento.setScale(0,2);
    conocimiento.setFillColor(sf::Color::Blue);
    borderc.setOutlineColor(sf::Color::White);
    borderc.setFillColor(sf::Color::Transparent);

    //Estres
    vale =0;
    valem = 200;
    bordere.setSize(sf::Vector2f(5,5));
    estres.setSize(sf::Vector2f(5,5));
    bordere.setOutlineThickness(0.3);
    bordere.setScale(20,2);
    estres.setScale(0,2);
    estres.setFillColor(sf::Color::Red);
    bordere.setOutlineColor(sf::Color::White);
    bordere.setFillColor(sf::Color::Transparent);
}

Player::~Player()
{
    delete sprite;
    sprite = NULL;
    delete texture;
    texture = NULL;
}
//render del personaje en mapa
void Player::render (sf::RenderWindow* window)
{
    window->draw(*sprite);
}
void Player::eventos(int tecla)
{
    // ARRIBA
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        source.y=2;

        if(source.x>=2){
            source.x=0;
        }else{
            source.x ++;
        }

        velocidad.y -= MAX_VELOCIDAD;
        //std::cout<<"ARRIBA"<<std::endl;
    }

    // ABAJO
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        source.y=0;

        if(source.x>=2){
            source.x=0;
        }else{
            source.x ++;
        }

        velocidad.y += MAX_VELOCIDAD;
        //std::cout<<"ABAJO"<<std::endl;
    }

    //IZQUIERDA
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        source.y=3;

        if(source.x>=2){
            source.x=0;
        }else{
            source.x ++;
        }

        velocidad.x -= MAX_VELOCIDAD;
        //std::cout<<"IZQUIERDA"<<std::endl;
    }

    //DERECHA
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        source.y=1;

        if(source.x>=2){
            source.x=0;
        }else{
            source.x ++;
        }

        velocidad.x += MAX_VELOCIDAD;
        //std::cout<<"DERECHA"<<std::endl;
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
       !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        source.x=0;
    }
    // asignar rectangulo de textura correspondiente
    sprite->setTextureRect(sf::IntRect(source.x*SPRITE_WIDTH,source.y*SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
}
void Player::actualizarPos (float time)
{
    lastPosicion = posicion;

    // suma de vectores
    posicion += velocidad*time;

    velocidad.x = 0;
    velocidad.y = 0;

    //std::cout << "anterior: " << lastPosicion.x << ", " << lastPosicion.y << std::endl;
    //std::cout << "actual: " << posicion.x << ", " << posicion.y << std::endl;
}
void Player::interpolar (float tick)
{
    sf::Vector2f posicionInterpolada = sf::Vector2f();

    posicionInterpolada = (posicion-lastPosicion)*tick + lastPosicion;

    sprite->setPosition(posicionInterpolada);

    //std::cout << "sprite: " << posicionInterpolada.x << ", " << posicionInterpolada.y << std::endl;
}
void Player::setCoordenadas(int width, int height)
{
    int x = posicion.x/width;
    int y = posicion.y/height;

    if(x!=coordenadas.x || y!=coordenadas.y)
    {
        std::cout << "Coordenadas: (" << x << ", " << y << ")" << std::endl;
        coordenadas.x = x;
        coordenadas.y = y;
    }
}
sf::Vector2i* Player::getCoordenadas()
{
    return &coordenadas;
}

sf::Vector2f* Player::getPosition()
{
    return &posicion;
}
void Player::colisionMapa ()
{
    // si el personaje colisiona no puede moverse en esa posicion
    posicion = lastPosicion;
}

//render del personaje en combate
void Player::draw(sf::RenderWindow* window){
    window->draw(player);
    window->draw(conocimiento);
    window->draw(estres);
    window->draw(bordere);
    window->draw(borderc);
}
//posicion para el combate
void Player::setPosition(int x, int y){
    player.setPosition(x,y);
}
//posicion del estres en combate
void Player::setPositionE(int x, int y){
    estres.setPosition(x,y);
    bordere.setPosition(x,y);
}

//posicion conocimiento en combate
void Player::setPositionC(int x, int y){
    conocimiento.setPosition(x,y);
    borderc.setPosition(x,y);
}

void Player::updatE(float x){
    if(x+vale>=valem)
        estres.setScale(20,2);
    else if(x+vale<=0){
            estres.setScale(0,2);
    }else{
        estres.setScale(((x+vale)/valem)*20.f,2);
        vale=x+vale;
        std::cout<<vale<<std::endl;
        }
}

void Player::updatC(float x){
    if(x+valc>=valcm)
        conocimiento.setScale(20,2);
    else if(x+valc<=0){
            conocimiento.setScale(0,2);
    }else{
        conocimiento.setScale(((x+valc)/valcm)*20.f,2);
        valc=x+valc;
        std::cout<<valc<<std::endl;
        }
}


