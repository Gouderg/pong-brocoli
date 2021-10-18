#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent) {
	srand(time(NULL));

	// Initialisation du fond
	this->setSceneRect(0,0,SIZE_W, SIZE_H);											// On initialise au dimensions de nos constantes
	this->setBackgroundBrush(Qt::black);											// On met le fond en noir

	// On dessine un trait blanc au milieu pour le fun
	QPen pen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);				// On crée un crayon de couleur blanche, d'épaisseur 1px et qui fais un trait solide
	QLine ligne_middle(SIZE_W / 2, 0, SIZE_W / 2, SIZE_H);							// On place notre ligne au milieu
	this->addLine(ligne_middle, pen);												// On ajoute la ligne à notre scène					

	// On initialise les valeurs autour de la balle
	dir_X = (rand() % (SIZE_W / 100) * 2) - (SIZE_W / 100);							// On génère un nombre relatif pour savoir la vitesse de la balle ainsi que sa direction
	if (dir_X == 0) {dir_X ++;}														// Si le déplacement en x est nul, on l'incrémente de 1
	dir_Y = (rand() % (SIZE_H / 100) * 2) - (SIZE_H / 100);
	if (dir_Y == 0) {dir_Y ++;}														// Si le déplacement en y est nul, on l'incrémente de 1
	radius_ball = QPixmap("balle2.png").height() / 2;								// On récupère le diamètre et on le divise par 2 pour avoir le rayon
	width_pall = QPixmap("palette.png").width();									// On récupère la largeur de la palette
	height_pall = QPixmap("palette.png").height();									// On récupère la hauteur de la palette
	score_left = 0;
	score_right = 0;
	
	// On dessine la balle
	ball = new QGraphicsPixmapItem(QPixmap("balle2.png"));							// On récupère le dessin de la balle
	ball->setPos(SIZE_W / 2 - radius_ball, SIZE_H / 2 - radius_ball);				// On la postionne à l'endroit voulu
	this->addItem(ball);															// On l'ajoute à notre scène

	// On dessine la palette de gauche
	left_palette = new QGraphicsPixmapItem(QPixmap("palette.png"));					// On récupère l'image de la palette
	left_palette->setPos(SIZE_W * 0.042, (SIZE_H - height_pall) / 2);				// On la positionne à gauche
	this->addItem(left_palette);													// On l'ajoute à notre scène
	
	// On dessine la palette de droite
	right_palette = new QGraphicsPixmapItem(QPixmap("palette.png"));				// On récupère l'image de la palette
	right_palette->setPos(SIZE_W - (SIZE_W * 0.042), (SIZE_H - height_pall) / 2);	// On la positionne à droite
	this->addItem(right_palette);													// On l'ajoute à notre scène

	// On dessine le score_board de gauche
	QFont scoreFont("8_Bit_Madness.ttf", 30);										// On déclare notre police d'écriture	
	left_score_affich = this->addText(QString::number(0));							// On initialise le score à 0
	left_score_affich->setDefaultTextColor(Qt::white);								// On colorie le score en blanc
	left_score_affich->setPos(SIZE_W * 0.25,10);									// On positionne le score à gauche
	left_score_affich->setFont(scoreFont);											// On rajoute la police à notre score

	right_score_affich = this->addText(QString::number(0));							// On initialise le score à 0
	right_score_affich->setDefaultTextColor(Qt::white);								// On colorie le score en blanc
	right_score_affich->setPos(SIZE_W*0.75, 10);									// On positionne le score à gauche
	right_score_affich->setFont(scoreFont);											// On rajoute la police à notre score

	timer = new QTimer(this);														// On rajoute un timer à notre scène 
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));						// On lui dit d'appeler la fonction update à la fin du temps
	timer->start(30);																// On met une période de 30 ms
}

Scene::~Scene() {
	std::cout << "Appel du destructeur de scene" << std::endl;
}

