#include "mainWindow.hpp"
  
mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  QAction *quit = new QAction("&Quit", this);

  QMenu *file;
  file = menuBar()->addMenu("&File");
  file->addAction(quit);

  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void mainWindow::onKeyClick(QString nt)
{
  QTextStream out(stdout);
  out << "Button clicked:" << nt <<  endl;
}

void mainWindow::addKey(int left, QString nt) 
{
  key *t = new key(nt,this);
  QString s = nt.right(1);
  if(s=="#") {
    t->setGeometry(left, 30, 30, 80);
  } else {
    t->setGeometry(left, 30, 40, 160);
  }
  connect(t, SIGNAL(clicked()), this, SLOT(onKeyClick(nt)));
}
