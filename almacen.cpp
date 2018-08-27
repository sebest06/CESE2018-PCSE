#include "almacen.h"
#include <string>
#include <iostream>
#include <string.h>

Almacen* Almacen::s_pInstance = 0;

std::vector<Cliente*> Almacen::clientes;

Almacen::Almacen()
{
    //ctor
}

Almacen::~Almacen()
{
    //dtor
}

int Almacen::findSocketFromName(std::string name)
{
	for(size_t i=0; i<clientes.size(); i++)
	{
		//std::cout << clientes[i]->getName().c_str() << " =? " << name.c_str() << std::endl;
		if(strcmp(clientes[i]->getName().c_str(),name.c_str()) == 0) return clientes[i]->getSocket();
	}

	std::cerr << "Client id not found." << std::endl;
	return -1;
}
