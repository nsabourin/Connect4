/*		Connect Four
Type		: Application console
Equipe		: P1
Langage		: C
Creation	: 2021/02/14
*/

#include <iostream>

//0. Definitions des fonctions
int		jouerTour(int, char);
void	affichageMegaUltime(void);
bool	verificationMegaUltime(int, int);

char tableau[6][7];

int main() {

	//1. Remplir le tableau vide (espacements)
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j <= 7; j++) {
			tableau[i][j] = ' ';
		}
	}

	//2. Afficher tableau vide 
	affichageMegaUltime();

	//3. Initialisation des variables
	char	joueur			= 15;
	int		drop			= 0;
	int		tokens			= 0;
	int		choix_rangee;		
	bool	victoire	= false;

	//4. Actions
	do {

		//4.1 Si erreur dans le dernier tour
		if (drop != -1) {
			
			//4.1.1 Si j2 a joue, c'est le tour de j1
			if (joueur == 15) {
				std::cout << "Joueur 1, indiquer la position voulue : ";
				joueur = 254;	//token pour l'affichage 
			}
			
			//4.1.2 L'inverse
			else {
				std::cout << "Joueur 2, indiquer la position voulue : ";
				joueur = 15;	//token pour l'affichage
			}
		}

		//4.2 Boucle true
		while (true) {
			
			//4.2.1 Arret de la boucle si egalite
			if (tokens == 42) { break; }
			std::cin >> choix_rangee;
			choix_rangee--;				//Ajuster pour indice 1 = 0 dans les tableaux

			//4.2.2 Arret de la boucle si le choix est OK
			if (choix_rangee <= 6 && choix_rangee >= 0) { break; }
			else { std::cout << std::endl << "Entrer un indice entre 1 et 7 : "; }

			//4.2.3 Traiter la possibilite de mauvaise entree avec cin.fail()
			/****************Pas de break ici*******************************/
		}
		
		//4.3 Traiter l'egalite (break encore)
		if (tokens == 42) { break; }

		//4.4 Jouer tour
		drop = jouerTour(choix_rangee, joueur);

		//4.5 Traiter le retour -1 donc si la colonne est pleine
		if (tokens == -1) { 
			std::cout << "Colonne pleine!\nEntrer un indice entre 1 et 7 : ";
		}

		//4.6 Refresh pour afficher le nouveau tableau si pas de victoire
		else {
			victoire = verificationMegaUltime(choix_rangee, drop);
			tokens++;
			system("CLS");
			affichageMegaUltime();
		}
	} while (victoire);
	system("CLS");

	//5. Un coup sorti de la boucle, on peut traiter l'egalite
	if (tokens == 42) {
		std::cout << "Egalite!" << std::endl;
		std::cin.ignore();
		return 0;
	}

	//6. Traiter la victoire
	std::string message = (joueur == 15) ? "Victoire eclatante du joueur 1!" : "Victoire epoustouflante du joueur 2!";
	std::cout << message << std::endl;

	std::cin.ignore();

	return 0;
}

/*		  **jouerTour**
Entree	: n0 de rangee (entier) & joueur (char)
Sortie	: Position drop (entier)
Role	: Calculer le tour joue
*/
int jouerTour(int alpha, char joueur) {
	if (tableau[0][alpha] == ' ') {
		int i;
		for (i = 0; tableau[i][alpha] == ' '; i++) {
			if (i == 5) {
				tableau[i][alpha] = joueur;
				return i;
			}
		}
		i--;
		tableau[i][alpha] = joueur;
		return i;
	}
	else {
		return - 1;
	}
}

/*		  **affichageMegaUltime**
Entree	: void
Sortie	: void
Role	: Afficher de maniere stylee le board
*/
void affichageMegaUltime() {

	//Print les indices
	std::cout << " 1   2   3   4   5   6   7\n";

	//Bboucle le tableau (j, k et l sont les colonnes)
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j <= 6; j++) { 
			std::cout << char(218) << char(196) << char(191) << " "; 
		}
		std::cout << std::endl;

		for (int k = 0; k <= 6; k++) { 
			std::cout << char(179) << tableau[i][k] << char(179) << " "; 
		}
		std::cout << std::endl;

		for (int l = 0; l <= 6; l++) { 
			std::cout << char(192) << char(196) << char(217) << " "; 
		}
		std::cout << std::endl;
	}
}

/*		  **verificationMegaUltime**
Entree	: n0 de rangee (entier) & position de drop (entier)
Sortie	: Gagne ou pas (booleen)
Role	: Verifier s'il y a victoire
*/
bool verificationMegaUltime(int r, int d) {
	
	//Initialisation des variables
	char joueur = tableau[r][d];
	
	int vertical	= 1;
	int horizontal	= 1;
	int diag1		= 1;
	int diag2		= 1;
	int i, j;

	/********************Verification horizontale********************/
	
	//Regarder a gauche
	for (j = d - 1; tableau[r][j] == joueur && j >= 0; j--) {
		horizontal++;
	}

	//Regarder a droite
	for (j = d + 1; tableau[r][j] == joueur && j <= 6; j++) {
		horizontal++;
	}

	//Condition de victoire (connect four)
	if (horizontal >= 4) { return true; }


	/********************Verification verticale********************/

	//Regarder en dessous
	for (i = r + 1; tableau[i][d] == joueur && i <= 5; i++) {
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
	for (i = r - 1, j = d - 1; tableau[i][j] == joueur && i >= 0 && j <= 6; diag1++) {
		i--;
		j--;
	}

	//Regarder en bas a droite
	for (i = r + 1, j = d + 1; tableau[i][j] == joueur && i <= 5 && j >= 0; diag1++) {
		i++;
		j++;
	}

	//Condition de victoire (connect four)
	if (diag1 >= 4) { return true; }


	/********************Verification diagonale (2)********************/

	//Regarder au dessus a droite
	for (i = r - 1, j = d + 1; tableau[i][j] == joueur && i >= 0 && i <= 6; diag2++) {
		i--;
		j++;
	}

	//Regarder au dessus a gauche
	for (i = r + 1, j = d - 1; tableau[i][j] == joueur && i <= 5 && j >= 0; diag2++) {
		i++;
		j--;
	}

	//Condition de victoiree (connect four)
	if (diag2 >= 4) { return true; }
}

