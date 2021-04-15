#ifndef TABLEAU_H
#define TABLEAU_H

#include <vector>
#include "deplacement.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>

class Tableau : public QWidget {

    Q_OBJECT

public:

    //Constr et destr
    explicit Tableau(QWidget* parent = nullptr);
    Tableau();
    ~Tableau();


    int verifVictoire(); //Valeurs de retour( 1 : j1, 2 : j2, 0 : Partie nulle)
    int deplacer(int, int);
    void affichageMegaUltime();
    int getCurseur();
    void setCurseur(int);
    void moveCurseur();
    void enleverDeplacement(int i, int j) {
        tableau[i][j] = 0;
    }

    //Méthode pour vérifier la valeur dans une case du tableau
    int getCase(int i, int j) {
        return tableau[i][j];
    }
    //Méthode pour insérer une valeur dans une case du tableau
    void setCase(int x, int y) {
        tableau[x][y] = 2;
    }

private:
    void createTableau();
    void initTableau();
    int** tableau;
    int tokenDeSuite; //Le but de la victoire est de se rendre a 4
    int rowCount = 7;
    int columnCount = 7;
    int curseur = 3;
    QGridLayout* grille;
    QImage* token1;
    QImage* token2;
    QImage* vide;
    QVector<QVector<QLabel*>>* vecCase;
    
};
#endif // BOARD_H