/*
 * Packet.h
 *
 *  Created on: 03/07/2014
 *      Author: wachs
 */

#ifndef PACKET_H_
#define PACKET_H_

#include <QObject>
#include <QDateTime>
#include <QByteArray>
#include <QDataStream>

class Packet {
private:
	QDateTime date;
	unsigned int size;
	QByteArray content;

public:
	Packet(int size = 1024);
	Packet(QByteArray bytes);
	virtual ~Packet();

	const QByteArray getContent() const {
		QByteArray ret;
		QDataStream out(&ret, QIODevice::ReadWrite);
		out << date;
		out << size;
		ret.append(content);
		return ret;
	}

	const QDateTime& getDate() const {
		return date;
	}

	void setDate(const QDateTime& date) {
		this->date = date;
	}
};

#endif /* PACKET_H_ */
