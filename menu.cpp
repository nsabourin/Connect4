#include "menu.h"

//Constructeur de la fenêtre principale
Menu::Menu(QWidget* parent) : QMainWindow(parent)
{
	setMinimumSize(800, 600);
	setWindowTitle("ChugFour 1.0");
	setAutoFillBackground(true);
	setBackGround();


}

void Menu::setBackGround()
{
	QPalette palette;
	QPixmap pixMap("path.jpg");
	pixMap = pixMap.scaled(size(), Qt::IgnoreAspectRatio);
	palette.setBrush(backgroundRole(), QBrush(pixMap));
	this->setPalette(palette);
}

//Constructeur du menu principal
menuPrincipal::menuPrincipal(QWidget* parent) : QWidget(parent)
{
	setupMenu();
}
//Fonction permettant d'ajouter tous les widgets nécessaires au bon fonctionnement du menu principal
void menuPrincipal::setupMenu()
{
	//Construction des 3 boutons
	jouerAmi = new QPushButton("1 vs 1");
	jouerAI = new QPushButton("1 vs AI");
	quitter = new QPushButton("Quitter");
	//Création des deux contenants pour les widgets
	mainBox = new QVBoxLayout(this);
	buttonBox = new QHBoxLayout();
	//Ajout des widgets existants dans leur contenant respectif
	buttonBox->addWidget(jouerAmi);
	buttonBox->addWidget(jouerAI);
	buttonBox->addWidget(quitter);
	mainBox->addLayout(buttonBox);

	//connect(jouerAI, &QPushButton);
	//connect(jouerAmi, &QPushButton);
	connect(quitter, &QPushButton::clicked, this, &menuPrincipal::clicQuitter);
}

void menuPrincipal::clicAmi()
{

}
void menuPrincipal::clicAI()
{

}
void menuPrincipal::clicQuitter()
{
	exit(EXIT_SUCCESS);
}