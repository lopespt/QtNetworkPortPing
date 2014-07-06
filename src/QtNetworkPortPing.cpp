#include <QCoreApplication>

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QWidgetAction>
#include <QLineEdit>
#include <QTextBrowser>
#include <QtSql>
#include <QLabel>
#include <QSqlDatabase>
#include <qtcpsocket.h>
#include <qobject.h>
#include <Program.h>

int main(int argc, char * argv[]) {
	QCoreApplication app(argc, argv);

	new Program();
	printf("\n");
	return app.exec();
}
