#include <iostream>
#include "Player.h"

Player::Player(){

    //Parte de animacion y movimiento
    source= sf::Vector2i (0, 0);
    coordenadas = sf::Vector2i(0,0);

    posicion = sf::Vector2f(304, 288);
    posicionBarraEstres = sf::Vector2f(304-250, 288-165);
    posicionRellenoEstres = sf::Vector2f((304-250)+35, (288-165)+60);
    posicionRellenoConocimiento = sf::Vector2f((304-250)+35, (288-165)+26);

    lastPosicion = posicion;
    velocidad = sf::Vector2f(0,0);

    texture = new sf::Texture();
    //Carga la textura y si da error lanza un mensaje
    if(!texture->loadFromFile("resources/character.png"))
    {
        std::cerr << "Error cargando la imagen character.png";
        exit(0);
    }

    //=============SPRITE PARA MAPA=============
    sprite = new sf::Sprite();
    sprite->setTexture(*texture);
    sprite->setTextureRect(sf::IntRect(source.x*SPRITE_WIDTH,source.y*SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    sprite->setOrigin(SPRITE_WIDTH/2,SPRITE_HEIGHT);
    sprite->setPosition(posicion);

    //=============SPRITE PARA COMBATE=============
    combatSprite = new sf::Sprite();
    combatSprite->setTexture(*texture);
    combatSprite->setTextureRect(sf::IntRect(0*SPRITE_WIDTH,1*SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT));
    combatSprite->setOrigin(SPRITE_WIDTH/2,SPRITE_HEIGHT);
    combatSprite->setPosition(275,600);
    combatSprite->setScale(8, 8);

    //SPRITE PARA BARRA ESTRES Y CONOCIMIENTO
    spriteBarras = new sf::Sprite();
    spriteBarras->setTexture(*texture);
    spriteBarras->setTextureRect(sf::IntRect(4*SPRITE_WIDTH,0*SPRITE_HEIGHT,78,53));
    spriteBarras->setPosition(posicionBarraEstres);
    spriteBarras->scale(1.5,1.5);

    rellenoConocimientoSprite = new sf::Sprite();
    rellenoConocimientoSprite->setTexture(*texture);
    rellenoConocimientoSprite->setTextureRect(sf::IntRect(4*SPRITE_WIDTH, 2*SPRITE_HEIGHT, 0, 3)); //max 52
    rellenoConocimientoSprite->setPosition(posicionRellenoEstres);
    rellenoConocimientoSprite->scale(1.5,1.5);

    rellenoEstresSprite = new sf::Sprite();
    rellenoEstresSprite->setTexture(*texture);
    rellenoEstresSprite->setTextureRect(sf::IntRect(4*SPRITE_WIDTH, 2*SPRITE_HEIGHT+3, conocimiento, 3)); //max 52
    rellenoEstresSprite->setPosition(posicionRellenoConocimiento);
    rellenoEstresSprite->scale(1.5,1.5);

}

Player::~Player()
{
    delete sprite;
    sprite = NULL;
    delete texture;
    texture = NULL;
}

void Player::eventos()
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
    sf::Vector2f posicionInterpolada;

    posicionInterpolada = (posicion-lastPosicion)*tick + lastPosicion;

    sprite->setPosition(posicionInterpolada);
    spriteBarras->setPosition(posicionInterpolada.x-250, posicionInterpolada.y-165);
    rellenoEstresSprite->setPosition(posicionInterpolada.x-215, posicionInterpolada.y-105);
    rellenoConocimientoSprite->setPosition(posicionInterpolada.x-215, posicionInterpolada.y-139);

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

sf::Sprite* Player::getSprite()
{
    return sprite;
}

sf::Sprite* Player::getCombatSprite()
{
    return combatSprite;
}

void Player::ganaConocimiento()
{
    conocimiento += 5;
    rellenoConocimientoSprite->setTextureRect(sf::IntRect(4*SPRITE_WIDTH, 2*SPRITE_HEIGHT+3, conocimiento, 3)); //max 52
}

void Player::render(sf::RenderWindow* window)
{
    window->draw(*sprite);
    window->draw(*spriteBarras);
}

void Player::HUD(sf::RenderWindow* window)
{
    window->draw(*spriteBarras);
    window->draw(*rellenoEstresSprite);
    window->draw(*rellenoConocimientoSprite);
}




