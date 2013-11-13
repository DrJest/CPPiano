#include "mainWindow.hpp"
#include "keyboard.hpp"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

// draws default file->quit menu
mainWindow* mainWindow::defaultMenus()
{
    QAction *quit = new QAction("&Quit", this);
    quit->setShortcut(Qt::Key_Q | Qt::CTRL);
    QMenu *file; 
    file = menuBar()->addMenu("&File");
    file->addAction(quit);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));    
    return this;
}

// this adds both menus and toolbars !
mainWindowMenu* mainWindow::addMenu(QString label){
  mainWindowMenu* m = new mainWindowMenu();
  // Toolbars don't need label, so we gonna call it with NO args
  // if we want a toolbar, with a QString if we want a menu
  // NOTE: menus and toolbars are actually instantied in this->draw();
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
