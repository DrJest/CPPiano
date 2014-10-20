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
    QMenu *file; 
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


    QMenu *edit;
    QAction *defaults = new QAction("Default", this);
    QAction *complete = new QAction("Complete", this);
    edit = menuBar()->addMenu("&Modifica");

    QActionGroup* layouts = new QActionGroup(edit);
    layouts->addAction(defaults);
    layouts->addAction(complete);
    defaults->setChecked(true);

    edit->addAction(defaults);
    edit->addAction(complete);
    
    //connect(item1, SIGNAL(triggered()), someobject, (SLOT(item1slot()));
    //connect(item2, SIGNAL(triggered()), someobject, (SLOT(item2slot()));
    //connect(item3, SIGNAL(triggered()), someobject, (SLOT(item3slot()));

    
    return this;
}

mainWindowMenu* mainWindow::addMenu(QString label){
  mainWindowMenu* m = new mainWindowMenu();
  if(label != "")
    this->menus.push_back(*m);
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
  if ( !this->menus.count() ) this->defaultMenus();
    for (int i = 0; i < this->menus.size(); ++i) {
        mainWindowMenu menu = this->menus.at(i);
        QMenu* m;
        m = menuBar()->addMenu(menu.label);
        for (int j = 0; j < menu.items.size(); ++j) {
          mainWindowMenuItem item = menu.items.at(j);
          QAction* a = new QAction(item.label, this);
          if(item.shortcut) 
            a->setShortcut(item.shortcut);
          m->addAction(a);
        }
    }  
  QMainWindow::setCentralWidget(this->mainWidget);
  return this;
}

QWidget* mainWindow::getMainWidget()
{
  return this->mainWidget;
}
