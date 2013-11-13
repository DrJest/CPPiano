#include "key.hpp"
#include "keyboard.hpp"
#include <QMap>
#include <QRegExp>

Key::Key(QString name, QWidget *parent)
  : QPushButton(name, parent)
{
  // nt must be formatted as: [a-g][1-7][#]{0,1}
  // so i trim the first 3 letters and use a regex
  name = name.left(3);
  if(!name.contains(QRegExp("[a-g][1-7][#]{0,1}")) ) 
  {
    QTextStream out(stdout);
    out << "Error: " << name << "is not a valid keynote\n";
    return;
  }
  
  this->_name = name;
  this->setGeometry(0,0,0,0);
  
  if(name.right(1)=="#") 
  {
    this->setStyleSheet("background-color: black;color: white;");
    this->_sharp=true;
  } else {
    this->setStyleSheet("background-color: white;color: black;");
  }
  this->_valid = true;
}

Key* Key::setFrequency(double f)
{
  this->_frequency = f;
  return this;
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

/*
Key* Key::assignKey(int keyCode)
{
  this->_keyCode = keyCode;
  QMap<QString, QString> layout;
   layout["a"] = "a"; //LA4
   layout["w"] = "a#";
   layout["s"] = "b";
   layout["d"] = "c";
   layout["r"] = "c#";
   layout["f"] = "d";
   layout["t"] = "d#";
   layout["g"] = "e";
   layout["h"] = "f";
   layout["u"] = "f#";
   layout["j"] = "g";
   layout["i"] = "g#";
   layout["k"] = "a";
   layout["o"] = "a#";
   layout["l"] = "b";
   layout["p"] = "c";
  
  //double f;
  //QString l;
  QVector<QString> notes{"a4","a4#","b4","c5","c5#","d5","d5#","e5","f5","f5#","g5","g5#","a5","a5#","b5","c6"};
  //FU**ING QMAP/STDMAP that makes no index access to their key/value pair
  //also, too lazy to extend qmap with this feature
  //so I use another vector to pass from index to key before access QMap
  QVector<QString> keys{"a","w","s","d","r","f","t","g","h","u","j","i","k","o","l","p"};
  //n.set(
  return this;
}
*/

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

