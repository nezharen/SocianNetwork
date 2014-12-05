/*
*
*MainWindow.cpp
*Author: Zhang Kai
*The main window.
*
*/

#include <QtGui>
#include <time.h>
#include "MainWindow.h"
#include "ShortestPathDialog.h"
#include "ShortestPath.h"
#include "ConnectedComponentDialog.h"
#include "ConnectedComponent.h"

MainWindow::MainWindow()
{
	createAction();
	createMenu();
	createGraph();
	shortestPathDialog = NULL;
	connectedComponentDialog = NULL;
	start = NULL;
	end = NULL;
	path = NULL;
	connectedComponentG = NULL;
	mode = new DisplayMode(MODE_ALL);
	setFixedSize(820, 660);
	setWindowTitle(tr("SocialNetwork"));
}

MainWindow::~MainWindow()
{
	if (shortestPathDialog != NULL)
		delete shortestPathDialog;
	if (connectedComponentDialog != NULL)
		delete connectedComponentDialog;
	if (start != NULL)
		delete start;
	if (end != NULL)
		delete end;
	if (path != NULL)
		delete [] path;
	if (connectedComponentG != NULL)
	{
		List *p, *q;
		for (int i = 0; i < connectedComponentG->n; i++)
		{
			p = connectedComponentG->head[i].next;
			while (p != NULL)
			{
				q = p->next;
				delete p;
				p = q;
			}
		}
		delete connectedComponentG;
	}
	
	deleteAction();
	deleteMenu();
	deleteGraph();
	delete mode;
}

void MainWindow::createAction()
{
	openAction = new QAction(tr("&Open"), this);
	openAction->setStatusTip(tr("Open a data file."));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

	exitAction = new QAction(tr("&Exit"), this);
	exitAction->setStatusTip(tr("Exit."));
	connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	shortestPathAction = new QAction(tr("&Shortest path"), this);
	shortestPathAction->setEnabled(false);
	shortestPathAction->setStatusTip(tr("Find shortest path."));
	connect(shortestPathAction, SIGNAL(triggered()), this, SLOT(showShortestPathDialog()));

	connectedComponentAction = new QAction(tr("&Connected component"), this);
	connectedComponentAction->setEnabled(false);
	connectedComponentAction->setStatusTip(tr("Find connected component."));
	connect(connectedComponentAction, SIGNAL(triggered()), this, SLOT(showConnectedComponentDialog()));

	aboutAction = new QAction(tr("&About SocialNetwork"), this);
	aboutAction->setStatusTip(tr("Show the program's about box."));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

	aboutQtAction = new QAction(tr("About Qt"), this);
	aboutQtAction->setStatusTip(tr("Show the Qt library's about box."));
	connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	statusBar();
}

void MainWindow::createMenu()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
	findMenu = menuBar()->addMenu(tr("&Find"));
	findMenu->addAction(shortestPathAction);
	findMenu->addAction(connectedComponentAction);
	aboutMenu = menuBar()->addMenu(tr("&About"));
	aboutMenu->addAction(aboutAction);
	aboutMenu->addAction(aboutQtAction);
}

void MainWindow::createGraph()
{
	qsrand(time(NULL));

	G = new Graph;
	G->n = G->m = 0;
	for (int i = 0; i < MAX_N; i++)
	{
		G->head[i].num = 0;
		G->head[i].next = NULL;
	}

	position = new QPoint[MAX_N];
}

void MainWindow::deleteAction()
{
	delete openAction;
	delete exitAction;
	delete shortestPathAction;
	delete connectedComponentAction;
	delete aboutAction;
	delete aboutQtAction;
}

void MainWindow::deleteMenu()
{
	delete fileMenu;
	delete findMenu;
	delete aboutMenu;
}

