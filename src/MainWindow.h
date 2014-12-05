/*
*
*MainWindow.h
*Author: Zhang Kai
*The main window.
*
*/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "Graph.h"
#define SIZE_POINT 3

class QAction;
class QMenu;
class QString;
class QPoint;
class ShortestPathDialog;
class ConnectedComponentDialog;

typedef enum {MODE_ALL, MODE_SHORTEST_PATH, MODE_CONNECTED_COMPONENT} DisplayMode;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
protected slots:
	void openFile();
	void showShortestPathDialog();
	void showConnectedComponentDialog();
	void findShortestPath(const int &startIndex, const int &endIndex);
	void findConnectedComponent(const double &t, const int &mode);
	void showAll();
	void showAbout();
protected:
	void createAction();
	void createMenu();
	void createGraph();
	void deleteAction();
	void deleteMenu();
	void deleteGraph();
	void loadFile(const QString &fileName);
	void paintEvent(QPaintEvent *event);
	void draw(QPainter *painter);
private:
	QMenu *fileMenu, *findMenu, *aboutMenu;
	QAction *openAction, *exitAction, *shortestPathAction, *connectedComponentAction, *aboutAction, *aboutQtAction;
	Graph *G, *connectedComponentG;
	QPoint *position;
	ShortestPathDialog *shortestPathDialog;
	ConnectedComponentDialog *connectedComponentDialog;
	int *start, *end;
	int *path;
	DisplayMode *mode;
};

#endif

