#include "MainWindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent) {
	qwgt.setWindowTitle("Hello world");

}

void MainWindow::show() {
	qwgt.show();
}
