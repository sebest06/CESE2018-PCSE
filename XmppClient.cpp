/*
 * XmppClient.cpp
 *
 *  Created on: 1/8/2018
 *      Author: electro1
 */

#define NO_MOSTRAR "password"
#include "XmppClient.h"
#include "almacen.h"
#include "servidor.h"

#include <string>
#include <string.h>
#include <iostream>

#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>

XmppClient::XmppClient() {
	JID jid("testbot@404.city");
	client = new Client( jid, NO_MOSTRAR );
	connListener = new ConnListener();
	client->registerMessageHandler( this );
	client->registerConnectionListener(connListener);
}

XmppClient::~XmppClient() {
	delete client;
	delete connListener;
}

void XmppClient::handleMessage(const Message& stanza, MessageSession* session) {
	char salida[50];
	char *ptrToken;
	cout << "Mensaje: " << stanza.body() << endl;
	string msj = stanza.body();

	if(memcmp(msj.c_str(),"/nodo ",6) == 0)
	{
		strcpy(salida,msj.c_str());
		ptrToken = strtok(salida+6," ,\r\n");
		if(ptrToken != NULL)
		{
			int socket = ElAlmacen::Instance()->findSocketFromName(ptrToken);
			//std::cout << "SOCKET = " << socket << std::endl;
			ptrToken = strtok(NULL,"\r\n");
			TheServidor::Instance()->sendData(socket,ptrToken,strlen(ptrToken),0);
		}
	}
	//msj

}

void XmppClient::sendMessage(const Message& stanza) {
	client->send( stanza );
}

void XmppClient::sendChat(const string jid, const string body) {
	Message msg(Message::Chat, JID(jid), body);
	client->send( msg );
}

void XmppClient::connect() {
	client->connect(true);
}
