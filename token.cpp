#include "token.h"

/*Token::Token(QWidget* parent, int a, int c, Infos* info) :index(0), tour(0), positionY(5), jeu(a), dep(c), daddy(parent), totalMoves(1), info(info) {

    setPixmap(QPixmap(":/../twisTea.png"));
    setPos(135, 6.5);

    //tableau = new Tableau();

    if (jeu == 1) {
        info->setEtiquette1("Tour du Joueur 1");
        info->setEtiquette3("Pas de Minimax");
        info->setEtiquette4("Pas de AlphaBeta");
    }
    else if (jeu == 2) {
        info->setEtiquette1("Tour du Joueur");
        info->setEtiquette3("Pas de Minimax");
        info->setEtiquette4("Le nombre de deplacements pour AlphaBeta est : ");
        info->setEtiquette5(0);
    }
    else if (jeu == 3) {
        info->setEtiquette1("Player Move");
        info->setEtiquette3("Le nombre de mouvements pour minimax est : ");
        info->setEtiquette4("Le nombre de mouvements pour AlphaBeta est : ");
        info->setEtiquette2(0);
        info->setEtiquette5(0);
    }
}

void Token::actionClavier(QKeyEvent* actionTouche) {
    if (actionTouche->key() == Qt::Key_Escape) {
        menu = new Menu(0);
        menu->show();
        view->hide();
        info->hide();
    }
    if (actionTouche->key() == Qt::Key_Left && x() > 155) {
        index--;
        index = (index % 7 + 7) % 7;
        setPos(x() - 78.5, y());
    }
    else if (actionTouche->key() == Qt::Key_Left) {
        index--;
        index = (index % 7 + 7) % 7;
        setPos(x() + 78.5 * 6, y());
    }
    else if (actionTouche->key() == Qt::Key_Right && x() < 550) {
        index++;
        index = (index % 7 + 7) % 7;
        setPos(x() + 78.5, y());
    }
    else if (actionTouche->key() == Qt::Key_Right) {
        index++;
        index = (index % 7 + 7) % 7;
        setPos(x() - 78.5 * 6, y());
    }
    else if (actionTouche->key() == Qt::Key_Space) {

        //Pas d'AI
        ancienIndex = index;

        if (jeu == 1) {
            info->setEtiquette1("Deplacement j1");

            if (tour == 0) {
                //Actualiser tokens dans tableau
                info->setEtiquette1("Deplacement j1");
                positionY = tableau->deplacer(index, 1);

                if (positionY >= 0) {
                    //Fait tomber le token
                    JouerToken* token = new JouerToken(1, 5 - positionY);
                    token->setPos(x(), y());
                    //Actualiser scene
                    scene()->addItem(token);

                    if (tableau->verifVictoire() == 1) {
                        QMessageBox::critical(daddy, "Joueur 1 gagne", "Ici pour autre partie");
                        menu = new Menu(0);
                        menu->show();
                        view->hide();
                        info->hide();
                    }
                    passe = true;
                    info->setEtiquette1("Deplacement j2");
                }
            }

            else if (tour == 1) {
                info->setEtiquette1("Deplacement j2");
                //Actualiser tableau
                positionY = tableau->deplacer(index, 2);

                if (positionY >= 0) {

                    JouerToken* token = new JouerToken(0, 5 - positionY);
                    token->setPos(135 + index * 78.5, y());
                    //Actualiser scene
                    scene()->addItem(token);
                    view->update();
                    if (tableau->verifVictoire() == 2) {
                        QMessageBox::critical(daddy, "Joueur 1 gagne", "Rejouer cliquer");
                        menu = new Menu(0);
                        menu->show();
                        view->hide();
                        info->hide();
                    }
                    passe = true;
                    info->setEtiquette1("Deplacement j 1");
                }
            }
            if (tour == 1 && passe) {
                this->setPixmap(QPixmap(":/../twisTea.png"));
                this->setPos(135 + index * 78.5, y());
                tour = 0;
                passe = false;
            }
            else if (tour == 0 && passe)
            {
                this->setPixmap(QPixmap(":/../twisTea.png"));
                this->setPos(135 + index * 78.5, y());
                tour = 1;
                passe = false;
            }
        }

        //Avec AI
        else if (jeu == 2) {
            info->setEtiquette1("Deplacement AI");
            //Actualise tableauy
            positionY = tableau->deplacer(index, 1);

            if (positionY >= 0) {
                //Mm chose que sans AI
                JouerToken* token = new JouerToken(1, 5 - positionY);
                token->setPos(x(), y());
                scene()->addItem(token);
                if (tableau->verifVictoire() == 1)
                {
                    QMessageBox::critical(daddy, "Victoire humanite", "Rejouer");
                    menu = new Menu(0);
                    menu->show();
                    view->hide();
                    info->hide();
                }
            }
            if (totalMoves == 1) {
                positionY--;
                tableau->setCase(positionY, index);
                totalMoves++;
            }
            else {
                //index = IA().performMovealphabeta(*tableau, 2, dep, info);
                positionY = tableau->deplacer(index, 2);
            }


            if (positionY >= 0) {
                //MM chose ici encore
                JouerToken* token = new JouerToken(0, 5 - positionY);
                token->setPos(135 + index * 78.5, y());
                scene()->addItem(token);
                if (tableau->verifVictoire() == 2) {
                    QMessageBox::critical(daddy, "Les humains sont noob", "Rejouer");
                    menu = new Menu(0);
                    menu->show();
                    view->hide();
                    info->hide();
                }
            }
            index = ancienIndex;
        }

    }
}*/