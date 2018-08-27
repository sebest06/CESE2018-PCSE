#include "XmppClient.h"
#include "server.h"
#include "mythread.h"
#include <unistd.h>

void *TcpServerThread(void *args)
{
	XmppClient *client = (XmppClient *) args;
	Server *s;
	s = new Server(client);
	//Main loop
	s->AcceptAndDispatch();
	return NULL;
}

int main()
{
	XmppClient *client = NULL;
	client = new XmppClient();

	MyThread *t = new MyThread();
	t->Create((void *) TcpServerThread, client);

	client->connect();

	return 1;
}
