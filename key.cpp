#include "key.hpp"

key::key(QString name, QWidget *parent)
  : QPushButton(name, parent)
{
  this->name = name;
  this->assign(name);
}

void key::assign(QString name)
{
  note * n = new note();
  n->setNote(name);
  this->n = *n;
}

QString key::getN(){
  return this->name;
}
