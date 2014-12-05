/*
*
*ConnectedComponentDialog.cpp
*Author: Zhang Kai
*The dialog to count connected component.
*
*/

#include <QtGui>
#include "ConnectedComponentDialog.h"

ConnectedComponentDialog::ConnectedComponentDialog()
{
	tLabel = new QLabel(tr("&Threshold:"));
	tEdit = new QLineEdit;
	tEdit->setAlignment(Qt::AlignHCenter);
	tLabel->setBuddy(tEdit);

	modeRadio0 = new QRadioButton(tr("Compare the &integer parts only."));
	modeRadio1 = new QRadioButton(tr("Compare the &fractional parts only."));
	modeRadio2 = new QRadioButton(tr("Compare &both."));
	modeRadio2->setChecked(true);
	modeGroup = new QGroupBox(tr("Mode"));

	findButton = new QPushButton(tr("&Find"));
	findButton->setDefault(true);
	exitButton = new QPushButton(tr("&Exit"));

	connect(findButton, SIGNAL(clicked()), this, SLOT(showConnectedComponent()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

	topLayout = new QHBoxLayout;
	topLayout->addWidget(tLabel);
	topLayout->addWidget(tEdit);

	radioLayout = new QVBoxLayout;
	radioLayout->addWidget(modeRadio0);
	radioLayout->addWidget(modeRadio1);
	radioLayout->addWidget(modeRadio2);
	modeGroup->setLayout(radioLayout);
	middleLayout = new QHBoxLayout;
	middleLayout->addWidget(modeGroup);

	bottomLayout = new QHBoxLayout;
	bottomLayout->addWidget(findButton);
	bottomLayout->addStretch();
	bottomLayout->addWidget(exitButton);

	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(middleLayout);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);
	setWindowTitle(tr("Connected component"));
	setFixedSize(sizeHint());
}

ConnectedComponentDialog::~ConnectedComponentDialog()
{
	delete tLabel;
	delete tEdit;
	delete modeRadio0;
	delete modeRadio1;
	delete modeRadio2;
	delete findButton;
	delete exitButton;
	delete topLayout;
	delete radioLayout;
	delete bottomLayout;
	delete modeGroup;
	delete middleLayout;
	delete mainLayout;
}

void ConnectedComponentDialog::showConnectedComponent()
{
	if (modeRadio0->isChecked())
		emit findConnectedComponent(tEdit->text().toDouble(), 0);
	if (modeRadio1->isChecked())
		emit findConnectedComponent(tEdit->text().toDouble(), 1);
	if (modeRadio2->isChecked())
		emit findConnectedComponent(tEdit->text().toDouble(), 2);
}

void ConnectedComponentDialog::closeEvent(QCloseEvent *event)
{
	emit showAll();
}

