/**
*
* mainWindow.hpp
*
* Instanzia e disegna la finestra
*
***/ 

#include "mainWindow.hpp"
#include "options.hpp"
#include <QActionGroup>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

//  Disegna l'opzione quit nella finestra, nella finestrella file
mainWindow* mainWindow::defaultMenus()
{
    QMenu *file;
    options* opt = new options(this);

    QAction *UpOct = new QAction("Octave &Up", this);
    QAction *DownOct = new QAction("Octave &Down", this);
    QAction *quit = new QAction("&Quit", this);
    quit->setShortcut(Qt::Key_Q | Qt::CTRL);
    file = menuBar()->addMenu("&File");

    file->addAction(UpOct); 
    file->addAction(DownOct); 
    file->addAction(quit);
    
    connect(UpOct, SIGNAL(triggered()), this->mainWidget, SLOT(chOctEventUp()));
    connect(DownOct, SIGNAL(triggered()), this->mainWidget, SLOT(chOctEventDown()));
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit())); 

    QMenu *edit = menuBar()->addMenu("&Modifica");

    QAction *optLabel = new QAction("&Preferenze", this);
    optLabel->setShortcut(Qt::Key_P | Qt::CTRL);
    edit->addAction(optLabel);
    connect(optLabel, SIGNAL(triggered()), opt, SLOT(spawnOptionsWindow()));
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
