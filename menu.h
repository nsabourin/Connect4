#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedWidget>
#include<QStackedLayout>
#include "tableau.h"
#include "menudeux.h"

class Menu : public QMainWindow
{
	Q_OBJECT

public:
	explicit Menu(QWidget *parent = nullptr);

private:
	QWidget* mainWidget;
	QGraphicsScene* backGround;
	Tableau* tableau;
	void setBackGroundMenu1();
	void setBackGroundTableau();
	void initialisationFenetre();
	void keyPressEvent(QKeyEvent* event);
	Tableau* tab;
	menuAI* menuOrdi;
	QPushButton* jouerAmi;
	QPushButton* jouerAI;
	QPushButton* quitter;
	QGridLayout* buttonBox;
public slots:
	void clicAmi();
	void clicAI();
	void clicQuitter();
};

#endif