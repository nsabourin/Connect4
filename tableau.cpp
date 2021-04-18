#include "tableau.h"
#define EMPTY 0
#define jeton1 1
#define jeton2 2
#define JOUEUR1 1
#define JOUEUR2 2

//Constructeur du menu principal
Tableau::Tableau(QWidget* parent) : QWidget(parent)
{
    initTableau();
	createTableau();
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
            if (getCase(i,j) == jeton1)
            {
                temp->convertFromImage(*token1);
            }
            else if (getCase(i,j) == jeton2)
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
//Création d'un tableau avec les valeurs de bases 0
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
            tableau[i][j] = EMPTY;
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
                temp->convertFromImage(*token2);
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
            if (turn % 2)
            {
                temp->convertFromImage(*token1);
                t->setPixmap(*temp);
                grille->addWidget(t, 0, i, 1, 1);
            }
            else
            {
                temp->convertFromImage(*token2);
                t->setPixmap(*temp);
                grille->addWidget(t, 0, i, 1, 1);
            }

        }
        else
        {
            t->setPixmap(*temp);
            grille->addWidget(t, 0, i, 1, 1);
        }
    }
}

void Tableau::jouerTour(int colonne)
{
    int joueur_turn;
    int c = 0;
    bool testeur = true;
    if (turn % 2) { joueur_turn = JOUEUR1; }
    else { joueur_turn = JOUEUR2; }
    if (tableau[0][colonne] == EMPTY) {
        int i;
        for (i = 1; i<rowCount-1; i++)
        {
            if (tableau[i][colonne] == EMPTY)
            {
                c++;
            }
            if (i == columnCount - 1)
            {
                tableau[i][colonne] = joueur_turn;
                turn++;
                tokens++;
                affichageMegaUltime();
                moveCurseur();
                //testeur = verificationMegaUltime(colonne, c,joueur_turn); ** à faire fonctionner**
                if (testeur == true)
                {
                    qDebug() << "victoire";
                }
                else
                {
                    qDebug() << "try harder";
                }
                break;
            }
        }
        
        tableau[c][colonne] = joueur_turn;
        turn++;
        tokens++;
        affichageMegaUltime();
        moveCurseur();
        //testeur = verificationMegaUltime(colonne, c,joueur_turn); **à faire fonctionner**
        if (testeur == true)
        {
            qDebug() << "victoire";
        }
        else
        {
            qDebug() << "try harder";
        }
    }
}
/*		  **verificationMegaUltime**
Entree	: n0 de rangee (entier) & position de drop (entier)
Sortie	: Gagne ou pas (booleen)
Role	: Verifier s'il y a victoire
*/
bool Tableau::verificationMegaUltime(int d, int r,int player) 
{

    //Initialisation des variables
    
    int joueur = player;
    int vertical = 1;
    int horizontal = 1;
    int diag1 = 1;
    int diag2 = 1;
    int i, j;

    /********************Verification horizontale********************/

    //Regarder a gauche
    for (j = d - 1;j >= 0; j--) {
        if (tableau[r][j] == joueur)
        {
            horizontal++;
        }
        
    }

    //Regarder a droite
    for (j = d + 1;j <= columnCount; j++) {
        if (tableau[r][j] == joueur)
        {
            horizontal++;
        }
        
    }

    //Condition de victoire (connect four)
    if (horizontal >= 4) { return true; }


    /********************Verification verticale********************/

    //Regarder en dessous
    for (i = r + 1;i < rowCount-1; i++) {
        if (tableau[i][d] == joueur)
        {
            vertical++;
        }
        
    }

    //Regarder au dessus
    for (i = r - 1;i >= 0; i--) {
        if (tableau[i][d] == joueur)
        {
            vertical++;
        }
        
    }

    //Condition de victoire (connect four)
    if (vertical >= 4) { return true; }


    /********************Verification diagonale (1)********************/

    //Regarder au dessus a gauche 
    for (i = r - 1, j = d - 1;i >= 0 && j < columnCount; diag1++) {
        if (tableau[i][j] == joueur)
        {
            i--;
            j--;
        }

    }

    //Regarder en bas a droite
    for (i = r + 1, j = d + 1;i < rowCount-1 && j >= 0; diag1++) {
        if (tableau[i][j] == joueur)
        {
            i++;
            j++;
        }

    }

    //Condition de victoire (connect four)
    if (diag1 >= 4) { return true; }


    /********************Verification diagonale (2)********************/

    //Regarder au dessus a droite
    for (i = r - 1, j = d + 1;i >= 0 && i < columnCount; diag2++) {
        if (tableau[i][j] == joueur)
        {
            i--;
            j++;
        }

    }

    //Regarder au dessus a gauche
    for (i = r + 1, j = d - 1;i < rowCount-1 && j >= 0; diag2++) {
        if (tableau[i][j] == joueur)
        {
            i++;
            j--;
        }

    }

    //Condition de victoiree (connect four)
    if (diag2 >= 4) { return true; }
    return false;
}

