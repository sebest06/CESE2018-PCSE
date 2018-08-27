/*
 * Nodo.cpp
 *
 *  Created on: 16/8/2018
 *      Author: electro1
 */

#include "Nodo.h"
#include "almacen.h"
#include "servidor.h"
#include <map>

const std::string Nodo::s_type = "NODO";

Nodo::Nodo() {
	// TODO Auto-generated constructor stub

}

Nodo::~Nodo() {
	// TODO Auto-generated destructor stub
}

void Nodo::procesarDatos(char* buffer, int len)
{
	char salida[50];

	if(TheServidor::Instance()->getXmppClient() != NULL)
	{
		snprintf(salida,50,"%s: %s",getName().c_str(),buffer);
		TheServidor::Instance()->getXmppClient()->sendChat(getJid(),salida);
	}
}
int Nodo::login(char* buffer, int len)
{
	char *ptrToken;
	ptrToken = strtok(buffer,", \r\n");
	if(ptrToken != NULL)
	{
		setName(ptrToken);
		ptrToken = strtok(NULL,", \r\n");
		if(ptrToken != NULL)
		{
			setJid(ptrToken);
		}
		else
		{
			setJid("lamulita@404.city");
		}
	}
	else
	{
		return -1;
	}

	std::cout << "Adding client with id: " << getId() << std::endl;
	std::cout << "Adding client with id: " << getName() << std::endl;
	std::cout << "Adding client with id: " << getJid() << std::endl;

	return 0;
}

void Nodo::setJid(std::string jid)
{
	m_jid = jid;
}

std::string Nodo::getJid(void)
{
	return m_jid;
}
