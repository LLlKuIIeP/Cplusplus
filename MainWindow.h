#pragma once

#include <vector>
#include <memory>
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
	void click_help();


private:
	QWidget m_qwgt;
	std::unique_ptr<QMenuBar> m_menu_bar;// = std::make_unique<QMenuBar>(&wgt);
	std::vector<std::unique_ptr<QMenu>> m_top_menu;


};
