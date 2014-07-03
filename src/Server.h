/*
 * Server.h
 *
 *  Created on: 03/07/2014
 *      Author: wachs
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <assert.h>
#include "ServerThread.h"

class Server: public QTcpServer {
Q_OBJECT
public:
	Server(quint16, QObject* parent = NULL);
	virtual ~Server();


private:
	unsigned int clientsConnected;
	void incomingConnection(qintptr handle);

	private slots:
	void incrementClients();
	void decrementClients();
};

#endif /* SERVER_H_ */
