#include "mainWindow.hpp"
#include "keyboard.hpp"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

QWidget* mainWindow::setMainWidget(QWidget* w) 
{
  this->mainWidget = w;
  return w;
}

bool mainWindow::disableDefaultMenus()
{
  return this->defaultMenusDisabled = true;
}


mainWindow* mainWindow::draw() 
{
  if (!this->defaultMenusDisabled)
  {
    QAction *quit = new QAction("&Quit", this);
    quit->setShortcut(Qt::Key_Q | Qt::CTRL);

    QMenu *file; //, *edit;
    file = menuBar()->addMenu("&File");
    //edit = menuBar()->addMenu("&Modifica");
    file->addAction(quit);

    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
  }
  /*QMenu* file;
  vector = this->menus;
  for (int i = 0; i < vector.size(); ++i) {
    file = vector.at(i);
    //file = 
  }*/
  QMainWindow::setCentralWidget(this->mainWidget);
  return this;
}

QWidget* mainWindow::getMainWidget()
{
  return this->mainWidget;
}

void mainWindow::keyPressEvent(QKeyEvent *event)
{
  QVector<int> code{ 65, 87, 83, 68, 82, 70, 84, 71, 72, 85, 74, 73, 75, 79, 76, 80};
  
  QTextStream out(stdout);
  out << event->key() << "\n";
}
 
void mainWindow::keyReleaseEvent(QKeyEvent *event)
{
  QTextStream out(stdout);
  out << event->key() << "\n";
}
