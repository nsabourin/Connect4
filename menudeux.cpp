#include "menudeux.h"

menuAI::menuAI(QWidget* parent) : QWidget(parent)
{
	menu2Box = new QGridLayout(this);
	easy = new QPushButton("EASY",this);
	medium = new QPushButton("MEDIUM",this);
	hard = new QPushButton("HARD",this);
	back = new QPushButton("QUIT",this);

	easy->setFixedWidth(200);
	medium->setFixedWidth(200);
	hard->setFixedWidth(200);
	back->setFixedWidth(200);

	easy->setFixedHeight(50);
	medium->setFixedHeight(50);
	hard->setFixedHeight(50);
	back->setFixedHeight(50);
	
	menu2Box->addWidget(easy);
	menu2Box->addWidget(medium);
	menu2Box->addWidget(hard);
	menu2Box->addWidget(back);
	this->setLayout(menu2Box);
	this->hide();
	connect(back, SIGNAL(clicked()),this,SLOT(quit()));
}
void menuAI::keyPressEvent(QKeyEvent* event)
{

	if (event->key() == Qt::Key_Q)
	{
		exit(EXIT_SUCCESS);
	}
}
void menuAI::clicEasy()
{
	
}
void menuAI::clicMedium()
{

}

void menuAI::clicHard()
{

}

void menuAI::quit()
{
	exit(EXIT_SUCCESS);
}

