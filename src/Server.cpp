/*
 * Server.cpp
 *
 *  Created on: 03/07/2014
 *      Author: wachs
 */

#include "Server.h"

Server::Server(quint16 port, QObject *parent) :
		QTcpServer(parent), clientsConnected(0) {

	listen(QHostAddress::Any, port);
	waitForNewConnection(10);
	if (isListening())
		printf("Listening on port %d\n", port);
	else
		printf("Error trying to listen on port %d\n", port);

	fflush(stdout);


}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

void Server::incomingConnection(qintptr handle) {

	ServerThread* sthread;
	sthread = new ServerThread(handle);
	QObject::connect(sthread,SIGNAL(disconnected()), this, SLOT(decrementClients()));
	QObject::connect(sthread,SIGNAL(connected()), this, SLOT(incrementClients()));
	sthread->start();

}

void Server::incrementClients() {
	clientsConnected++;
	printf("Clients connected: %d\r", clientsConnected);
}

void Server::decrementClients() {
	clientsConnected--;
	printf("Clients connected: %d\r", clientsConnected);
}
