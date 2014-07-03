/*
 * Program.h
 *
 *  Created on: 02/07/2014
 *      Author: wachs
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <QObject>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QThread>
#include <QFile>
#include <QHostInfo>
#include "Server.h"
#include "Client.h"

class Program: public QObject {
Q_OBJECT
private:
	QTcpSocket *s;
public:
	Program();
	virtual ~Program();
	void showHelp();

};

#endif /* PROGRAM_H_ */
