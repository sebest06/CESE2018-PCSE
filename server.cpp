#include "server.h"
#include "servidor.h"
#include "almacen.h"
#include "Nodo.h"
#include "cliente.h"
#include <string>


using namespace std;

XmppClient* Server::xmpp = 0;

Server::Server(XmppClient *client)
{
  //Initialize static mutex from MyThread
    MyThread::InitMutex();
    Server::xmpp = client;
    TheServidor::Instance()->setXmppClient(xmpp);
}

/*
	AcceptAndDispatch();

	Main loop:
		Blocks at accept(), until a new connection arrives.
		When it happens, create a new thread to handle the new client.
*/
void Server::AcceptAndDispatch() {

    int c;
    MyThread *t;

    while(1) {

      t = new MyThread();
      c = TheServidor::Instance()->acceptSocket();

      if(c < 0) {
        cerr << "Error on accept";
      }
      else {
        t->Create((void *) Server::HandleClient, &c);
      }
    }
}

void *Server::HandleClient(void *args) {

    Cliente *c;
    int thisSocket = *(int *) args;

    char buffer[256-25];
    char salida[50];
    char *ptrToken;
    int index;
    int n;

    memset(buffer, 0, sizeof buffer);
    n = TheServidor::Instance()->recvData(thisSocket, buffer, sizeof buffer, 0);
    c = new Nodo();

    if(memcmp(buffer,"/name ",6) == 0)
    {
    	if(!c->login(buffer+6,n-6))
    	{
			c->setSocket(thisSocket);
			MyThread::LockMutex("Critical Area");
			ElAlmacen::Instance()->clientes.push_back(c);
			MyThread::UnlockMutex("Critical Area");
    	}
    	else
    	{
    		close(thisSocket);
        	delete c;
        	return NULL;
    	}
    }
    else
    {
    	close(thisSocket);
    	delete c;
    	return NULL;
    }

    while(1) {
    	memset(buffer, 0, sizeof buffer);
    	n = TheServidor::Instance()->recvData(thisSocket, buffer, sizeof buffer, 0);
    	//Client disconnected?
    	if(n == 0) {
    		cout << "Client diconnected" << endl;
    		close(thisSocket);
    		//Remove client in Static clients <vector> (Critical section!)
    		MyThread::LockMutex("Borrando de lista");
    		index = Server::FindSocketClient(thisSocket);
    		cout << "Erasing user whose name is: " << ElAlmacen::Instance()->clientes[index]->getName() << endl;
    		ElAlmacen::Instance()->clientes.erase(ElAlmacen::Instance()->clientes.begin() + index);
    		MyThread::UnlockMutex("Borrando de lista");
    		break;
    	}
    	else if(n < 0) {
    		//cerr << "Error while receiving message from client: " << c->getName() << endl;
    		TheServidor::Instance()->close(thisSocket);
    	}
    	else {
    		MyThread::LockMutex((const char *) "Test");
    		cout << buffer << endl;
    		c->procesarDatos(buffer,n);
    		MyThread::UnlockMutex((const char *) "Test");
    	}
    }

    return NULL;
}
/*
  Should be called when vector<Client> clients is locked!
*/
int Server::FindSocketClient(int socket)
{
    for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
    {
        if((ElAlmacen::Instance()->clientes[i]->getSocket()) == socket) return (int) i;
    }

    cerr << "Client id not found." << endl;
    return -1;
}
