/**
*
* mainWindow.hpp
*
* Instanzia e disegna la finestra
*
***/ 

#include "mainWindow.hpp"
#include <QActionGroup>
#include <QMessageBox>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qApp->setStyleSheet("QPushButton:focus {outline: none}");
}


void mainWindow::closeEvent ( QCloseEvent * event )
{  
    if(((keyBoard*)getMainWidget())->_rec->unsaved()) {
        event->ignore();        
        if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation?",
                              "Are you sure you want to exit?", 
                              QMessageBox::Yes|QMessageBox::No))
        {
            event->accept();
            qApp->quit();
        }
    }
}; 

//  Disegna l'opzione quit nella finestra, nella finestrella file
mainWindow* mainWindow::defaultMenus()
{
    options* opt = new options(this);
    RecPlay * _rec = ((keyBoard*)getMainWidget())->_rec;
    QTextStream out(stdout);

    QMenu* file = menuBar()->addMenu("&File");

    QAction *open = new QAction("&Open", file);
    open->setShortcut(Qt::Key_O | Qt::CTRL);
    file->addAction(open);
    connect(open, SIGNAL(triggered()), _rec, SLOT(Open())); 

    QAction *save = new QAction("&Save", file);
    save->setShortcut(Qt::Key_S | Qt::CTRL);
    file->addAction(save);
    connect(save, SIGNAL(triggered()), _rec, SLOT(Save())); 

    QAction* saveas = new QAction("Save &As", file);
    saveas->setShortcut(Qt::Key_S | Qt::CTRL | Qt::ShiftModifier);
    file->addAction(saveas);
    connect(saveas, SIGNAL(triggered()), _rec, SLOT(SaveAs())); 


    QAction *quit = new QAction("&Quit", file);
    quit->setShortcut(Qt::Key_Q | Qt::CTRL);
    file->addAction(quit);
    connect(quit, SIGNAL(triggered()), this, SLOT(close())); 
    
    QMenu *edit = menuBar()->addMenu("&Edit");

    QAction *UpOct = new QAction("Octave &Up", edit);
    QAction *DownOct = new QAction("Octave &Down", edit);

    edit->addAction(UpOct); 
    edit->addAction(DownOct); 
    connect(UpOct, SIGNAL(triggered()), this->mainWidget, SLOT(chOctEventUp()));
    connect(DownOct, SIGNAL(triggered()), this->mainWidget, SLOT(chOctEventDown()));
    
    QAction *octaveSep = new QAction(edit);
    octaveSep->setSeparator(true);
    edit->addAction(octaveSep);

    QAction *optLabel = new QAction("&Preferences", this);
    optLabel->setShortcut(Qt::Key_P | Qt::CTRL);
    edit->addAction(optLabel);
    connect(optLabel, SIGNAL(triggered()), opt, SLOT(spawnOptionsWindow()));

    QMenu* rec = menuBar()->addMenu("&Rec");
    QAction* startRec = new QAction("Start Recording",rec);
    QAction* stopRec = new QAction("Stop Recording",rec);
    startRec->setShortcut(Qt::Key_R | Qt::CTRL);
    stopRec->setShortcut(Qt::Key_R | Qt::ShiftModifier);
    rec->addAction(startRec);
    rec->addAction(stopRec);
    connect(startRec, SIGNAL(triggered()), _rec, SLOT(startRec()));
    connect(stopRec, SIGNAL(triggered()), _rec, SLOT(stopRec()));

    QAction* pause = new QAction("Pause", rec);
    rec->addAction(pause);
    connect(pause, SIGNAL(triggered()), _rec, SLOT(Pause()));
    
    QAction* start = new QAction("Play",rec);
    QAction* stop = new QAction("Stop",rec);
    stop->setShortcut(Qt::Key_Period | Qt::CTRL);
    rec->addAction(start);
    rec->addAction(stop);
    connect(start, SIGNAL(triggered()), _rec, SLOT(Play()));
    connect(stop, SIGNAL(triggered()), _rec, SLOT(Stop()));

    QAction* clear = new QAction("Clear",rec);
    clear->setShortcut(Qt::Key_C | Qt::CTRL);
    rec->addAction(clear);
    connect(clear, SIGNAL(triggered()), _rec, SLOT(Clear()));

    _rec->setButtons(startRec,stopRec,pause,start,stop);

    start->setEnabled(false);
    stop->setEnabled(false);
    pause->setEnabled(false);
    stopRec->setEnabled(false);

    return this;
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
