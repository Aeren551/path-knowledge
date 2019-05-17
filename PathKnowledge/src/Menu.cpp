#include "Menu.h"

Menu::Menu()
{
    objetoSeleccionado = 0;
    numObjetos = 0;
    if(!fuente.loadFromFile("resources/Menus/2.TTF"))
    {
        cout<<"Error al cargar la fuente del texto. Menu"<<endl;
    }
    if(!t_fondo.loadFromFile("resources/Menus/fondo1.jpg"))
    {
        cout<<"Error al cargar la la textura del fondo. Menu"<<endl;
    }
    if(!t_marco.loadFromFile("resources/Menus/marco2.png"))
    {
        cout<<"Error al cargar la la textura del fondo. Menu"<<endl;
    }

    marco = sf::Sprite(t_marco);
    fondo = sf::Sprite(t_fondo);
    fondo.scale(1.15,1);

    //marco.setColor(sf::Color(120,80,50));
    marco.scale(0.3,0.1);
    marco.setOrigin(marco.getLocalBounds().width/2, marco.getLocalBounds().height/2-110);
    menuObjetos = NULL;
}

int Menu::menuInicio(sf::RenderWindow* w)
{
    // INICIALIZAR VALORES
    window = w;
    width = window->getSize().x;
    height = window->getSize().y;


    titulo = sf::Text();
    titulo.setString("     Path \n\n       of \n\n Knowledge");
    titulo.setFont(fuente);
    titulo.setCharacterSize(70);
    titulo.setColor(sf::Color::Yellow);
    titulo.setOrigin(0,0);
    titulo.setPosition(600,150);
    titulo_sombra = sf::Text();
    titulo_sombra.setString(titulo.getString());
    titulo_sombra.setFont(fuente);
    titulo_sombra.setCharacterSize(70);
    titulo_sombra.setColor(sf::Color(0,0,0));
    titulo_sombra.setOrigin(2,2);
    titulo_sombra.setPosition(titulo.getPosition());

    numObjetos = 4;
    menuObjetos = new sf::Text[numObjetos];

    menuObjetos[0].setString("Comenzar");
    menuObjetos[1].setString("Ayuda");
    menuObjetos[2].setString("Creditos");
    menuObjetos[3].setString("Salir");
    for (int i=0; i<numObjetos; i++)
    {
        menuObjetos[i].setFont(fuente);
        menuObjetos[i].setColor(sf::Color(230,230,230));
        menuObjetos[i].setCharacterSize(40);
        menuObjetos[i].setOrigin(menuObjetos[i].getLocalBounds().width/2, menuObjetos[i].getLocalBounds().height/2);
        menuObjetos[i].setPosition(width/2-200, height/(numObjetos+1)*(i+1));
    }
    sf::Text* menuObjetos2 = new sf::Text[numObjetos];
    for (int i=0; i<numObjetos; i++)
    {
        menuObjetos2[i].setString(menuObjetos[i].getString());
        menuObjetos2[i].setFont(fuente);
        menuObjetos2[i].setColor(sf::Color(30,30,30));
        menuObjetos2[i].setCharacterSize(40);
        menuObjetos2[i].setOrigin(menuObjetos[i].getLocalBounds().width/2-1, menuObjetos[i].getLocalBounds().height/2-1);
        menuObjetos2[i].setPosition(menuObjetos[i].getPosition());
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
                                    ayuda();
                                    break;
                                case 2:
                                    //CREDITOS
                                    creditos();
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
        window->clear();
        window->draw(fondo);
        window->draw(marco);
        for (int i=0; i<numObjetos; i++)
        {
            window->draw(menuObjetos2[i]);
        }
        for (int i=0; i<numObjetos; i++)
        {
            window->draw(menuObjetos[i]);
        }
        window->draw(titulo_sombra);
        window->draw(titulo);
        window->display();

    }
    // eliminar puntero
    delete[] menuObjetos;
    menuObjetos = NULL;
    delete[] menuObjetos2;
    menuObjetos2 = NULL;
    estado = NULL;
}

