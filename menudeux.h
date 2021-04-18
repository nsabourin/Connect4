#pragma once

#include<QApplication>
#include <QMainWindow>
#include <QPushButton>
#include "tableau.h"

class menuAI : public QWidget
{
	Q_OBJECT

public:
	explicit menuAI(QWidget* parent = nullptr);
private:
	QPushButton* easy;
	QPushButton* medium;
	QPushButton* hard;
	QPushButton* back;
	QGridLayout* menu2Box;
private slots:
	void clicEasy();
	void clicMedium();
	void clicHard();
	void quit();

};