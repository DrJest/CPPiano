#include "key.hpp"
#include "keyboard.hpp"
#include <QMap>
#include <QRegExp>
#include <unistd.h>

Key::Key()
{ 
}

Key::Key(QString name, QWidget *parent)
  : QPushButton(name, parent)
{
  // nt must be formatted as: [a-g][1-7][#]{0,1}
  // so i trim the first 3 letters and use a regex
  name = name.left(3);
  if(!name.contains(QRegExp("[a-g][0-7][#]{0,1}")) && name!="c8") 
  {
    QTextStream out(stdout);
    out << "Error: " << name << "is not a valid keynote\n";
    return;
  }
  
  this->_name = name;
  this->setGeometry(0,0,0,0);
  
  QString style;
  if(name.right(1)=="#") 
  {
    style = "background-color: black;color: white;";
    this->_sharp=true;
  } else {
    style = "background-color: white;color: black;";
  }
  this->_defaultStyle = style;
  this->setStyleSheet(style);
  this->_valid = true;
}

Key* Key::setFrequency(double f)
{
  this->_frequency = f;
  this->_aOutput = new AudioOutputStreamer(f, this);
  return this;
}

Key* Key::setDefaultStyle()
{
  this->setStyleSheet(this->_defaultStyle);
  return this;
}

void Key::play()
{
  this->setStyleSheet("background-color:red");
  this->_aOutput->start();
  this->_playing = true;
}

void Key::stop()
{
  this->setDefaultStyle();
  this->_aOutput->stop();
  this->_playing=false;
}

bool Key::valid()
{
  return this->_valid;
}

bool Key::sharp()
{
  return this->_sharp;
}

int Key::left()
{
  return this->_left;
}

Key* Key::setGeometry(int l, int t, int w, int h)
{
  this->_left=l;
  this->_top =t;
  this->_width=w;
  this->_height=h;
  QPushButton::setGeometry(l,t,w,h);
  return this;
}

QString Key::name()
{
  return this->_name;
}

double Key::frequency()
{
  return this->_frequency;
}

void Key::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    ((keyBoard*)(this->_parent))->playNote(this);
  } else {
    QPushButton::mousePressEvent(event);
  }
}

