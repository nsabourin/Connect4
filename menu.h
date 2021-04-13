#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

class Menu : public QMainWindow
{
	Q_OBJECT

public:
	explicit Menu(QWidget *parent = nullptr);

private:
	QGraphicsScene* backGround;
	void setBackGround();
};

class menuPrincipal : public QWidget
{
	Q_OBJECT

public:
	explicit menuPrincipal(QWidget* parent = 0);

private:
	void setupMenu();
	QPushButton* jouerAmi;
	QPushButton* jouerAI;
	QPushButton* quitter;
	QVBoxLayout* mainBox;
	QHBoxLayout* buttonBox;
public slots:
	void clicAmi();
	void clicAI();
	void clicQuitter();
};

#endif