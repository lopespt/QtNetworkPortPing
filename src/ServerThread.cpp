/*
 * ServerThread.cpp
 *
 *  Created on: 03/07/2014
 *      Author: wachs
 */

#include "ServerThread.h"

ServerThread::ServerThread(qintptr handle) :
		QThread() {

	this->socket = new QTcpSocket();
	this->socket->setSocketDescriptor(handle);
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(receivedPacket()));
	QObject::connect(socket, SIGNAL(disconnected()), this,
			SLOT(onDisconnection()));
	QObject::connect(socket, SIGNAL(connected()), this,
				SLOT(onConnection()));


	this->socket->setReadBufferSize(50 * 1024);

}

ServerThread::~ServerThread() {
	socket->close();
}

void ServerThread::run() {
	this->socket->open(QIODevice::ReadWrite);
}

void ServerThread::receivedPacket() {
	QByteArray bytesRecieved;
	//while (!socket->atEnd()) {
	bytesRecieved = socket->readAll();
	//socket->waitForReadyRead(100);
	//}

	printf("Received Packet!\n");
	Packet p;
	socket->write(bytesRecieved);
	socket->flush();
	fflush(stdout);
}

void ServerThread::onDisconnection() {
	emit disconnected();
}

void ServerThread::onConnection() {
	emit connected();
}
