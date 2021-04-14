/*
		P1 - Chug Four

Qt, C++, makefile

Cree le 2021-04-12

Membres:
Olivier Rivard, Simon Bradette, Anthony Daunais, Henri Beauregard,
Alexis Dupont, Maxime Grenier-Castillo, Nicolas Sabourin, Michael Kabraelian
*/

#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <Qdebug>

#include "menu.h"
#include "deplacement.h"
#include "jouerToken.h"
#include "tableau.h"

int main(int argc, char* argv[]) {
	QApplication appli(argc, argv);

	//Implementer menu.h avant
	Menu* mainMenu = new Menu;
	menuPrincipal* menu1 = new menuPrincipal;
	mainMenu->setCentralWidget(menu1);
	mainMenu->show();

	return appli.exec();
}