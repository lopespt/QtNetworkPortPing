/*
 * Client.h
 *
 *  Created on: 03/07/2014
 *      Author: wachs
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <assert.h>
#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>
#include "Packet.h"
#include <QTimer>

class Client: public QObject {
Q_OBJECT
public:
	Client(QHostAddress& address, quint16 port, unsigned int packetsSize);
	virtual ~Client();

public slots:
	void sendPacket();
	void receiveResponse();

private slots:
	void onConnected();
	void connect(const QHostAddress&, quint16);

signals:

	void connected();
	void disconnected();

private:
	QTcpSocket *socket;
	QTimer timer;
	unsigned int packetsSize;
};

#endif /* CLIENT_H_ */
