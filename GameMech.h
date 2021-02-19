
#ifndef GAMEMECH_H_EXISTS
#define GAMEMECH_H_EXISTS

class GameMech
{
public:
	GameMech(int, int);
	~GameMech();
	char getValueAt(int ligne, int colonne);
	

	int getTokens();
	int getTurn();
	int getMaxLigne();
	int getMaxColonne();

	int	jouerTour(int);
	bool verificationMegaUltime(int, int);

private:
	char tableau[6][7];
	int max_ligne;
	int max_colonne;
	int	tokens ;
	bool victoire;
	int turn;
	char JOUEUR1 = 254;
	char JOUEUR2 = 15;
	char EMPTY = ' ';

};

#endif




