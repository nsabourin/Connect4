#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QGraphicsPixmapItem>
#include <QDialog>

namespace Ui {
	class Gameplay;
}
class Gameplay :public QDialog, public QGraphicsPixmapItem {
	Q_OBJECT
public:
	//Constr et destr
	explicit Gameplay(QWidget* parent = nullptr, int = 2, int = 7);
	~Gameplay();

	int jeu;
private:
	Ui::Gameplay* ui;
	QGraphicsScene* scene;
	int dep;
	QWidget* daddy;
};
#endif // !GAMEPLAY_H
