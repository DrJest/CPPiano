#include "keyboard.hpp"
#include "key.hpp"
#include <QString>

keyBoard::keyBoard(QWidget *parent)
  : QWidget(parent)
{
}

void keyBoard::addKey(int left, QString nt) 
{
  Key *t = new Key(nt,this);
  QString s = nt.right(1);
  if(s=="#") {
    t->setGeometry(left, 30, 30, 80);
  } else {
    t->setGeometry(left, 30, 40, 160);
  }
  //connect(t, SIGNAL(disPressed()), this, SLOT(onKeyClick(note)));
}

