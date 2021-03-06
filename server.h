#ifndef _server_h_
#define _server_h_

#include "XmppClient.h"
#include <iostream>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

#include "mythread.h"
#include "cliente.h"

#define PORT 30666

using namespace std;

class Server {

  public:
    Server(XmppClient *client);
    void AcceptAndDispatch();
    static void * HandleClient(void *args);

  private:
    static int FindSocketClient(int socket);
    static XmppClient *xmpp;

};

#endif
