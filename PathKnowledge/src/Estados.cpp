#include "Estados.h"

Estados * Estados::pinstance = 0; //Inicializar el puntero

Estados * Estados::Instance()
{
    if(pinstance == 0) //¿Es la primera llamada?
    {
        pinstance = new Estados; //Creamos la instancia
    }
    return pinstance; //Devolvemos la direccion de la instancia
}


Estados::Estados()
{
    estado = 0;
    estadoCombate = 0;
}

Estados::~Estados()
{
    //dtor
}

int Estados::getEstado()
{
    return estado;
}

void Estados::setEstado(int e)
{
    estado = e;
}

int Estados::getEstadoCombate()
{
    return estadoCombate;
}

void Estados::setEstadoCombate(int ec)
{
    estadoCombate = ec;
}