// Fonction appelé à chaque fois que le timer s'écoule
void Scene::update() {

	//Si notre balle rencontre un mur sur l'axe des x, on arrete la balle et on la remet au milieu en lui rendant ses valeurs d'origines en rajoutant 1 points au gagnant
	if ((ball->x() + radius_ball > SIZE_W) || (ball->x() + radius_ball < 0)) {
		if (dir_X < 0) {															// Si la balle était dans le sens négatif
			score_right += 1;														// On rajoute +1 au joueur de droite
			right_score_affich->setPlainText(QString::number(score_right));			// On affiche le nouveau résulat	
		} else {
			score_left += 1;														// On rajoute +1 au joueur de gauche
			left_score_affich->setPlainText(QString::number(score_left));			// On affiche le nouveau résultat
		}

		if (score_right >= 5 || score_left >= 5) {
			QFont scoreFont("8_Bit_Madness.ttf", 60);								// On déclare notre police d'écriture	
			winner_score = this->addText("WINNER");									// On affiche le mot "Winner"
			winner_score->setDefaultTextColor(Qt::white);							// On met la couleur en blanc
			winner_score->setPos(SIZE_W * 0.25,SIZE_H * 0.25);						// On le positionne au centre
			winner_score->setFont(scoreFont);	   									// On rajoute la police d'écriture
			timer->stop();															// On arrête le timer
		} else {
			dir_X = (rand() % (SIZE_W / 100) * 2) - (SIZE_W / 100); 				// On régénère la vitesse de la balle en x
			if (dir_X == 0) {dir_X ++;}												// Si le déplacement en x est nul, on l'incrémente de 1				
			dir_Y = (rand() % (SIZE_H / 100) * 2) - (SIZE_H / 100);					// On régénère la vitesse de la balle en y
			if (dir_Y == 0) {dir_Y ++;}												// Si le déplacement en y est nul, on l'incrémente de 1
			ball->setPos(SIZE_W / 2 - radius_ball, SIZE_H / 2 - radius_ball);		// On replace la balle au milieu
		}	

		
	}

	//Si notre balle rencontre un mur sur l'axe des y, on lui fait changer de direction
	if ((ball->y() + radius_ball > SIZE_H) || (ball->y() + radius_ball / 2 < 0)) {
		dir_Y = - dir_Y;
	}

	//Si la balle touche la palette de gauche ou de droite, on la renvoie en incrémentant la vitesse
	if ((left_palette->collidesWithItem(ball) && dir_X < 0) || (right_palette->collidesWithItem(ball) && dir_X > 0)) {
		dir_X = -dir_X;
		if (dir_X < 28 && dir_X > -28) {
			dir_X += (dir_X > 0) ? 2 : -2;	// En fonction du sens, on incrémente la vitesse tant qu'elle est inférieur à 28
		} 
	}

	// if (dir_X > 0) {
	// 	right_palette->setY(ball->y());
	// } else {
	// 	left_palette->setY(ball->y());
	// }
	
	//On fais avancer la balle
	ball->setPos(ball->x() + dir_X, ball->y() + dir_Y);
}

// Fonction qui réupère la touche pressée
void Scene::keyPressEvent (QKeyEvent *event) {

	// Si on appuie sur la touche Z
	if (event->key() == Qt::Key_Z) {						
		if (left_palette->y() == 0) return;							// On regarde si on ne touche pas le haut
		else left_palette->setY(left_palette->y() - 30);			// On remonte de 30 pixels vers le haut
	}

	// Si on appuie sur la touche X
	if (event->key() == Qt::Key_X) {
		if (left_palette->y() + height_pall == SIZE_H) return; 		// On regarde si on ne touche pas la bas
		else left_palette->setY(left_palette->y() + 30); 			// On descend de 30 pixels vers le bas
	}

	//Si on appuie sur la touche I
	if (event->key() == Qt::Key_I) {
		if (right_palette->y() == 0) return;						// On regarde si on ne touche pas le haut
		else right_palette->setY(right_palette->y() - 30); 			// On remonte de 30 pixels vers le bas
	}

	// Si on appuie sur la touche N
	if (event->key() == Qt::Key_N) {
		if (right_palette->y() + height_pall == SIZE_H) return; 	// On regarde si on ne touche pas la bas
		else right_palette->setY(right_palette->y() + 30); 			// On descend de 30 pixels vers le bas
	}

	// Si on appuie sur la touche Espace
	if (event->key() == Qt::Key_Space) {
		if (timer->isActive()) timer->stop();						// Si le timer est activé, on le désactive, 
		else timer->start(30);										// Sinon on l'active
	}

	// Si on appuie sur la touche Echap
	if (event->key() == Qt::Key_Escape) {
		exit(EXIT_FAILURE);											// On quitte le programme
	}	
}	

 