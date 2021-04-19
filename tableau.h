#ifndef TABLEAU_H
#define TABLEAU_H

#include <vector>
#include <QMainWindow>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QDebug>
#include "CommunicationFPGA.h"
#include <iostream>
class Tableau : public QWidget {

    Q_OBJECT

public:

    //Constr et destr
    explicit Tableau(QWidget* parent = nullptr);
    ~Tableau();


    int verifVictoire(); //Valeurs de retour( 1 : j1, 2 : j2, 0 : Partie nulle)
    void affichageMegaUltime();
    int getCurseur();
    void setCurseur(int);
    void writeCurseur();
    void jouerTour(int colonne);
    bool verificationMegaUltime(int d, int r,int player);
    int detectePhoneme(CommunicationFPGA port);

    //Méthode pour vérifier la valeur dans une case du tableau
    int getCase(int i, int j) {
        return tableau[i][j];
    }
    //Méthode pour insérer une valeur dans une case du tableau
    void setCase(int x, int y) {
        tableau[x][y] = 2;
    }

private:
    CommunicationFPGA port;
    void createTableau();
    void initTableau();
    int** tableau;
    int tokenDeSuite; //Le but de la victoire est de se rendre a 4
    int rowCount = 7;
    int columnCount = 7;
    int curseur = 3;
    int turn = 0;
    int tokens = 0;
    QGridLayout* grille;
    QImage* token1;
    QImage* token2;
    QImage* vide;
    QPixmap* toke1;
    QPixmap* toke2;
    QPixmap* videe;
    QLabel* tok1;
    QLabel* tok2;
    QLabel* videee;
    QLabel* transLabel;
    QLayoutItem* testeur;
    
};
#endif // BOARD_H