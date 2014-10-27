/**
*
* mainWindow.hpp
*
* Instanzia e disegna la finestra
*
***/ 

#include "mainWindow.hpp"
#include <QActionGroup>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

//  Disegna l'opzione quit nella finestra, nella finestrella file
mainWindow* mainWindow::defaultMenus()
{
    options* opt = new options(this);
    RecPlay * _rec = ((keyBoard*)getMainWidget())->_rec;

    QTextStream out(stdout);
    out << _rec;

    QMenu* file = menuBar()->addMenu("&File");
    QAction *quit = new QAction("&Quit", file);
    quit->setShortcut(Qt::Key_Q | Qt::CTRL);
    file->addAction(quit);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit())); 
    
    QMenu *edit = menuBar()->addMenu("&Edit");
    QAction *optLabel = new QAction("&Preferences", this);
    optLabel->setShortcut(Qt::Key_P | Qt::CTRL);
    edit->addAction(optLabel);
    connect(optLabel, SIGNAL(triggered()), opt, SLOT(spawnOptionsWindow()));

    QMenu* octave = menuBar()->addMenu("&Octave");
    QAction *UpOct = new QAction("Octave &Up", octave);
    QAction *DownOct = new QAction("Octave &Down", octave);
    octave->addAction(UpOct); 
    octave->addAction(DownOct); 
    connect(UpOct, SIGNAL(triggered()), this->mainWidget, SLOT(chOctEventUp()));
    connect(DownOct, SIGNAL(triggered()), this->mainWidget, SLOT(chOctEventDown()));

    QMenu* rec = menuBar()->addMenu("&Rec");
    QAction* startRec = new QAction("Star&t",rec);
    QAction* stopRec = new QAction("Sto&p",rec);
    rec->addAction(startRec);
    rec->addAction(stopRec);
    connect(startRec, SIGNAL(triggered()), _rec, SLOT(startRec()));
    connect(stopRec, SIGNAL(triggered()), _rec, SLOT(stopRec()));

    return this;
}

QMenu* mainWindow::addMenu(QString label)
{
  QMenu* m = menuBar()->addMenu(label);
  return m;
}
 
int mainWindow::getMenus()
{
  return this->menus.size();
}

int mainWindow::getToolbars()
{
  return this->tbars.size();
}

mainWindow* mainWindow::draw() 
{
  this->defaultMenus();
  QMainWindow::setCentralWidget(this->mainWidget);
  return this;
}

QWidget* mainWindow::getMainWidget()
{
  return this->mainWidget;
}
