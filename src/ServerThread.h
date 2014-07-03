/*
 * ServerThread.h
 *
 *  Created on: 03/07/2014
 *      Author: wachs
 */

#ifndef SERVERTHREAD_H_
#define SERVERTHREAD_H_

#include <QThread>
#include <QTcpSocket>
#include <QByteArray>
#include <QObject>
#include "Packet.h"

class ServerThread: public QThread {
Q_OBJECT
public:
	ServerThread(qintptr socketDescriptor);
	virtual ~ServerThread();

signals:
	void disconnected();
	void connected();

private:
	QTcpSocket* socket;
	void run();

private slots:
	void receivedPacket();
	void onDisconnection();
	void onConnection();
};

#endif /* SERVERTHREAD_H_ */
