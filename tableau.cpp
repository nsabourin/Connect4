#include "tableau.h"
#define empty 0
#define jeton1 1
#define jeton2 2

//Constructeur du menu principal
Tableau::Tableau(QWidget* parent) : QWidget(parent)
{
    initTableau();
	createTableau();
    
}
//Création d'un tableau avec les valeurs de bases 0
Tableau::Tableau() : tokenDeSuite(0)
{
    tableau = new int* [6];

    //Pour chaque ligne du tableau, on rajoute une colonne de 7 de long
    for (int i = 0;i < 6;i++)
    {
        tableau[i] = new int[7];
    }

    for (int i = 0;i < 6;i++)
    {
        for (int j = 0;j < 7;j++)
        {
            tableau[i][j] = 0;
        }
    }
    
}
//Destructeur pour libérer de la mémoire quand on crée un nouveau tableau
Tableau::~Tableau()
{
    for (int i = 0;i < 6;i++)
    {
        delete[] tableau[i];
    }
}
void Tableau::affichageMegaUltime()
{

    for (int i = 0;i < rowCount-1;i++)
    {
        for (int j = 0;j < columnCount;j++)
        {
            QPixmap* temp = new QPixmap();
            if (getCase(i,j) == 1)
            {
                temp->convertFromImage(*token1);
            }
            else if (getCase(i,j) == 2)
            {
                temp->convertFromImage(*token2);
            }
            else
            {
                temp->convertFromImage(*vide);
            }
            QLabel* t = new QLabel();
            t->setPixmap(*temp);
            grille->addWidget(t, i+1, j, 1, 1);
        }
    }
}

int Tableau::getCurseur()
{
    return curseur;
}

void Tableau::setCurseur(int a)
{
    curseur = a;
}

void Tableau::initTableau()
{
    tableau = new int* [6];

    for (int i = 0;i < 6;i++)
    {
        tableau[i] = new int[7];
    }

    for (int i = 0;i < 6;i++)
    {
        for (int j = 0;j < 7;j++)
        {
            if (j == 6)
            {
                tableau[i][j] = 1;
            }
            else
            {
                tableau[i][j] = 0;
            }
            
        }
    }
}

void Tableau::createTableau()
{
    vecCase = new QVector<QVector<QLabel*>>(rowCount);
    grille = new QGridLayout(this);
    token1 = new QImage(100,100,QImage::Format::Format_RGB32);
    token2 = new QImage(100, 100, QImage::Format::Format_RGB32);
    vide = new QImage(100, 100, QImage::Format::Format_RGB32);
    token1->load("twiJaune.png");
    token2->load("twiRouge.png");
    vide->load("vide.png");
    *token2 = token2->scaled(100, 100, Qt::KeepAspectRatio);
    *token1 = token1->scaled(100, 100, Qt::KeepAspectRatio);
    *vide = vide->scaled(100, 100, Qt::KeepAspectRatio);

    for (int i = 0;i < rowCount;i++)
    {
        
        for (int j = 0;j < columnCount;j++)
        {
            QPixmap *temp = new QPixmap();
            QLabel* t = new QLabel();
            if (i == 0 && j == curseur)
            {
                temp->convertFromImage(*token1);
                t->setPixmap(*temp);
                grille->addWidget(t, i, j, 1, 1);
            }
            else if(i == 0)
            {
                
            }
            else
            {
                temp->convertFromImage(*vide);
                t->setPixmap(*temp);
                grille->addWidget(t, i, j, 1, 1);
            }
        }
    }
    setLayout(grille);
}
void Tableau::moveCurseur()
{
    for (int i = 0;i < rowCount;i++)
    {
        QPixmap* temp = new QPixmap();
        QLabel* t = new QLabel();
        if (i == curseur)
        {
            temp->convertFromImage(*token1);
            t->setPixmap(*temp);
            grille->addWidget(t, 0, i, 1, 1);
        }
        else
        {
            t->setPixmap(*temp);
            grille->addWidget(t, 0, i, 1, 1);
            
        }
    }
}
