/*
*
*ConnectedComponentDialog.h
*Author: Zhang Kai
*The dialog to count connected component.
*
*/

#ifndef CONNECTED_COMPONENT_DIALOG_H
#define CONNECTED_COMPONENT_DIALOG_H
#include <QDialog>

class QLabel;
class QLineEdit;
class QRadioButton;
class QGroupBox;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class ConnectedComponentDialog : public QDialog
{
	Q_OBJECT
public:
	ConnectedComponentDialog();
	~ConnectedComponentDialog();
signals:
	void findConnectedComponent(const double &t, const int &mode);
	void showAll();
protected slots:
	void showConnectedComponent();
protected:
	void closeEvent(QCloseEvent *event);
private:
	QLabel *tLabel;
	QLineEdit *tEdit;
	QRadioButton *modeRadio0, *modeRadio1, *modeRadio2;
	QGroupBox *modeGroup;
	QPushButton *findButton, *exitButton;
	QHBoxLayout *topLayout, *middleLayout, *bottomLayout;
	QVBoxLayout *radioLayout, *mainLayout;
};

#endif

