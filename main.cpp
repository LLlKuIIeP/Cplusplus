#include <QCoreApplication>
#include <QtWidgets>

#include <QDebug>

int main(int argc, char *argv[])
{
	qDebug() << "hello\n";
	QApplication app(argc, argv);
	QWidget wgt;
	wgt.setWindowTitle("Hello world");

	wgt.show();




	return app.exec();

}
