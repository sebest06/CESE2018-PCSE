/*
 * Nodo.h
 *
 *  Created on: 16/8/2018
 *      Author: electro1
 */

#ifndef NODO_H_
#define NODO_H_

#include "cliente.h"
#include <string>

class Nodo : public Cliente {
public:
	Nodo();
	virtual ~Nodo();
	virtual int getSocket(){return m_socket;}
	virtual void setSocket(int socket){m_socket = socket;}
	virtual void setName(std::string name){m_name = name;}
	virtual std::string getName(void){return m_name;}
	virtual void procesarDatos(char* buffer, int len);
	virtual int login(char* buffer, int len);
	virtual void setId(int id){m_id = id;}
	virtual int getId(void){return m_id;}
	virtual std::string getStateID() const {return s_type;}
	virtual void setJid(std::string jid);
	virtual std::string getJid(void);
protected:
private:
	static const std::string s_type;
	std::string m_name;
	std::string m_jid;
	int m_id;
	bool m_registrada;
	int m_socket;
};

#endif /* NODO_H_ */
