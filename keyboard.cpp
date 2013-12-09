#include <QAudio>
#include <QAudioOutput>
#include "key.hpp"
#include "keyboard.hpp"

keyBoard::keyBoard(QWidget *parent)
  : QWidget(parent)
{
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
keyBoard* keyBoard::updateTopBar()
{
  this->_topBar->setText( "   Current Octave: "+QString::number(this->_curOctave)+" (Min: "+QString::number(this->_minOctave)+"; Max:"+QString::number(this->_maxOctave)+")" );
  return this;  
}

int keyBoard::width() 
{
  return this->cNotes.count() * this->cKeyWidth;
}
int keyBoard::height() 
{
  return this->cKeyHeight+30;
}

void keyBoard::playNote(Key* note)
{
    note->setStyleSheet("background-color:red");
    note->play();
    QTextStream out(stdout);
    out << note->name() << " ";
}

void keyBoard::stopNote(Key* note)
{
  note->setDefaultStyle();
  note->stop();
}

keyBoard* keyBoard::generate(int minO, int maxO, QString genN, double genF)
{
  genN = genN.left(3);
  if(!genN.contains(QRegExp("[a-g][1-8][#]{0,1}")) ) 
  {
    return this;
  }
  this->_generatorNote = genN;
  this->_generatorFreq = genF;
  this->_curOctave = genN.mid(1,1).toInt();
  this->_minOctave = minO;
  this->_maxOctave = maxO;
  this->_generated = true;
  
  QString h = "";
  if(genN.right(1)=="#") h="#";
  QString startN = genN.left(1) + h;

  QString notes="cdefgab";
  
  QVector<QString> allNotes;
  QString tmp;
  
  for (int i = 5; i<7; ++i)
  {
    tmp = notes.at(i)+QString::number(minO-1);
    allNotes.push_back(tmp);
    if(tmp.left(1)!="b"&&tmp.left(1)!="e") {
      tmp += "#";
      allNotes.push_back(tmp);
    }
  }
  for(int i = minO; i<=maxO; ++i)
  {
    for(int j = 0; j <7; j++)
    {
      tmp = notes.at(j)+QString::number(i);
      allNotes.push_back(tmp);
      if(tmp.left(1)!="b"&&tmp.left(1)!="e") {
        allNotes.push_back(tmp+"#");
      }
    }
  }
  allNotes.push_back( "c"+QString::number(maxO+1) );
  int n = allNotes.indexOf(genN);
  double f, a = 1.05946309436;
  for(int i = 0; i<allNotes.size();++i) 
  {
    f = genF * pow(a, (i-n));
    // cant draw buttons now, it will caused sovrapposition of cNotes on aNotes
    // notes are sorteb by frequency, because it is always crescent(?)
    (allNotes.at(i).right(1)=="#") ? this->aNotes[f]=allNotes.at(i) : this->cNotes[f]=allNotes.at(i); 
  }
  return this;
}

keyBoard* keyBoard::draw() 
{
  if( this->_generated == false ) {
    this->generate(4, 4);
  }

  int left = 0;  
    for( auto i : this->cNotes.keys() )
    {
      Key* t = new Key(cNotes.value(i), this);
      this->_keys.push_back(t);
      t->setGeometry(left, 20, this->cKeyWidth, this->cKeyHeight)->setFrequency( i );
      left += this->cKeyWidth;
    }
    left = this->cKeyWidth - ( this->aKeyWidth / 2 );
    for( auto j : this->aNotes.keys() )
    {
      if(aNotes.value(j).left(1) == "c" || aNotes.value(j).left(1) == "f") left += this->cKeyWidth;
      Key* t = new Key(aNotes.value(j), this);
      this->_keys.push_back(t);
      t->setGeometry(left, 20, this->aKeyWidth, this->aKeyHeight)->setFrequency( j );
      left += this->cKeyWidth;
    }
    QLabel* fb = new QLabel(this);
    this->_topBar = fb;
    this->updateTopBar();
  return this;
}

Key* keyBoard::getNoteByKeyCode(int keyCode)
{
  if(this->_layout=="base")
  {
    int cur = this->_curOctave;
    
    QVector<int> code{ 65, 87, 83, 68, 82, 70, 84, 71, 72, 85, 74, 73, 75, 79, 76, 80};
    QVector<QString> K{"a$p","a$p#","b$p","c$c","c$c#","d$c","d$c#","e$c","f$c","f$c#","g$c","g$c#","a$c","a$c#","b$c","c$n"};
    if(code.indexOf(keyCode)==-1) return (new Key());
    
    int index = code.indexOf(keyCode);
    QString note = K.at(index);
    
    note = note.replace("$c",QString::number(cur)).replace("$p",QString::number(cur-1)).replace("$n",QString::number(cur+1));

    for (int i= 0; i< this->_keys.size(); ++i)
    {
      if(note==this->_keys.at(i)->name()) { return this->_keys.at(i); }
    }
  }
  return (new Key());
}

void keyBoard::keyPressEvent(QKeyEvent *event)
{
  QTextStream out(stdout);
  int KC = event->key();
  if(KC==Qt::Key_Control)
  {
    _curOctave = _curOctave-1;
    if(_curOctave<_minOctave) _curOctave = _minOctave;
    this->updateTopBar();
    return;
  }
  
  if(KC==Qt::Key_Shift)
  {
    this->_curOctave = _curOctave+1;
    if(_curOctave>_maxOctave) _curOctave = _maxOctave;
    this->updateTopBar();
    return;
  }
  Key* t = this->getNoteByKeyCode(KC);
  if(t->valid()) playNote(t);
}
 
void keyBoard::keyReleaseEvent(QKeyEvent *event)
{
  Key* t = this->getNoteByKeyCode(event->key());
  if(t->valid()) stopNote(t);
  return;
}
