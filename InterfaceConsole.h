#include <iostream>
#include "GameMech.h"

class interfaceConsole {
public:
	void affichageMegaUltime(GameMech& game) {
		//Print les indices
		std::cout << " 1   2   3   4   5   6   7\n";

		//Boucle le tableau (j, k et l sont les colonnes)
		for (int i = 0; i < game.getMaxLigne(); i++) {
			for (int j = 0; j < game.getMaxColonne(); j++) {
				std::cout << char(218) << char(196) << char(191) << " ";
			}
			std::cout << std::endl;

			for (int k = 0; k < game.getMaxColonne(); k++) {
				std::cout << char(179) << game.getValueAt(i,k) << char(179) << " ";
			}
			std::cout << std::endl;

			for (int l = 0; l < game.getMaxColonne(); l++) {
				std::cout << char(192) << char(196) << char(217) << " ";
			}
			std::cout << std::endl;
		}
	}
};