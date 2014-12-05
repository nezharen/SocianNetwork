/*
*
*ShortestPathDialog.h
*Author: Zhang Kai
*The dialog to count shortest path.
*
*/

#ifndef SHORTEST_PATH_DIALOG_H
#define SHORTEST_PATH_DIALOG_H
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class ShortestPathDialog : public QDialog
{
	Q_OBJECT
public:
	ShortestPathDialog();
	~ShortestPathDialog();
signals:
	void findShortestPath(const int &startIndex, const int &endIndex);
	void showAll();
protected:
	void closeEvent(QCloseEvent *event);
protected slots:
	void showShortestPath();
private:
	QLabel *startLabel, *endLabel;
	QLineEdit *startEdit, *endEdit;
	QPushButton *findButton, *exitButton;
	QHBoxLayout *topLayout, *bottomLayout;
	QVBoxLayout *leftLayout, *rightLayout, *mainLayout;
};

#endif

