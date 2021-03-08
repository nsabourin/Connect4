#include "GameMech.h"

//Constructeur
GameMech::GameMech(int p_ligne_max, int p_colonne_max) {

	tokens = 0;
	victoire = false;
	turn = 0;
	max_ligne = p_ligne_max;
	max_colonne = p_colonne_max;


	for (int i = 0; i < max_ligne; i++) {
		for (int j = 0; j < max_colonne; j++) {
			tableau[i][j] = EMPTY;
		}
	}
}

/*		  **getValueAt**
Entree	: nb de lignes (entier) & nb de colonnes (char)
Sortie	: Position drop (entier)
Role	: Retourner le tableau avec le bon nb de lignes et colonnes
*/
char GameMech::getValueAt(int ligne, int colonne) {
	return tableau[ligne][colonne];
}

/*		  **jouerTour**
Entree	: n0 de rangee (entier)
Sortie	: Position drop (entier)
Role	: Calculer le tour joue
*/
int GameMech::jouerTour(int colonne) {
	char joueur_turn;
	if (turn % 2) { joueur_turn = JOUEUR1; }
	else { joueur_turn = JOUEUR2; }
	if (tableau[0][colonne] == ' ') {
		int i;
		for (i = 0; tableau[i][colonne] == EMPTY; i++) {
			if (i == max_ligne - 1) {
				tableau[i][colonne] = joueur_turn;
				turn++;
				tokens++;
				return i;
			}
		}
		i--;
		tableau[i][colonne] = joueur_turn;
		turn++;
		tokens++;
		return i;
	}
	else {
		return -1;
	}
}

/*		  **verificationMegaUltime**
Entree	: n0 de rangee (entier) & position de drop (entier)
Sortie	: Gagne ou pas (booleen)
Role	: Verifier s'il y a victoire
*/
bool GameMech::verificationMegaUltime(int d, int r) {

	//Initialisation des variables
	char joueur = tableau[r][d];

	int vertical = 1;
	int horizontal = 1;
	int diag1 = 1;
	int diag2 = 1;
	int i, j;

	/********************Verification horizontale********************/

	//Regarder a gauche
	for (j = d - 1; tableau[r][j] == joueur && j >= 0; j--) {
		horizontal++;
	}

	//Regarder a droite
	for (j = d + 1; tableau[r][j] == joueur && j <= max_colonne; j++) {
		horizontal++;
	}

	//Condition de victoire (connect four)
	if (horizontal >= 4) { return true; }


	/********************Verification verticale********************/

	//Regarder en dessous
	for (i = r + 1; tableau[i][d] == joueur && i < max_ligne; i++) {
		vertical++;
	}

	//Regarder au dessus
	for (i = r - 1; tableau[i][d] == joueur && i >= 0; i--) {
		vertical++;
	}

	//Condition de victoire (connect four)
	if (vertical >= 4) { return true; }


	/********************Verification diagonale (1)********************/

	//Regarder au dessus a gauche 
	for (i = r - 1, j = d - 1; tableau[i][j] == joueur && i >= 0 && j < max_colonne; diag1++) {
		i--;
		j--;
	}

	//Regarder en bas a droite
	for (i = r + 1, j = d + 1; tableau[i][j] == joueur && i < max_ligne && j >= 0; diag1++) {
		i++;
		j++;
	}

	//Condition de victoire (connect four)
	if (diag1 >= 4) { return true; }


	/********************Verification diagonale (2)********************/

	//Regarder au dessus a droite
	for (i = r - 1, j = d + 1; tableau[i][j] == joueur && i >= 0 && i < max_colonne; diag2++) {
		i--;
		j++;
	}

	//Regarder au dessus a gauche
	for (i = r + 1, j = d - 1; tableau[i][j] == joueur && i < max_ligne && j >= 0; diag2++) {
		i++;
		j--;
	}

	//Condition de victoiree (connect four)
	if (diag2 >= 4) { return true; }
	return false;
}

int GameMech::getTokens() {
	return tokens;
}
int GameMech::getTurn() {
	return turn;
}

int GameMech::getMaxLigne() {
	return max_ligne;
}
int GameMech::getMaxColonne() {
	return max_colonne;
}

//Destructeur
GameMech::~GameMech() {}