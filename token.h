#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <QMessageBox>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent> // Avec touches, a modifier pour boutons FPGA

#include "jouerToken.h"
#include "tableau.h"
#include "menu.h"
#include "infos.h"
#include "ia.h"

class Token :public QGraphicsPixmapItem {
public:
	//Constructeur
	Token(QWidget* parent = nullptr, int a = 25, int c = 75, Infos* = nullptr);

	void actionClavier(QKeyEvent* actionTouche);
	void ptsView(QGraphicsView* vue) {
		view = vue;
	}
protected:
	int index;
	int positionY;
	int tour;
	int ancienIndex;
	int jeu;
	int dep;
	int totalMoves;
	bool passe;
	Tableau* tableau;
	IA minimax;
	QGraphicsView* view;
	Menu* menu;
	Infos* info;
};
#endif // !TOKEN_H