void MainWindow::deleteGraph()
{
	List *p, *q;

	for (int i = 0; i < G->n; i++)
	{
		p = G->head[i].next;
		while (p != NULL)
		{
			q = p->next;
			delete p;
			p = q;
		}
	}
	delete G;
	delete [] position;
}

void MainWindow::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Select a file"), ".", tr("Text files (*.txt)\n""All files (*.*)"));
	if (!fileName.isEmpty())
		loadFile(fileName);
}

void MainWindow::loadFile(const QString &fileName)
{
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(this, tr("SocialNetwork"), tr("Can not read file %1.").arg(file.fileName()));
		return;
	}

	List *p, *q;
	for (int i = 0; i < G->n; i++)
	{
		p = G->head[i].next;
		while (p != NULL)
		{
			q = p->next;
			delete p;
			p = q;
		}
	}

	for (int i = 0; i < G->n; i++)
	{
		G->head[i].num = 0;
		G->head[i].next = NULL;
	} // Initialization of the adjacency list.

	int x, y;
	double tmp;
	struct List * tmpList;
	QTextStream fin(&file);

	fin >> G->n >> G->m;

	for (int i = 0; i < G->n; i++)
	{
		position[i].setX(qrand() % 780 + 20);
		position[i].setY(qrand() % 580 + 40);
	}

	for (int i = 0; i < G->m; i++)
	{
		fin >> x >> y >> tmp;
		tmpList = new struct List;
		tmpList->des = y;
		tmpList->dis = tmp;
		tmpList->next = G->head[x].next;
		G->head[x].next = tmpList;
		G->head[x].num++;
		tmpList = new struct List;
		tmpList->des = x;
		tmpList->dis = tmp;
		tmpList->next = G->head[y].next;
		G->head[y].next = tmpList;
		G->head[y].num++;
	} // Build the adjacency list.

	(*mode) = MODE_ALL;
	setWindowTitle(file.fileName());
	if (G->n > 0)
	{
		shortestPathAction->setEnabled(true);
		connectedComponentAction->setEnabled(true);
	}
	update();
	QMessageBox::information(this, tr("SocialNetwork"), tr("File reading successful."));
}

void MainWindow::showShortestPathDialog()
{
	if (shortestPathDialog == NULL)
	{
		shortestPathDialog = new ShortestPathDialog;
		connect(shortestPathDialog, SIGNAL(findShortestPath(const int &, const int &)), this, SLOT(findShortestPath(const int &, const int &)));
		connect(shortestPathDialog, SIGNAL(showAll()), this, SLOT(showAll()));
	}

	shortestPathDialog->show();
	shortestPathDialog->raise();
	shortestPathDialog->activateWindow();
}

void MainWindow::findShortestPath(const int &startIndex, const int &endIndex)
{
	if ((startIndex < 0) || (startIndex >= G->n) || (endIndex < 0) || (endIndex >= G->n))
	{
		QMessageBox::warning(shortestPathDialog, tr("SocialNetwork"), tr("The number must be between 0 to %1").arg(G->n - 1));
		return;
	}

	if (start == NULL)
		start = new int;
	if (end == NULL)
		end = new int;
	if (path == NULL)
		path = new int [MAX_N];
	*start = startIndex;
	*end = endIndex;
	for (int i = 0; i < G->n; i++)
		path[i] = -1;
	ShortestPath(startIndex, path, (*G));
	(*mode) = MODE_SHORTEST_PATH;
	update();
}

void MainWindow::showConnectedComponentDialog()
{
	if (connectedComponentDialog == NULL)
	{
		connectedComponentDialog = new ConnectedComponentDialog;
		connect(connectedComponentDialog, SIGNAL(findConnectedComponent(const double &, const int &)), this, SLOT(findConnectedComponent(const double &, const int &)));
		connect(connectedComponentDialog, SIGNAL(showAll()), this, SLOT(showAll()));
	}

	connectedComponentDialog->show();
	connectedComponentDialog->raise();
	connectedComponentDialog->activateWindow();
}

