#ifndef INFOS_H
#define INFOS_H

#include <QDialog>

//Garder mm namespace que autre fenetre
//pour display les infos
//----------namespace ui pour Infos

class Infos : public QDialog {
	Q_OBJECT
public:
	//Constr et destr
	explicit Infos(QWidget* parent = nullptr);
	~Infos();

	//Setters
	void setEtiquette1(QString = "");
	void setEtiquette2(int);
	void setEtiquette3(QString = "");
	void setEtiquette4(QString = "");
	void setEtiquette5(int);

private:
	//Ui::Infos* ui;
};
#endif