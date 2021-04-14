#ifndef TABLEAU_H
#define TABLEAU_H

class Tableau {
#include <vector>
#include "deplacement.h"
#include <QMainWindow>
#include <QGridLayout>

class Tableau : public QWidget {
public:

    //Constr et destr
    Tableau();
    Tableau(Tableau&);
    ~Tableau();
    explicit Tableau(QWidget* parent = nullptr);
    int verifVictoire(); //Valeurs de retour( 1 : j1, 2 : j2, 0 : Partie nulle)
    int deplacer(int, int);
    void affichageMegaUltime();
    void enleverDeplacement(int i, int j) {
        tableau[i][j] = 0;
    }

    //getset methodes
    int getCase(int i, int j) {
        return tableau[i][j];
    }
    void setCase(int x, int y) {
        tableau[x][y] = 2;
    }

private:
    int** tableau;
    int tokenDeSuite; //Le but de la victoire est de se rendre a 4
    void createTableau();
};
#endif // BOARD_H