void Menu::creditos()
{
    sf::Text t = sf::Text();
    t.setString("Desarrolladores:    PentaEnix");
    t.setFont(fuente);
    t.setCharacterSize(60);
    t.setColor(sf::Color::Yellow);
    t.setOrigin(0,0);
    t.setPosition(170,100);
    sf::Text t_sombra = sf::Text();
    t_sombra.setString(t.getString());
    t_sombra.setFont(fuente);
    t_sombra.setCharacterSize(60);
    t_sombra.setColor(sf::Color::Black);
    t_sombra.setOrigin(-2,-2);
    t_sombra.setPosition(t.getPosition());

    int c_lenght = 7;
    sf::Text* contenido = new sf::Text[c_lenght];
    contenido[1].setString("Jose Antonio Sansano Melero");
    contenido[6].setString("Javier Alted Navarro");
    contenido[5].setString("Gaspar Angel Tortosa Pardo");
    contenido[4].setString("Monica Iglesias Gonzalez");
    contenido[3].setString("Jose Manuel Manresa Guirao");
    contenido[2].setString("Ruben Muriana Sala");
    for (int i=1; i<c_lenght; i++)
    {
        contenido[i].setFont(fuente);
        contenido[i].setCharacterSize(30);
        contenido[i].setColor(sf::Color(230,230,230));
        contenido[i].setOrigin(0,0);
        contenido[i].setPosition(210, 60*i+170);
    }
    sf::Text* contenido2 = new sf::Text[c_lenght];
    for (int i=1; i<c_lenght; i++)
    {
        contenido2[i].setString(contenido[i].getString());
        contenido2[i].setFont(fuente);
        contenido2[i].setCharacterSize(30);
        contenido2[i].setColor(sf::Color(30,30,30));
        contenido2[i].setOrigin(1,1);
        contenido2[i].setPosition(210, 60*i+170);
    }

    sf::Text volver = sf::Text();
    volver.setString("Volver");
    volver.setFont(fuente);
    volver.setCharacterSize(40);
    volver.setColor(sf::Color(180,0,0));
    volver.setOrigin(volver.getLocalBounds().width/2, volver.getLocalBounds().height/2);
    volver.setPosition(800,500);
    sf::Text volver2 = sf::Text();
    volver2.setString("Volver");
    volver2.setFont(fuente);
    volver2.setCharacterSize(40);
    volver2.setColor(sf::Color(0,0,0));
    volver2.setOrigin(volver.getLocalBounds().width/2-1, volver.getLocalBounds().height/2-1);
    volver2.setPosition(800,500);
    sf::Sprite m = sf::Sprite(t_marco);
    m.scale(0.3,0.1);
    m.setOrigin(marco.getLocalBounds().width/2, marco.getLocalBounds().height/2-110);
    m.setPosition(volver.getPosition());


    bool seguir = true;
    while (window->isOpen() && seguir)
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
                        case sf::Keyboard::Space:
                        case sf::Keyboard::Return:
                        case sf::Keyboard::Escape:
                            // CAMBIAR ESTADO
                            seguir = false;
                            break;
                    }
                    break;
            }
        }
        window->clear();
        window->draw(fondo);
        window->draw(t_sombra);
        window->draw(t);
        window->draw(volver2);
        window->draw(volver);
        window->draw(m);
        for(int i=1; i<c_lenght;i++)
            window->draw(contenido2[i]);
        for(int i=1; i<c_lenght;i++)
            window->draw(contenido[i]);
        window->display();
    }
    delete[] contenido;
    contenido = NULL;
    delete[] contenido2;
    contenido2 = NULL;
}
void Menu::ayuda()
{
    sf::Text t = sf::Text();
    t.setString("Ayuda");
    t.setFont(fuente);
    t.setCharacterSize(60);
    t.setColor(sf::Color::Yellow);
    t.setOrigin(t.getLocalBounds().width/2,0);
    t.setPosition(width/2,100);
    sf::Text t_sombra = sf::Text();
    t_sombra.setString(t.getString());
    t_sombra.setFont(fuente);
    t_sombra.setCharacterSize(60);
    t_sombra.setColor(sf::Color(0,0,0));
    t_sombra.setOrigin(t_sombra.getLocalBounds().width/2-2,0-2);
    t_sombra.setPosition(t.getPosition());

    int num_im = 3;
    sf::Texture* textures = new sf::Texture[num_im];

    if(!textures[0].loadFromFile("resources/Menus/wasd2.png"))
    {
        cout<<"Error al cargar la textura wasd2. Menu - Ayuda"<<endl;
    }
    if(!textures[1].loadFromFile("resources/Menus/intro.png"))
    {
        cout<<"Error al cargar la textura intro. Menu - Ayuda"<<endl;
    }
    if(!textures[2].loadFromFile("resources/Menus/estres-cono.png"))
    {
        cout<<"Error al cargar la textura cono. Menu - Ayuda"<<endl;
    }

    sf::Sprite* imagenes = new sf::Sprite[num_im];
    for(int i=0; i<num_im; i++)
        imagenes[i] = sf::Sprite(textures[i]);
    imagenes[0].setTextureRect(sf::IntRect(100,100,400,190));
    imagenes[0].setColor(sf::Color(200,200,200));
    imagenes[0].setScale(0.5,0.5);
    imagenes[1].setScale(0.16,0.16);
    imagenes[2].setScale(0.5,0.5);
    imagenes[0].setPosition(220,130);
    imagenes[1].setPosition(700,150);
    imagenes[2].setPosition(180,290);


    int c_lenght = 7;
    sf::Text* contenido = new sf::Text[c_lenght];
    contenido[0].setString("Te has embarcado en un trepidante viaje en busca de conocimiento.");
    contenido[1].setString("Con las teclas 'wasd' te desplazas por el mapa.   Con la tecla 'intro' interactuas con los objetos.");
    contenido[3].setString("Barra de conocimiento: tu objetivo es aumentarla al maximo.");
    contenido[2].setString("Barra de estres: cuando se llene perderas conocimiento y volveras al inicio.");
    contenido[4].setString("Cuando te topes con un enemigo entraras en combate con el. Derrotalo antes de que lo haga el.");
    contenido[5].setString("El combate se realiza por turnos, atacas tu y luego ataca el enemigo.");
    contenido[6].setString("Derrota a tus enemigos para conseguir tu titulo universitario.");
    for (int i=0; i<c_lenght; i++)
    {
        contenido[i].setFont(fuente);
        contenido[i].setCharacterSize(20);
        contenido[i].setColor(sf::Color(230,230,230));
        contenido[i].setOrigin(0,0);
        contenido[i].setPosition(180, 50*i+190);
    }
    contenido[2].setPosition(180+140, contenido[2].getPosition().y);
    contenido[3].setPosition(180+140, contenido[3].getPosition().y);
    sf::Text* contenido2 = new sf::Text[c_lenght];
    for (int i=0; i<c_lenght; i++)
    {
        contenido2[i].setString(contenido[i].getString());
        contenido2[i].setFont(fuente);
        contenido2[i].setCharacterSize(20);
        contenido2[i].setColor(sf::Color(30,30,30));
        contenido2[i].setOrigin(1,1);
        contenido2[i].setPosition(contenido[i].getPosition());
    }


    sf::Text volver = sf::Text();
    volver.setString("Volver");
    volver.setFont(fuente);
    volver.setCharacterSize(40);
    volver.setColor(sf::Color(180,0,0));
    volver.setOrigin(volver.getLocalBounds().width/2, volver.getLocalBounds().height/2);
    volver.setPosition(800,500);
    sf::Text volver2 = sf::Text();
    volver2.setString("Volver");
    volver2.setFont(fuente);
    volver2.setCharacterSize(40);
    volver2.setColor(sf::Color(0,0,0));
    volver2.setOrigin(volver.getLocalBounds().width/2-1, volver.getLocalBounds().height/2-1);
    volver2.setPosition(volver.getPosition());
    sf::Sprite m = sf::Sprite(t_marco);
    m.scale(0.3,0.1);
    m.setOrigin(marco.getLocalBounds().width/2, marco.getLocalBounds().height/2-110);
    m.setPosition(volver.getPosition());


    bool seguir = true;
    while (window->isOpen() && seguir)
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
                        case sf::Keyboard::Space:
                        case sf::Keyboard::Return:
                        case sf::Keyboard::Escape:
                            // CAMBIAR ESTADO
                            seguir = false;
                            break;
                    }
                    break;
            }
        }
        window->clear();
        window->draw(fondo);
        window->draw(t_sombra);
        window->draw(t);
        window->draw(volver2);
        window->draw(volver);
        window->draw(m);
        for(int i=0; i<num_im; i++)
            window->draw(imagenes[i]);
        for(int i=1; i<c_lenght;i++)
            window->draw(contenido2[i]);
        for(int i=1; i<c_lenght;i++)
            window->draw(contenido[i]);
        window->display();
    }
    delete[] contenido;
    contenido = NULL;
    delete[] contenido2;
    contenido2 = NULL;
    delete[] textures;
    textures = NULL;
    delete[] imagenes;
    imagenes = NULL;
}

