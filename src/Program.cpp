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

		if (arguments.size() < 3) {
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
		if (!ok) {
			showHelp();
			return;
		}

		int packetSize = 2000;
		if (arguments.count() == 4) {
			packetSize = arguments.at(3).toInt(&ok);
			//assert(packetSize > 17);
			if (packetSize <= 17) {
				printf("Error: packet size must be greater than 17");
				fflush(stdout);
				return;
			}
		}
		packetSize -= 17;

		if (!ok) {
			showHelp();
			return;
		}

		printf("server: %s port: %hu\n",
				ipList.first().toString().toStdString().c_str(), port);
		new Client(ipList.first(), port, packetSize);
	} else {
		showHelp();
	}
}

Program::~Program() {

}

void Program::showHelp() {
	QFile f(":help.txt");
	f.open(QIODevice::ReadOnly);
	printf("%s\n", f.readAll().data());
	f.close();
	QCoreApplication::exit(0);
}
