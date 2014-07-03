/*
 * Client.cpp
 *
 *  Created on: 03/07/2014
 *      Author: wachs
 */

#include "Client.h"

Client::Client(QHostAddress& address, quint16 port, unsigned int packetsSize) :
		socket(new QTcpSocket(this)) {
	QObject::connect(socket, SIGNAL(readyRead()), this,
			SLOT(receiveResponse()));
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
	this->connect(address, port);

	timer.setInterval(1000);
	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(sendPacket()));
	socket->setReadBufferSize(20 * 1024);
	assert(packetsSize < 64 * 1024);
	this->packetsSize = packetsSize;
}

Client::~Client() {
	//Test
}

void Client::sendPacket() {
	//Maximum TCP packet size
	assert(packetsSize < 64 * 1024);
	Packet packet(packetsSize);
	if (socket->isOpen()) {
		socket->write(packet.getContent());
		//socket->waitForBytesWritten(1000);
	}
	socket->flush();
}

void Client::connect(const QHostAddress& address, quint16 port) {
	socket->connectToHost(address, port, QIODevice::ReadWrite);

}

void Client::receiveResponse() {
	QByteArray packetBytes;
	//while (!socket->atEnd()) {
	packetBytes += socket->readAll();
	//socket->waitForReadyRead(100);
	//}
	Packet packet(packetBytes);
	printf(
			"Response Received from Packet Sent at %s (Size %d) -> Difference: %lld ms\n",
			packet.getDate().toString("dd/MM/yyyy hh:mm:ss").toStdString().c_str(),
			packet.getContent().size(),
			packet.getDate().msecsTo(QDateTime::currentDateTime()));
	fflush(stdout);
}

void Client::onConnected() {
	//printf("Connectado!!!\n");
	timer.start();
	emit connected();
}

