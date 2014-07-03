/*
 * Program.cpp
 *
 *  Created on: 02/07/2014
 *      Author: wachs
 */

#include "Program.h"

Program::Program() :
		s(NULL) {
	QStringList arguments = QCoreApplication::instance()->arguments();
	bool ok;

	if (arguments.contains("-s", Qt::CaseSensitive)) {

		if (arguments.size() != 3) {
			showHelp();
			return;
		}

		unsigned short port = arguments.at(2).toUShort(&ok);
		//printf("%s \n", arguments.at(2).toStdString().c_str());
		if (ok)
			new Server(port, this);
		else
			showHelp();

	} else if (arguments.contains("-c", Qt::CaseSensitive)) {

		if (arguments.size() != 3) {
			showHelp();
			return;
		}

		QStringList hostStr = arguments.at(2).split(':');
		ok = hostStr.size() == 2;

		if (!ok) {
			showHelp();
			return;
		}

		unsigned short port = hostStr.at(1).toUShort(&ok);

		QList<QHostAddress> ipList =
				QHostInfo::fromName(hostStr.at(0)).addresses();

		if (ipList.empty()) {
			printf("Host not found! Verify DNS or IP Address.\n");
			return;
		}

		//ok = ok & host.setAddress(hostStr.at(0));
		if (!ok)
			showHelp();
		printf("server: %s port: %hu\n",
				ipList.first().toString().toStdString().c_str(), port);
		new Client(ipList.first(), port, 2000);
	} else {
		showHelp();
	}
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

void Program::showHelp() {
	QFile f(":help.txt");
	f.open(QIODevice::ReadOnly);
	printf("%s\n", f.readAll().data());
	f.close();
}