/*		Connect Four
Type		: Application console
Equipe		: P1
Langage		: C++
Creation	: 2021/02/14
*/

#include <iostream>
#include "InterfaceConsole.h"
#include "GameMech.h"

int main() {

	//0. Boucle rejouer
	bool recommencer = true;
	while (recommencer) {
		
		//1. Creation objets necessaires
		interfaceConsole interface;
		GameMech connectF(6, 7);

		//2. Afficher tableau vide & def variables
		interface.affichageMegaUltime(connectF);
		int	drop = 0;
		int choix_rangee = 0;
		bool victoire = false;

		//4. Actions
		do {
			//4.1 Si erreur dans le dernier tour
			if (drop != -1) {

				//4.1.1 Si j2 a joue, c'est le tour de j1
				if ((connectF.getTurn() % 2) == 0) { 
					std::cout << "Joueur 1, indiquer la position voulue : ";
					system("Color 09");
				}

				//4.1.2 L'inverse
				else { 
					std::cout << "Joueur 2, indiquer la position voulue : "; 
					system("Color 0E");
				}
			}

			//4.2 Boucle true
			while (true) {
				//4.2.1 Arret de la boucle si egalite
				if (connectF.getTokens() == 42) { break; }
				std::cin >> choix_rangee;
				choix_rangee--;				//Ajuster pour indice 1 = 0 dans les tableaux

				//4.2.2 Arret de la boucle si le choix est OK
				if (choix_rangee <= 6 && choix_rangee >= 0) { break; }
				else { std::cout << std::endl << "Entrer un indice entre 1 et 7 : "; }

				//4.2.3 Traiter la possibilite de mauvaise entree avec cin.fail()
				/****************Pas de break ici*******************************/
				if (std::cin.fail()) {
					std::cin.clear();	//.clear empeche de loop en essayant de tjrs faire cin->variable
					std::string c;
					std::cin >> c;
					std::cin.ignore();
				}
			}

			//4.3 Traiter l'egalite (break encore)
			if (connectF.getTokens() == 42) { break; }

			//4.4 Jouer tour
			drop = connectF.jouerTour(choix_rangee);

			//4.5 Traiter le retour -1 donc si la colonne est pleine
			if (drop == -1) {
				std::cout << "Colonne pleine!\nEntrer un indice entre 1 et 7 : ";
			}

			//4.6 Refresh pour afficher le nouveau tableau si pas de victoire
			else {
				victoire = connectF.verificationMegaUltime(choix_rangee, drop);
				system("CLS");
				interface.affichageMegaUltime(connectF);
			}

		} while (!victoire);
		

		//5. Un coup sorti de la boucle, on peut traiter l'egalite
		if (connectF.getTokens() == 42) {
			std::cout << "Egalite!" << std::endl;
			std::cin.ignore();
			return 0;
		}
		system("Color 0A");
		//6. Traiter la victoire
		std::string message = (connectF.getTurn() % 2) ? "\n\nVictoire eclatante du joueur 1!" : "Victoire epoustouflante du joueur 2!\n";
		std::cout << message << std::endl;

		//7. Recommencer si le joueur le veut
		int reponse;
		std::cout << "Voulez-vous recommencer? Oui-1	Non-Autre" << std::endl;
		std::cin >> reponse;
		if (reponse == 1) { system("CLS"); }
		else { recommencer = false; }
	}
	std::cin.ignore();
	return 0;
}