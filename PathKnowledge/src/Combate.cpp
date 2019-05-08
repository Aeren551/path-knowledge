#include "Combate.h"

#define UPDATE_TICK_TIME 1000/15


Combate::Combate(Player p, Enemy e):player(p),enemy(e),buttons(sf::Vector2f(90,125))
{

    //=======================ORDENAR ESTO CON EL .H=====================
    int turno=0;
    //Creamos una ventana
    sf::Font font;
    sf::Text text;
    sf::Text hp;
    sf::Text exp;
    font.loadFromFile("Pixeled.ttf");
    text.setFont(font);
    hp.setFont(font);
    exp.setFont(font);
    text.setColor(sf::Color::White);
    hp.setColor(sf::Color::Red);
    exp.setColor(sf::Color::Blue);
    text.setCharacterSize(25);
    text.setPosition(200,100);
    //player(sf::Vector2f(75,75));//Cambiar por Sprite
    //Enemy enemy(sf::Vector2f(100,100));//Cambiar por Sprite
    player.setPosition(100,200);
    enemy.setPosition(480,187);
    player.setPositionE(50,100);
    hp.setPosition(5,100);
    hp.setCharacterSize(10);
    player.setPositionC(50,150);
    exp.setPosition(5,150);
    exp.setCharacterSize(10);
    hp.setString("Est.");
    exp.setString("Con.");

}

Combate::~Combate(){

}

void Combate::start(sf::RenderWindow* window)
{
       sf::Event event;
    //maquina de estados (0 menu principal)
    Estados * estado = Estados::Instance();
    sf::Clock clock;
    while(estado->getEstado()==2)
    {
        if(clock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME*1.5)
        {
            while (window->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                    estado->setEstado(1);
            if (event.type == sf::Event::KeyPressed && event.key.code== sf::Keyboard::Escape)
                estado->setEstado(1);

        }
            if(turno==0)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    buttons.cursor(-1);

                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    buttons.cursor(1);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    int act = buttons.getOption();
                    switch(act)
                    {
                        case 1:
                            text.setString("Has atacado");
                            player.updatC(5.f);
                            turno=3;
                            buttons.changeTurn();
                        break;

                        case 2:
                            text.setString("Has usado Skill");
                            turno=2;
                            buttons.changeTurn();
                        break;

                        case 3:
                            text.setString("Has usado Items");
                            player.updatE(-20.f);
                            turno=3;
                            buttons.changeTurn();
                        break;

                        case 4:
                            text.setString("Has usado Flee");
                            Estados * estado = Estados::Instance();
                            estado->setEstado(1);
                        break;
                    }
                }
            }
            else if(turno==2)
                {
                    text.setString("Menu Skills");
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        turno=3;
                    }
                }
            else if(turno==3)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        text.setString("Te Estresas");
                        player.updatE(10.f);
                        turno=4;
                    }
                }
            else if(turno==4)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        text.setString("");
                        buttons.changeTurn();
                        turno=0;
                    }
                }//end turno
                render(window);
            clock.restart();
            }
            }
}

void Combate::render(sf::RenderWindow* window){
    window->clear();
    exp.setString("Con.");
    hp.setString("Est.");
    if(turno==0)
        text.setString("");
    player.draw(window);
    enemy.draw(window);
    window->draw(text);
    window->draw(hp);
    window->draw(exp);
    if(buttons.getTurn())
        buttons.draw(window);
    window->display();
}
