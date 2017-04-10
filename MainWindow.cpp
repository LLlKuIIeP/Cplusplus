MainWindow::MainWindow(QObject *parent) : QObject(parent), m_qwgt({}) {
	m_qwgt.setWindowTitle("Hello world");
	m_menu_bar = std::make_unique<QMenuBar>(&m_qwgt);
	//m_menu_bar->addMenu("Меню");

//	std::unique_ptr<QMenu> menu = std::make_unique<QMenu>("menu");
//	std::unique_ptr<QMenu> help = std::make_unique<QMenu>("help");

//	m_top_menu.push_back(menu);
//	m_top_menu.push_back(help);

	m_top_menu.push_back(std::make_unique<QMenu>("menu"));
	m_top_menu.push_back(std::make_unique<QMenu>("help"));

	///m_menu_bar->addMenu(menu.get());
	///std::unique_ptr<QMenu> help = std::make_unique<QMenu>("help");
	///m_menu_bar->addMenu(help.get());

}

void MainWindow::show() {
	for(auto &elem : m_top_menu) {
		m_menu_bar->addMenu(elem.get());
	}

	m_qwgt.show();
}

void MainWindow::click_help()
{
	qDebug() << "\n\tClick \"help\"\n";
}
