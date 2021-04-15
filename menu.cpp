#include "menu.h"

//Constructeur de la fenêtre principale
Menu::Menu(QWidget* parent) : QMainWindow(parent)
{	
	initialisationFenetre();
}

void Menu::setBackGroundMenu1()
{
	QPalette palette;
	QPixmap pixMap("backscreen.png");
	pixMap = pixMap.scaled(size(), Qt::IgnoreAspectRatio);
	palette.setBrush(backgroundRole(), QBrush(pixMap));
	this->setPalette(palette);
}
void Menu::setBackGroundTableau()
{
	this->setStyleSheet("background-color: blue;");
}
void Menu::initialisationFenetre()
{
	//Mise en page de la fenêtre principale
	setMinimumSize(800, 600);
	setWindowTitle("ChugFour 1.0");
	setAutoFillBackground(true);
	setBackGroundMenu1();

	//Initialisation des widgets pour le jeu
	mainWidget = new QWidget();
	tableau = new Tableau(this);
	menuOrdi = new menuAI(this);

	//Initialisation des boutons pour le menu principal
	jouerAmi = new QPushButton("1 vs 1", this);
	jouerAI = new QPushButton("1 vs AI", this);
	quitter = new QPushButton("Quitter", this);

	jouerAmi->setFixedWidth(200);
	jouerAI->setFixedWidth(200);
	quitter->setFixedWidth(200);
	jouerAmi->setFixedHeight(50);
	jouerAI->setFixedHeight(50);
	quitter->setFixedHeight(50);

	buttonBox = new QGridLayout(this);
	//Ajout des boutons dans un QGridLayout pour les avoir en ligne droite
	buttonBox->addWidget(jouerAmi, 0, 0);
	buttonBox->addWidget(jouerAI, 1, 0);
	buttonBox->addWidget(quitter, 2, 0);
	mainWidget->setLayout(buttonBox);

	//Connexion des différents boutons avec une action
	connect(jouerAmi, SIGNAL(clicked()), this, SLOT(clicAmi()));
	connect(jouerAI, SIGNAL(clicked()), this, SLOT(clicAI()));
	connect(quitter, SIGNAL(clicked()), this, SLOT(clicQuitter()));

	//Affichage du menu principal dans la mainWindow
	this->setCentralWidget(mainWidget);
}
void Menu::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Left && tableau->getCurseur() > 0)
	{
		int temp = tableau->getCurseur();
		temp--;
		tableau->setCurseur(temp);
	}
	if (event->key() == Qt::Key_Right && tableau->getCurseur() < 6)
	{
		int temp = tableau->getCurseur();
		temp++;
		tableau->setCurseur(temp);
	}
	tableau->moveCurseur();
}
void Menu::clicAmi()
{
	//On change la couleur de l'arrière plan pour mieux voir les cases.
	setBackGroundTableau();
	//Affichage du jeu dans la mainWindow
	this->setCentralWidget(tableau);
	

}
void Menu::clicAI()
{
	menuOrdi->show();
	this->setCentralWidget(menuOrdi);
}
void Menu::clicQuitter()
{
	exit(EXIT_SUCCESS);
}

