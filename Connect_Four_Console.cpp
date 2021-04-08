/*		Connect Four
Type		: Application console
Equipe		: P1
Langage		: C++
Creation	: 2021/02/14
*/

#include <iostream>
#include <chrono>
#include <thread>
#include "InterfaceConsole.h"
#include "GameMech.h"

//**************************************  FPGA  *******************************************
#include "CommunicationFPGA.h"
void testFPGA(CommunicationFPGA port);
//**************************************  FPGA  *******************************************

unsigned const int nreg_lect_stat_btn = 0;  // fpga -> PC  Statut et BTN lus FPGA -> PC
unsigned const int nreg_lect_swt = 1;  // fpga -> PC  SWT lus FPGA -> PC
unsigned const int nreg_lect_cmpt_t = 2;  // fpga -> PC  compteur temps FPGA -> PC
unsigned const int nreg_lect_can0 = 3;  // fpga -> PC  canal 0 lus FPGA -> PC
unsigned const int nreg_lect_can1 = 4;  // fpga -> PC  canal 1 lus FPGA -> PC
unsigned const int nreg_lect_can2 = 5;  // fpga -> PC  canal 2 lus FPGA -> PC
unsigned const int nreg_lect_can3 = 6;  // fpga -> PC  canal 3 lus FPGA -> PC
unsigned const int nreg_ecri_aff7sg0 = 7;  // PC	-> fpga (octet 0  aff.7 seg.)
unsigned const int nreg_ecri_aff7sg1 = 8;  // PC -> fpga (octet 1 aff.7 seg.)
unsigned const int nreg_ecri_aff7dot = 9;  // PC -> fpga (donnees dot-points)
unsigned const int nreg_ecri_led = 10; // PC -> fpga (donnees leds)

