#include "Menu.h"

Menu::Menu()
{
    objetoSeleccionado = 0;
    numObjetos = 0;
    fuente.loadFromFile("resources/fonts/Triforce.ttf");
    menuObjetos = NULL;
}

int Menu::menuInicio(sf::RenderWindow* window)
{
    // INICIALIZAR VALORES
    numObjetos = 4;
    menuObjetos = new sf::Text[numObjetos];
    int width = window->getSize().x;
    int height = window->getSize().y;

    menuObjetos[0].setString("JUGAR");
    menuObjetos[1].setString("Ayuda");
    menuObjetos[2].setString("Creditos");
    menuObjetos[3].setString("SALIR");
    for (int i=0; i<numObjetos; i++)
    {
        menuObjetos[i].setFont(fuente);
        menuObjetos[i].setColor(sf::Color::Red);
        menuObjetos[i].setPosition(sf::Vector2f((width/2)-(menuObjetos[i].getLocalBounds().width/2), height/(numObjetos+1)*(i+1)));
    }
    objetoSeleccionado = 0;
    marcarSeleccionado();


    //maquina de estados (0 menu principal)
    Estados * estado = Estados::Instance();
    while (window->isOpen() && estado->getEstado() == 0)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                // GESTION DE EVENTOS
                    switch(event.key.code)
                    {
                        case sf::Keyboard::W:
                        case sf::Keyboard::Up:
                            moveUp();
                            break;
                        case sf::Keyboard::S:
                        case sf::Keyboard::Down:
                            moveDown();
                            break;
                        case sf::Keyboard::Space:
                        case sf::Keyboard::Return:
                            // CAMBIAR ESTADO
                            switch(objetoSeleccionado)
                            {
                                case 0:
                                    estado->setEstado(1);
                                    break;
                                case 1:
                                    //AYUDA
                                    break;
                                case 2:
                                    //CREDITOS
                                    break;
                                case 3:
                                    //SALIR
                                    window->close();
                                    break;
                            }
                            break;
                    }
                    break;
            }
        }

        // DIBUJAR
        dibujar(window);
    }
    // eliminar puntero
    delete[] menuObjetos;
    menuObjetos = NULL;
}

int Menu::menuPause(sf::RenderWindow* window)
{
    // INICIALIZAR VALORES
    numObjetos = 2;
    menuObjetos = new sf::Text[numObjetos];
    int width = window->getSize().x;
    int height = window->getSize().y;

    menuObjetos[0].setString("CONTINUAR");
    menuObjetos[1].setString("SALIR");
    for (int i=0; i<numObjetos; i++)
    {
        menuObjetos[i].setFont(fuente);
        menuObjetos[i].setColor(sf::Color::Red);
        menuObjetos[i].setPosition(sf::Vector2f((width/2)-(menuObjetos[i].getLocalBounds().width/2), height/(numObjetos+1)*(i+1)));
    }
    objetoSeleccionado = 0;
    marcarSeleccionado();

    //maquina de estados (3 menu pause)
    Estados * estado = Estados::Instance();
    while (window->isOpen() && estado->getEstado() == 3)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                // GESTION DE EVENTOS
                    switch(event.key.code)
                    {
                        case sf::Keyboard::W: // para que funcione con ambos casos, flechas o WASD
                        case sf::Keyboard::Up:
                            moveUp();
                            break;
                        case sf::Keyboard::S:
                        case sf::Keyboard::Down:
                            moveDown();
                            break;
                        case sf::Keyboard::Space:
                        case sf::Keyboard::Return:
                            // CAMBIAR ESTADO
                            switch(objetoSeleccionado)
                            {
                                case 0:
                                    estado->setEstado(1);
                                    break;
                                case 1:
                                    //SALIR
                                    //window->close();
                                    estado->setEstado(0);
                                    break;
                            }
                            break;
                    }
                    break;
            }
        }

        // DIBUJAR
        dibujar(window);
    }
    // eliminar puntero
    delete[] menuObjetos;
    menuObjetos = NULL;
}

Menu::~Menu()
{
    //delete menuObjetos;
    //menuObjetos = NULL;
}

void Menu::marcarSeleccionado()
{
    menuObjetos[objetoSeleccionado].setColor(sf::Color::Green);
}
void Menu::moveUp()
{
    if(objetoSeleccionado > 0)
    {
        menuObjetos[objetoSeleccionado].setColor(sf::Color::Red);
        --objetoSeleccionado;
        menuObjetos[objetoSeleccionado].setColor(sf::Color::Green);
    }
}

void Menu::moveDown()
{
    if(objetoSeleccionado < numObjetos-1)
    {
        menuObjetos[objetoSeleccionado].setColor(sf::Color::Red);
        ++objetoSeleccionado;
        menuObjetos[objetoSeleccionado].setColor(sf::Color::Green);
    }
}
void Menu::dibujar(sf::RenderWindow* window)
{
    window->clear();
    for (int i=0; i<numObjetos; i++)
    {
        window->draw(menuObjetos[i]);
    }
    window->display();
}