void MainWindow::findConnectedComponent(const double &t, const int &mode)
{
	int k = 0;
	int connected[MAX_N];
	List *p, *q;

	if (connectedComponentG == NULL)
	{
		connectedComponentG = new Graph;
		connectedComponentG->n = connectedComponentG->m = 0;
		for (int i = 0; i < MAX_N; i++)
		{
			connectedComponentG->head[i].num = 0;
			connectedComponentG->head[i].next = NULL;
		}
	}

	for (int i = 0; i < connectedComponentG->n; i++)
	{
		p = connectedComponentG->head[i].next;
		while (p != NULL)
		{
			q = p->next;
			delete p;
			p = q;
		}
	}

	for (int i = 0; i < connectedComponentG->n; i++)
	{
		connectedComponentG->head[i].num = 0;
		connectedComponentG->head[i].next = NULL;
	}

	connectedComponentG->n = G->n;
	connectedComponentG->m = 0;

	for (int i = 0; i < G->n; i++)
		connected[i] = -1;
	
	for (int i = 0; i < G->n; i++)
		if (connected[i] < 0)
		{
			connected[i] = k;
			ConnectedComponent(*G, connected, t, mode, i, *connectedComponentG);
			k++;
		}
	*(this->mode) = MODE_CONNECTED_COMPONENT;
	update();
}

void MainWindow::showAll()
{
	(*mode) = MODE_ALL;
	update();
}

void MainWindow::showAbout()
{
	QMessageBox::about(this, tr("About SocialNetwork"), tr("<h2>SocialNetwork 1.0</h2>""<p>SocialNetwork is a program that makes data visiable.</p>"));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	QImage image(size(), QImage::Format_ARGB32_Premultiplied);
	QPainter imagePainter(&image);
	imagePainter.initFrom(this);
	imagePainter.setRenderHint(QPainter::Antialiasing, true);
	imagePainter.eraseRect(rect());
	draw(&imagePainter);
	imagePainter.end();

	QPainter windowPainter(this);
	windowPainter.drawImage(0, 0, image);
}

void MainWindow::draw(QPainter *painter)
{
	painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
	painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
	painter->drawRect(10, 30, 800, 600);
	painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));

	switch (*mode)
	{
	case MODE_ALL:
		for (int i = 0; i < G->n; i++)
			painter->drawEllipse(position[i], SIZE_POINT, SIZE_POINT);
		break;
	case MODE_SHORTEST_PATH:
		for (int i = (*end); ; )
		{
			if (path[i] == -1)
			{
				painter->drawEllipse(position[i], SIZE_POINT, SIZE_POINT);
				painter->drawText(position[i].x() + 1, position[i].y() - 3, QString::number(i));
				break;
			}
			painter->drawLine(position[i], position[path[i]]);
			painter->drawEllipse(position[i], SIZE_POINT, SIZE_POINT);
			painter->drawText(position[i].x() + 1, position[i].y() - 3, QString::number(i));
			i = path[i];
		}
		if (path[*end] == -1)
		{
			painter->drawEllipse(position[*start], SIZE_POINT, SIZE_POINT);
			painter->drawText(position[*start].x() + 1, position[*start].y() - 3, QString::number(*start));
		}
		break;
	case MODE_CONNECTED_COMPONENT:
		List *p;
		bool b[MAX_N];
		for (int i = 0; i < connectedComponentG->n; i++)
			b[i] = false;
		for (int i = 0; i < connectedComponentG->n; i++)
		{
			p = connectedComponentG->head[i].next;
			while (p != NULL)
			{	
				painter->drawLine(position[i], position[p->des]);
				b[i] = true;
				b[p->des] = true;
				p = p->next;
			}
		}
		for (int i = 0; i < connectedComponentG->n; i++)
			if (b[i])
				painter->drawEllipse(position[i], SIZE_POINT, SIZE_POINT);
		break;
	}
}