int Menu::menuPause(sf::RenderWindow* w)
{
    // INICIALIZAR VALORES
    window = w;
    width = window->getSize().x;
    height = window->getSize().y;

    titulo = sf::Text();
    titulo.setString("Pause");
    titulo.setFont(fuente);
    titulo.setCharacterSize(60);
    titulo.setColor(sf::Color::Yellow);
    titulo.setOrigin(titulo.getLocalBounds().width/2,titulo.getLocalBounds().height/2);
    titulo.setPosition(width/2,150);
    titulo_sombra = sf::Text();
    titulo_sombra.setString(titulo.getString());
    titulo_sombra.setFont(fuente);
    titulo_sombra.setCharacterSize(60);
    titulo_sombra.setColor(sf::Color(0,0,0));
    titulo_sombra.setOrigin(titulo_sombra.getLocalBounds().width/2-2,titulo_sombra.getLocalBounds().height/2-2);
    titulo_sombra.setPosition(titulo.getPosition());

    numObjetos = 3;
    menuObjetos = new sf::Text[numObjetos];
    menuObjetos[0].setString("Continuar");
    menuObjetos[1].setString("Ayuda");
    menuObjetos[2].setString("Salir");
    for (int i=0; i<numObjetos; i++)
    {
        menuObjetos[i].setFont(fuente);
        menuObjetos[i].setColor(sf::Color(230,230,230));
        menuObjetos[i].setCharacterSize(40);
        menuObjetos[i].setOrigin(menuObjetos[i].getLocalBounds().width/2, menuObjetos[i].getLocalBounds().height/2);
        menuObjetos[i].setPosition(width/2, height/(numObjetos+2)*(i+2));
    }
    sf::Text* menuObjetos2 = new sf::Text[numObjetos];
    for (int i=0; i<numObjetos; i++)
    {
        menuObjetos2[i].setString(menuObjetos[i].getString());
        menuObjetos2[i].setFont(fuente);
        menuObjetos2[i].setColor(sf::Color(30,30,30));
        menuObjetos2[i].setCharacterSize(40);
        menuObjetos2[i].setOrigin(menuObjetos2[i].getLocalBounds().width/2-1, menuObjetos2[i].getLocalBounds().height/2-1);
        menuObjetos2[i].setPosition(menuObjetos[i].getPosition());
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
                                    ayuda();
                                    break;
                                case 2:
                                    //SALIR
                                    estado->setEstado(0);
                                    break;
                            }
                            break;
                    }
                    break;
            }
        }

        // DIBUJAR
        window->clear();
        window->draw(fondo);
        //window->draw(fondo_b1);
        //window->draw(fondo_b2);


        window->draw(marco);
        for (int i=0; i<numObjetos; i++)
        {
            window->draw(menuObjetos2[i]);
        }
        for (int i=0; i<numObjetos; i++)
        {
            window->draw(menuObjetos[i]);
        }
        window->draw(titulo_sombra);
        window->draw(titulo);
        window->display();
    }
    // eliminar puntero
    delete[] menuObjetos;
    menuObjetos = NULL;
    delete[] menuObjetos2;
    menuObjetos2 = NULL;
    estado = NULL;
}

Menu::~Menu()
{
    //delete menuObjetos;
    //menuObjetos = NULL;
}

void Menu::marcarSeleccionado()
{
    menuObjetos[objetoSeleccionado].setColor(sf::Color(180,0,0));
    marco.setPosition(menuObjetos[objetoSeleccionado].getPosition());
}
void Menu::moveUp()
{
    if(objetoSeleccionado > 0)
    {
        menuObjetos[objetoSeleccionado].setColor(sf::Color(230,230,230));
        --objetoSeleccionado;
        marcarSeleccionado();
    }
}

void Menu::moveDown()
{
    if(objetoSeleccionado < numObjetos-1)
    {
        menuObjetos[objetoSeleccionado].setColor(sf::Color(230,230,230));
        ++objetoSeleccionado;
        marcarSeleccionado();
    }
}
void Menu::dibujar()
{
    window->clear();
    for (int i=0; i<numObjetos; i++)
    {
        window->draw(menuObjetos[i]);
    }
    window->draw(titulo);
    window->display();
}
