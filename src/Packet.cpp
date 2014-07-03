/*
 * Packet.cpp
 *
 *  Created on: 03/07/2014
 *      Author: wachs
 */

#include "Packet.h"

Packet::Packet(int size) {
	this->size = size;
	content = QByteArray(size, 0);
	date = QDateTime(QDateTime::currentDateTime());
}

Packet::Packet(QByteArray bytes) :
		size(0) {
	QDataStream in(&bytes, QIODevice::ReadOnly);
	in >> date;
	in >> size;
	content.resize(size);
	content.insert(0, bytes.data() + sizeof(QDateTime) + sizeof(unsigned int));
}

Packet::~Packet() {
	// TODO Auto-generated destructor stub
}

