#pragma once

#include <QObject>
#include <QtWidgets>

class MainWindow : public QObject
{
	Q_OBJECT
public:
	explicit MainWindow(QObject *parent = nullptr);
	void show();

signals:

public slots:

private:
	QWidget qwgt{};
};
