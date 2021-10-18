#ifndef SCENE_H
#define SCENE_H

#include "mainwindow.h"
#include <QtWidgets>
#include <iostream>
#include <ctime>

class Scene : public QGraphicsScene {
	Q_OBJECT

	public:
		static const int SIZE_W = 600;				// Largeur de la fenêtre
		static const int SIZE_H = 400;				// Hauteur de la fenêtre

		Scene(QObject *parent = 0); 				// Constructeur de la classe Scene
		~Scene();									// Destructeur de la classe Scene
		void keyPressEvent (QKeyEvent *event);		// Fonction qui réupère la touche pressée


	public slots:
		void update();								// Fonction qui update la position des éléments de la fenêtre
	
	private: 
		QTimer *timer;								// Timer permettant d'actualiser la fenêtre  au bout d'un certain temps
		QGraphicsTextItem * left_score_affich;		// Score du joueur de gauche
		QGraphicsTextItem * right_score_affich;		// Score du joueur de droite
		QGraphicsTextItem * winner_score;			// Affichage du vainqueur
		QGraphicsPixmapItem * ball;					// Image de balle
		QGraphicsPixmapItem * right_palette;		// Image de palette à droite 
		QGraphicsPixmapItem * left_palette;			// Image de palette à gauche

		int dir_X;									// Direction et vitesse de la balle en X
		int dir_Y; 									// Direction et vitesse de la balle en Y
		int radius_ball;							// Rayon de la balle
		int width_pall; 							// Largeur d'une palette
		int height_pall; 							// Hauteur d'une palette
		int score_left;								// Score du joueur de gauche
		int score_right; 							// Score du joueur de droite
};

#endif