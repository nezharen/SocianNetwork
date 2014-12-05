/*
*
*ShortestPathDialog.cpp
*Author: Zhang Kai
*The dialog to count shortest path.
*
*/

#include <QtGui>
#include "ShortestPathDialog.h"

ShortestPathDialog::ShortestPathDialog()
{
	startLabel = new QLabel(tr("&Start index:"));
	startEdit = new QLineEdit;
	startEdit->setAlignment(Qt::AlignHCenter);
	startLabel->setBuddy(startEdit);

	endLabel = new QLabel(tr("&End index:"));
	endEdit = new QLineEdit;
	endEdit->setAlignment(Qt::AlignHCenter);
	endLabel->setBuddy(endEdit);

	findButton = new QPushButton(tr("&Find"));
	findButton->setDefault(true);
	exitButton = new QPushButton(tr("&Exit"));

	connect(findButton, SIGNAL(clicked()), this, SLOT(showShortestPath()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

	leftLayout = new QVBoxLayout;
	leftLayout->addWidget(startLabel);
	leftLayout->addWidget(endLabel);

	rightLayout = new QVBoxLayout;
	rightLayout->addWidget(startEdit);
	rightLayout->addWidget(endEdit);

	topLayout = new QHBoxLayout;
	topLayout->addLayout(leftLayout);
	topLayout->addLayout(rightLayout);

	bottomLayout = new QHBoxLayout;
	bottomLayout->addWidget(findButton);
	bottomLayout->addStretch();
	bottomLayout->addWidget(exitButton);

	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);
	setWindowTitle(tr("Shortest path"));
	setFixedSize(sizeHint());
}

ShortestPathDialog::~ShortestPathDialog()
{
	delete startLabel;
	delete startEdit;
	delete endLabel;
	delete endEdit;
	delete findButton;
	delete exitButton;
	delete leftLayout;
	delete rightLayout;
	delete topLayout;
	delete bottomLayout;
	delete mainLayout;
}

void ShortestPathDialog::showShortestPath()
{
	emit findShortestPath(startEdit->text().toInt(), endEdit->text().toInt());
}

void ShortestPathDialog::closeEvent(QCloseEvent *event)
{
	emit showAll();
}

