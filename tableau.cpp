#include "tableau.h"
#define EMPTY 0
#define jeton1 1
#define jeton2 2
#define JOUEUR1 1
#define JOUEUR2 2

// numeros de registres correspondants pour les echanges FPGA <-> PC  ...
unsigned const int nreg_lect_stat_btn = 0;  // fpga -> PC  Statut et BTN lus FPGA -> PC
unsigned const int nreg_lect_swt = 1;       // fpga -> PC  SWT lus FPGA -> PC
unsigned const int nreg_lect_cmpt_t = 2;    // fpga -> PC  compteur temps FPGA -> PC 
unsigned const int nreg_lect_can0 = 3;      // fpga -> PC  canal 0 lus FPGA -> PC
unsigned const int nreg_lect_can1 = 4;      // fpga -> PC  canal 1 lus FPGA -> PC
unsigned const int nreg_lect_can2 = 5;      // fpga -> PC  canal 2 lus FPGA -> PC
unsigned const int nreg_lect_can3 = 6;      // fpga -> PC  canal 3 lus FPGA -> PC
unsigned const int nreg_ecri_aff7sg0 = 7;   // PC -> fpga (octet 0  aff.7 seg.)
unsigned const int nreg_ecri_aff7sg1 = 8;   // PC -> fpga (octet 1  aff.7 seg.)
unsigned const int nreg_ecri_aff7dot = 9;   // PC -> fpga (donnees dot-points)
unsigned const int nreg_ecri_led = 10;      // PC -> fpga (donnees leds)
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
    test = new QWidget();
    grille = new QGridLayout(this);
    token1 = new QImage(100,100,QImage::Format::Format_RGB32);
    token2 = new QImage(100, 100, QImage::Format::Format_RGB32);
    vide = new QImage(100, 100, QImage::Format::Format_RGB32);
    toke1 = new QPixmap();
    toke2 = new QPixmap();
    videe = new QPixmap();
    tok1 = new QLabel();
    tok2 = new QLabel();
    videee = new QLabel();
    token1->load("twiJaune.png");
    token2->load("twiRouge.png");
    vide->load("vide2.png");
    *token2 = token2->scaled(100, 100, Qt::KeepAspectRatio);
    *token1 = token1->scaled(100, 100, Qt::KeepAspectRatio);
    *vide = vide->scaled(100, 100, Qt::KeepAspectRatio);

    toke1->convertFromImage(*token1);
    toke2->convertFromImage(*token2);
    videe->convertFromImage(*vide);

    tok1->setPixmap(*toke1);
    tok2->setPixmap(*toke2);
    videee->setPixmap(*videe);


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
void Tableau::writeCurseur()
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
                writeCurseur();
                testeur = verificationMegaUltime(colonne, c,joueur_turn);
                if (testeur == true)
                {
                    animeVictoire();
                }
                break;
            }
        }
        
        tableau[c][colonne] = joueur_turn;
        turn++;
        tokens++;
        affichageMegaUltime();
        writeCurseur();
        testeur = verificationMegaUltime(colonne, c,joueur_turn);
        if (testeur == true)
        {
            animeVictoire();
        }
    }
}
//Encore à vérifier
int Tableau::detectePhoneme(CommunicationFPGA port)
{

    bool sortie = false;
    int valeur;
    int detect[4] = { 0 };
    int valBouton = 0;
    int valtest[4] = { 0 };
    int valeursDetection[12][2] = {
    {200,255},{150,225},{0,110},{32,112},{80,208},{25,125},{0,35},{0,45},
    {80,130},{0,30},{5,40},{0,30} };

    /*do {

    }
    }while(time<2)*/
    for (int i = 0; i < 4; i++) 
    {
        port.lireRegistre(i, valtest[i]);
        qDebug() << valtest[i];
    }

    if (valtest[0] >= valeursDetection[0][0] && valtest[0] <= valeursDetection[0][1])
    {
        detect[0]++;

    }
    if (valtest[0] >= valeursDetection[4][0] && valtest[0] <= valeursDetection[4][1])
    {
        detect[1]++;

    }
    if (valtest[0] >= valeursDetection[8][0] && valtest[0] <= valeursDetection[8][1])
    {
        detect[2]++;

    }

    if (valtest[1] >= valeursDetection[1][0] && valtest[1] <= valeursDetection[1][1])
    {
        detect[0]++;
    }
    if (valtest[1] >= valeursDetection[5][0] && valtest[1] <= valeursDetection[5][1])
    {
        detect[1]++;

    }
    if (valtest[1] >= valeursDetection[9][0] && valtest[1] <= valeursDetection[9][1])
    {
        detect[2]++;

    }
    if (valtest[2] >= valeursDetection[2][0] && valtest[2] <= valeursDetection[2][1])
    {
        detect[0]++;
    }
    if (valtest[2] >= valeursDetection[6][0] && valtest[2] <= valeursDetection[6][1])
    {
        detect[1]++;

    }
    if (valtest[2] >= valeursDetection[10][0] && valtest[2] <= valeursDetection[10][1])
    {
        detect[2]++;

    }
    if (valtest[3] >= valeursDetection[3][0] && valtest[3] <= valeursDetection[3][1])
    {
        detect[0]++;
    }
    if (valtest[3] >= valeursDetection[7][0] && valtest[3] <= valeursDetection[7][1])
    {
        detect[1]++;

    }
    if (valtest[3] >= valeursDetection[11][0] && valtest[3] <= valeursDetection[11][1])
    {
        detect[2]++;

    }
    for (int i = 0;i < 4;i++)
    {
        if (detect[i] == 4)
        {
            return i;
        }
    }
    return -1;
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
    int i, j = 0;

    /********************Verification horizontale********************/

    //Regarder a gauche
    for (j = d - 1;j >= 0; j--) {
        if (tableau[r][j] == joueur)
        {
            horizontal++;
        }
        
    }

    //Regarder a droite
    for (j = d + 1;j <= columnCount-1; j++) {
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
    for (i = r - 1, j = d - 1;i >= 0 && j < columnCount-1; i--,j--) {
        if (tableau[i][j] == joueur)
        {
            diag1++;
        }

    }

    //Regarder en bas a droite
    for (i = r + 1, j = d + 1;i < rowCount-1 && j >= 0;i++,j++) {
        if (tableau[i][j] == joueur)
        {
            diag1++;
        }

    }

    //Condition de victoire (connect four)
    if (diag1 >= 4) { return true; }


    /********************Verification diagonale (2)********************/

    //Regarder au dessus a droite
    for (i = r - 1, j = d + 1;i >= 0 && i < columnCount;i--,j++) {
        if (tableau[i][j] == joueur)
        {
            diag2++;
            i--;
            j++;
        }

    }

    //Regarder au dessus a gauche
    for (i = r + 1, j = d - 1;i < rowCount-1 && j >= 0;i++,j--) {
        if (tableau[i][j] == joueur)
        {
            diag2++;
        }

    }

    //Condition de victoiree (connect four)
    if (diag2 >= 4) { return true; }
    return false;
}
//Fonction permettant de visualiser la victoire avec une animation digne de ce nom
void Tableau::animeVictoire()
{
    QMessageBox* box = new QMessageBox();
    QGridLayout* test = new QGridLayout(box);
    icon_label = new QLabel(box);
    movie = new QMovie("gifTwistea.gif");
    box->setStyleSheet("QLabel{min-width: 358; min-height: 640;}");
    test->addWidget(icon_label, 0, 0);
    box->setLayout(test);
    icon_label->setMovie(movie);
    movie->start();
    mciSendString(L"play finalSound.mp3", NULL, 0, NULL);
    box->show();
}
