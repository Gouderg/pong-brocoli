#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>

#include "scene.h"
class Scene;

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		MainWindow();
		~MainWindow();

	private:
		Scene *scene;
		QWidget *widget_general;
		QGraphicsView *view;


};

#endif