int main() {

	

	//**************************************  FPGA  *******************************************
	BOOL statut_port = false;	//Statut du port de comm



	CommunicationFPGA port;	//Instance port de comm
	if (!port.estOk()) {
		std::cout << port.messageErreur() << std::endl;
		return 1;
	}
	else {
		std::cout << "Statut initial du port de communication : " << port.estOk() << std::endl << std::endl;
	}

	/*
	//::::::::::Exemples pour utiliser le port de comm::::::::::

	//Lire registre de l'interface
	int statut_circuit = 0;
	statut_port = port.lireRegistre(nreg_lect_stat_btn, statut_circuit);

	std::cout << "Lecture de statut_circuit : " << (int)statut_circuit << std::endl;
	std::cout << "Lecture de statut_port : " << statut_port << std::endl << std::endl;

	//Lire un registtre des switches
	int swt = 0;																//NOUVEAU vs l'exemple
	if (statut_port)statut_port = port.lireRegistre(nreg_lect_swt, swt);		//lire swt
	else { std::cout << "Erreur port nreg_lect_swt" << std::endl; exit(1); }	//exit clean tout en quittant safely

	//Ecrire registre de l'interface
	statut_port = port.ecrireRegistre(nreg_ecri_led, 1);	//envoye valeur 1 sur led(0) FPGA : signal pr passer en mode connecte
	if (!port.estOk()) {
		std::cout << port.messageErreur() << std::endl;
		return 1;
	}

	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	testFPGA(port);

	system("pause");
	system("cls");
	//**************************************  FPGA  *******************************************
	*/
	
	//0. Boucle rejouer
	bool recommencer = true;
	while (recommencer) {

		int choixJeu;
		int curseur = 4;
		int valBouton = 0;
		char direction;
		
		std::cout << "Jouer 1 vs 1 - 1\nJouer avec l'ordinateur		- 2" << std::endl;
		std::cin >> choixJeu;
		system("cls");


		/********************************************
		*				1 VS 1						*
		*											*
		********************************************/
		if (choixJeu == 1) {
			//1. Creation objets necessaires
			interfaceConsole interface_de_console;
			GameMech connectF(6, 7);

			//2. Afficher tableau vide & def variables
			interface_de_console.affichageMegaUltime(connectF, curseur);
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

					/* SANS CURSEUR
					std::cin >> choix_rangee;
					choix_rangee--;//Ajuster pour indice 1 = 0 dans les tableaux
					
					//4.2.2 Arret de la boucle si le choix est OK
					if (choix_rangee <= 6 && choix_rangee >= 0) { break; }
					else { std::cout << std::endl << "Entrer un indice entre 1 et 7 : "; }
					*/
		
					port.lireRegistre(nreg_lect_stat_btn, valBouton);//std::cin >> direction;
					if (valBouton == 8 && curseur - 1 > 0) {	//direction == 'a' ...
						curseur--; 
						system("cls");
						interface_de_console.affichageMegaUltime(connectF, curseur);
					}
					else if (valBouton == 2 && curseur + 1 < 8) { //direction == 'd' ...
						curseur++; 
						system("cls");
						interface_de_console.affichageMegaUltime(connectF, curseur);
					}
					else if (valBouton == 4) {	//direction == 's' ...
						choix_rangee = curseur-1;
						
						break;
					}
					
					while (valBouton == 8 || valBouton == 4 || valBouton == 2) {
						port.lireRegistre(nreg_lect_stat_btn, valBouton);
					}
					
					

					//4.2.3 Traiter la possibilite de mauvaise entree avec cin.fail()
					/****************Pas de break ici*******************************/
					/*SANS CURSEUR
					if (std::cin.fail()) {
						std::cin.clear();	//.clear empeche de loop en essayant de tjrs faire cin->variable
						std::string c;
						std::cin >> c;
						std::cin.ignore();
					}
					*/

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
					interface_de_console.affichageMegaUltime(connectF, curseur);
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

		/********************************************
		*				1 VS AI						*
		*											*
		********************************************/
		else if (choixJeu == 2) {
			bool tour_ai = false;
			//1. Creation objets necessaires
			interfaceConsole interface_de_console;
			GameMech connectF(6, 7);

			//2. Afficher tableau vide & def variables
			interface_de_console.affichageMegaUltime(connectF, curseur);
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
						std::cout << "Joueur 2 est en train de penser a son tour ... ";
						system("Color 0E");
						tour_ai = true;
					}
				}

				//4.2 Boucle true
				while (true) {
					//4.2.1 Arret de la boucle si egalite
					if (connectF.getTokens() == 42) { break; }

					/*
					if (!tour_ai) {
						std::cin >> choix_rangee;
						choix_rangee--;//Ajuster pour indice 1 = 0 dans les tableaux
					}
					else if (tour_ai) {
						choix_rangee = rand() % 7 + 1;
						choix_rangee--;
					}
					*/

					if (!tour_ai) {

						/*
						std::cin >> direction;
						if (direction == 'a' && curseur - 1 > 0) { curseur--; }
						else if (direction == 'd' && curseur + 1 < 8) { curseur++; }
						else if (direction == 's') {
							choix_rangee = curseur - 1;
							break;
						}
						system("cls");
						interface_de_console.affichageMegaUltime(connectF, curseur);
						*/
						port.lireRegistre(nreg_lect_stat_btn, valBouton);//std::cin >> direction;
						if (valBouton == 8 && curseur - 1 > 0) {	//direction == 'a' ...
							curseur--;
							system("cls");
							interface_de_console.affichageMegaUltime(connectF, curseur);
						}
						else if (valBouton == 2 && curseur + 1 < 8) { //direction == 'd' ...
							curseur++;
							system("cls");
							interface_de_console.affichageMegaUltime(connectF, curseur);
						}
						else if (valBouton == 4) {	//direction == 's' ...
							choix_rangee = curseur - 1;

							break;
						}

						while (valBouton == 8 || valBouton == 4 || valBouton == 2) {
							port.lireRegistre(nreg_lect_stat_btn, valBouton);
						}
					}
					else if (tour_ai) {
						choix_rangee = rand() % 7 + 1;
						choix_rangee--;
						break;
					}

					/*
					//4.2.2 Arret de la boucle si le choix est OK
					if (choix_rangee <= 6 && choix_rangee >= 0) { break; }
					else { std::cout << std::endl << "Entrer un indice entre 1 et 7 : "; }
					*/

					/*
					if (!tour_ai) {
						//4.2.3 Traiter la possibilite de mauvaise entree avec cin.fail()
					/****************Pas de break ici******************************
						if (std::cin.fail()) {
							std::cin.clear();	//.clear empeche de loop en essayant de tjrs faire cin->variable
							std::string c;
							std::cin >> c;
							std::cin.ignore();
						}
					}
					else if (tour_ai) { break; }
					*/
					

					/*
					choix_rangee = rand() % 7 + 1;
					curseur = choix_rangee;
					interface_de_console.affichageMegaUltime(connectF, curseur);

					choix_rangee--;
					break;
					*/
				}

				//4.3 Traiter l'egalite (break encore)
				if (connectF.getTokens() == 42) { break; }

				//4.4 Jouer tour
				if (!tour_ai) { drop = connectF.jouerTour(choix_rangee); }
				else if (tour_ai) {
					std::this_thread::sleep_for(std::chrono::seconds(1 + 1 / 2));
					drop = connectF.jouerTour(choix_rangee);
				}
				tour_ai = false;

				//4.5 Traiter le retour -1 donc si la colonne est pleine
				if (drop == -1) {
					std::cout << "Colonne pleine!\nEntrer un indice entre 1 et 7 : ";
				}

				//4.6 Refresh pour afficher le nouveau tableau si pas de victoire
				else {
					victoire = connectF.verificationMegaUltime(choix_rangee, drop);
					system("CLS");
					interface_de_console.affichageMegaUltime(connectF, curseur);
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
	}

	return 0;
}

void testFPGA(CommunicationFPGA port) {
	bool sortie=false;
	int valeur;
	int valBouton=0;
	for (int i = 0; i < 4; i++) {
		while (sortie!=true) {
			port.lireRegistre(nreg_lect_can0+i, valeur);
			port.ecrireRegistre(nreg_ecri_aff7sg0, valeur);
			port.lireRegistre(nreg_lect_stat_btn, valBouton);
			if (valBouton==17) {
				sortie = true;
				std::cout << "Entre dans le if" << std::endl;
			}
		}
		while (valBouton == 17) {
			port.lireRegistre(nreg_lect_stat_btn, valBouton);
		}
		valBouton = 0;	
		sortie = false;
	}
}