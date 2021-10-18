#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow() {
	//Le widget dans lequel tout s'affiche
	widget_general = new QWidget;
	QHBoxLayout * qbl_general = new QHBoxLayout;
	widget_general->setLayout(qbl_general);
	this->setCentralWidget(widget_general);

	//Ajout d'une scene
	scene = new Scene(this);
	view = new QGraphicsView(scene, this);

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	qbl_general->addWidget(view);

}

MainWindow::~MainWindow() {
	std::cout << "Appel du destructeur de MainWindow" << std::endl;
}
