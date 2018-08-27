/*
 * XmppClient.h
 *
 *  Created on: 1/8/2018
 *      Author: electro1
 */

#ifndef XMPPCLIENT_H_
#define XMPPCLIENT_H_

#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>

#include <string>
#include <iostream>

using namespace std;
using namespace gloox;

class ConnListener : public ConnectionListener {
public:
    virtual void onConnect() {
        cout << "ConnListener::onConnect()" << endl;
    }
    virtual void onDisconnect(ConnectionError e) {
        cout << "ConnListener::onDisconnect() " << e << endl;
    }
    virtual bool onTLSConnect(const CertInfo& info) {
        cout << "ConnListener::onTLSConnect()" << endl;
        return true;
    }
};

class XmppClient : public MessageHandler {
public:
	XmppClient();
    ~XmppClient();

    virtual void handleMessage( const Message& stanza, MessageSession* session = 0 );
    void sendMessage(const Message& stanza);
    void sendChat(const string jid, const string body);
    void connect();

private:
   Client* client;
   ConnListener* connListener;
};

#endif /* XMPPCLIENT_H_ */
