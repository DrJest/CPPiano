/**
 * key.cpp
 * 
 * crea i tasti della tastiera, gli associa un nome e una frequenza 
 * 
 * **/ 


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
  // Uso le regex per accettare solo le note 
  name = name.left(3);
  this->_parent = parent;
  if(!name.contains(QRegExp("[a-g][0-7][#]{0,1}")) && name!="c8") 
  {
    QTextStream out(stdout);
    out << "Error: " << name << "is not a valid keynote\n";
    return;
  }
  
  //do il nome alla nota e ne setto la posizione nella finestra
  this->_name = name;
  this->setGeometry(0,0,0,0);
  
  //Setta lo stile Default in funzione delle alterazioni
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

//Setta la frequenza.
//Crea un nuovo AudioOutputStreamer con frequenza f e con le variabili di questa key.
Key* Key::setFrequency(double f)
{
  this->_frequency = f;
  this->_aOutput = new AudioOutputStreamer(f, this);
  return this;
}

keyBoard* Key::parent()
{
  return (keyBoard*) this->_parent;
}

//Setta lo stile
Key* Key::setDefaultStyle()
{
  this->setStyleSheet(this->_defaultStyle);
  return this;
}

//Quando suono do start a AudioOutputStreamer e coloro in rosso
void Key::play()
{
  this->setStyleSheet("background-color:red");
  this->_aOutput->start();
  this->_playing = true;
}

//Quando smetto di suonare, stoppo AudioOutputStreamer e risetto lo stile
void Key::stop()
{
  this->setDefaultStyle();
  this->_aOutput->stop();
  this->_playing=false;
}

//Ritorna la validita della nota
bool Key::valid()
{
  return this->_valid;
}

//Ritorna l'alterazione della nota
bool Key::sharp()
{
  return this->_sharp;
}

//Restituisce la larghezza
int Key::left()
{
  return this->_left;
}

//Setta le dimensioni e le coordinate spaziali e posiziona il bottone associato alla nota.
Key* Key::setGeometry(int l, int t, int w, int h)
{
  this->_left=l;
  this->_top =t;
  this->_width=w;
  this->_height=h;
  QPushButton::setGeometry(l,t,w,h);
  return this;
}

//restituisce il nome
QString Key::name()
{
  return this->_name;
}

//restituisce la frequenza
double Key::frequency()
{
  return this->_frequency;
}

//Fa suonare la nota alla pressione col mouse. playNote appartiene a keyBoard
void Key::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    ((keyBoard*)(this->_parent))->playNote(this);
  } else {
    QPushButton::mousePressEvent(event);
  }
}
