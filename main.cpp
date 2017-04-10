#include <QCoreApplication>
#include <QtWidgets>

#include <QDebug>

#include <memory>

#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "MainWindow.h"

class  Print : public QObject
{
	Q_OBJECT

public:
	void print() {
		qDebug() << "\n\tclass Print\n";
	}

public slots:
	void print_slot() {
		print();
	}
};




//class MainWindow : public QObject
//{
//	Q_OBJECT
//public:
//	explicit MainWindow() {
//		qwgt.setWindowTitle("Hello world");
//	}
//	void show() {
//		qwgt.show();
//	}

//private:
//	QWidget qwgt{};
//};




int main(int argc, char *argv[])
{
	qDebug() << "\tПривет мир!\n";


	QApplication app(argc, argv);
///	QWidget wgt;
///	wgt.setWindowTitle("Hello world");

//	//QMenuBar *menuBar = new QMenuBar(&wgt);
//	//menuBar->addMenu("Меню");

//	//std::unique_ptr<QMenuBar> menu_bar = std::make_unique<QMenuBar>(&wgt);
//	//menu_bar->addMenu("Меню");

//	std::unique_ptr<QMenuBar> menu_bar = std::make_unique<QMenuBar>(&wgt);
//	std::unique_ptr<QMenu> menu = std::make_unique<QMenu>("menu");
//	std::unique_ptr<QMenu> file = std::make_unique<QMenu>("file");

//	std::unique_ptr<QMenu> help = std::make_unique<QMenu>("help");
//	std::shared_ptr<QAction> action_help(help->addAction("help"));
//	connect();

//	menu_bar->addMenu(menu.get());
//	menu_bar->addMenu(file.get());
//	menu_bar->addMenu(help.get());

//	std::unique_ptr<QPushButton> button_1 = std::make_unique<QPushButton>("Кнопочка", &wgt);

///	wgt.show();

	MainWindow main_window;
	main_window.show();
	return app.exec();
}
