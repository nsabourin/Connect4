#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "tableau.h"
#include "menudeux.h"
#include "windows.h"
#pragma comment(lib, "Winmm.lib")

class Menu : public QMainWindow
{
	Q_OBJECT

public:
	explicit Menu(QWidget *parent = nullptr);

private:
	QWidget* mainWidget;
	QGraphicsScene* backGround;
	Tableau* tableau;
	menuAI* menuOrdi;
	QPushButton* jouerAmi;
	QPushButton* jouerAI;
	QPushButton* quitter;
	QGridLayout* buttonBox;
	
	void setBackGroundMenu1();
	void setBackGroundTableau();
	void initialisationFenetre();
	void keyPressEvent(QKeyEvent* event);

public slots:
	void clicAmi();
	void clicAI();
	void clicQuitter();
};

#endif