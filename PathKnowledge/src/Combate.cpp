#include "Combate.h"

#define UPDATE_TICK_TIME 1000/15


Combate::Combate(Player* p, Enemy *e)
{
    cout<<"creo un combate"<<endl;
    sf::Clock relojInput;
    player = p;
    enemy = e;
    spriteJugador = p->getCombatSprite();
    spriteEnemigo = e->getCombatSprite();


    //====================IMAGEN DE FONDO==========================
    texturaFondo = new sf::Texture;
    if(!texturaFondo->loadFromFile("resources/fondo_bosque_2.jpg"))
    {
        cout<<"Error con la textura del bosque para fondo"<<endl;
    }
    spriteFondo = new sf::Sprite;
    spriteFondo->setTexture(*texturaFondo);
    spriteFondo->setScale(1.2, 1);
    //=============================================================

    //=======================OPCIONES EN COMBATE===================
    fuenteCombate = new sf::Font;
    if(!fuenteCombate->loadFromFile("resources/fonts/Pixeled.ttf"))
    {
        cout<<"Error al cargar la fuente"<<endl;
    }
    menuCombate = new sf::Text[3];
    menuCombate[0].setString("Ataque normal");
    menuCombate[1].setString("Habilidad");
    menuCombate[2].setString("Huir");
    for(int i = 0; i < 3; i++)
    {
        menuCombate[i].setFont(*fuenteCombate);
        if(i == 1)
            menuCombate[i].setPosition(i*425+80, 625);
        else
            menuCombate[i].setPosition(i*425+40, 625);
    }
    marcarSeleccionado();
    //=============================================================

    //==============BARRAS DE VIDA Y DEMAS=========================
    textura = new sf::Texture();
    if(!textura->loadFromFile("resources/character.png"))
    {
        cout<<"Error con la textura character.png (clase combate)"<<endl;
    }
    barraVidaEnemigo = new sf::Sprite();
    barraVidaEnemigo->setTexture(*textura);
    barraVidaEnemigo->setTextureRect(sf::IntRect(4*SPRITE_WIDTH, 2*SPRITE_HEIGHT+6, 56, 7)); //max 52
    barraVidaEnemigo->setPosition(710,185);
    barraVidaEnemigo->scale(5,5);

    vidaEnemigo = new sf::Sprite();
    vidaEnemigo->setTexture(*textura);
    vidaEnemigo->setTextureRect(sf::IntRect(4*SPRITE_WIDTH, 2*SPRITE_HEIGHT+3, enemy->getVida(), 3)); //max 52
    vidaEnemigo->setPosition(720,195);
    vidaEnemigo->scale(5,5);

    //=============================================================
}

Combate::~Combate()
{
    delete texturaFondo;
    texturaFondo = NULL;
}

void Combate::compruebaFin()
{
    Estados * estado = Estados::Instance();
    if(enemy->getVida() <= 0)
    {
        player->ganaConocimiento();
        estado->setEstado(1);
    }

}

void Combate::input(sf::RenderWindow* window)
{
    Estados * estado = Estados::Instance();
    if(relojInput.getElapsedTime().asSeconds() >= 0.15 && estado->getEstadoCombate() == 0)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            relojInput.restart();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            moveLeft();
            relojInput.restart();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            relojInput.restart();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            moveRight();
            relojInput.restart();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            ejecutarAccion();
            relojInput.restart();
        }
    }
}

void Combate::ejecutarAccion()
{
    Estados * estado = Estados::Instance();
    switch(objetoSeleccionado)
    {
        case 0:
            cout<<"Ataco"<<endl;
            //hago las cosas que tenga que hacer
            //y despues...
            //cambio estadoCombate para dar turno al enemigo
            //estado->setEstadoCombate(1);
            enemy->restaVida();
            vidaEnemigo->setTextureRect(sf::IntRect(4*SPRITE_WIDTH, 2*SPRITE_HEIGHT+3, enemy->getVida(), 3)); //max 52
        break;

        case 1:
            cout<<"Uso habilidad"<<endl;
            //hago las cosas que tenga que hacer
            //y despues...
            //cambio estadoCombate para dar turno al enemigo
            //estado->setEstadoCombate(1);
        break;

        case 2:
            cout<<"Huyo como un cobarde"<<endl;
            player->ganaConocimiento();
            estado->setEstado(1);
        break;
    }
}

void Combate::moveRight()
{
    if(objetoSeleccionado < 2)
    {
        menuCombate[objetoSeleccionado].setColor(sf::Color::White);
        objetoSeleccionado++;
    }
    marcarSeleccionado();
}

void Combate::moveLeft()
{
    if(objetoSeleccionado > 0)
    {
        menuCombate[objetoSeleccionado].setColor(sf::Color::White);
        objetoSeleccionado--;
    }
    marcarSeleccionado();
}

void Combate::marcarSeleccionado()
{
    menuCombate[objetoSeleccionado].setColor(sf::Color::Green);
}

void Combate::render(sf::RenderWindow* window)
{
    window->draw(*spriteFondo);
    window->draw(*spriteJugador);
    window->draw(*spriteEnemigo);
    window->draw(*barraVidaEnemigo);
    window->draw(*vidaEnemigo);
    for(int i = 0; i < 3; i++)
    {
        window->draw(menuCombate[i]);
    }
}
