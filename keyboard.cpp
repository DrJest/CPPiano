#include "keyboard.hpp"
#include "key.hpp"
#include <QRegExp>


keyBoard::keyBoard(QWidget *parent)
  : QWidget(parent)
{
}

Key* keyBoard::addKey(QString nt) 
{
  Key *t = new Key(nt,this);
  // nt must be formatted as: [a-g][1-7][#]{0,1}
  // so i trim the first 3 letters and use a regex
  nt = nt.left(3);
  if(!nt.contains(QRegExp("[a-g][1-7][#]{0,1}")) ) 
  {
    QTextStream out(stdout);
    out << "Error: " << nt << "is not a valid keynote\n";
    return t;
  }
  // duplicated notes? 
  if(this->isPresent(nt))
  {
    QTextStream out(stdout);
    out << "Error: " << nt << "is already present in this keyboard\n";
    return t;
  }
  QString s = nt.right(1);
  
  if(s=="#") 
    this->aKeys.push_back(t);
  else 
    this->cKeys.push_back(t);
  
  return t;
}

bool keyBoard::isPresent(QString note)
{
  for( int i = 0; i < this->cKeys.size(); ++i)
  {
    if ( note == this->cKeys.at(i)->getN() ) return true;
  }
  for( int i = 0; i < this->aKeys.size(); ++i)
  {
    if ( note == this->aKeys.at(i)->getN() ) return true;
  }
  return false;
}

keyBoard* keyBoard::draw() 
{
  int cLeft = 0;
  int aLeft = this->cKeyWidth - ( this->aKeyWidth / 2 );
  if(cKeys.at(0)->getN().left(1) == "b" || cKeys.at(0)->getN().left(1) == "e") aLeft += this->cKeyWidth;
  
  for( int i = 0; i < this->cKeys.size(); ++i)
  {
    this->cKeys.at(i)->setGeometry(cLeft, 0, this->cKeyWidth, this->cKeyHeight);
    cLeft += this->cKeyWidth;
  }
  for( int i = 0; i < this->aKeys.size(); ++i)
  {
    if(aKeys.at(i)->getN().left(1) == "c" || aKeys.at(i)->getN().left(1) == "f") aLeft += this->cKeyWidth;
    this->aKeys.at(i)->setGeometry(aLeft, 0, this->aKeyWidth, this->aKeyHeight);
    aLeft += this->cKeyWidth;
  }
  return this;
}

keyBoard* keyBoard::setCKeyHeight(int h)
{
  this->cKeyHeight =  h;
  return this;
}
keyBoard* keyBoard::setCKeyWidth(int w)
{
  this->cKeyWidth = w;
  return this;
}
keyBoard* keyBoard::setAKeyHeight(int h)
{
  this->cKeyHeight = h;
  return this;
}
keyBoard* keyBoard::setAKeyWidth(int w)
{
  this->cKeyWidth = w;
  return this;
}

keyBoard* keyBoard::setKeyGeometry(int ch, int cw, int ah, int aw)
{
  return this->setCKeyHeight(ch)->setCKeyWidth(cw)->setAKeyHeight(ah)->setAKeyWidth(aw);
}

int keyBoard::getWidth() 
{
  return this->cKeys.count() * this->cKeyWidth;
}

int keyBoard::getHeight() 
{
  return this->cKeyHeight;
}

void keyBoard::playNote(Key* note)
{
  
}
