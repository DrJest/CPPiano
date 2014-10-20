/**
 *  keyboard.cpp
 * 
 *  Disegna la tastiera
 * 
 * */

#include <QAudio>
#include <QAudioOutput>
#include <QDesktopWidget>
#include "key.hpp"
#include "keyboard.hpp"

//Crea keyboard usando un QWidget (ossia mainwindow)
keyBoard::keyBoard(QWidget *parent)
  : QWidget(parent)
{
}
//Setta le dimensioni dei tasti alterati e puliti
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

//Setta la geometria
keyBoard* keyBoard::setKeyGeometry(int ch, int cw, int ah, int aw)
{
  return this->setCKeyHeight(ch)->setCKeyWidth(cw)->setAKeyHeight(ah)->setAKeyWidth(aw);
}

//Aggiorna la topbar
keyBoard* keyBoard::updateTopBar()
{
  this->_topBar->setText( "   Current Octave: "+QString::number(this->_curOctave)+" (Min: "+QString::number(this->_minOctave)+"; Max:"+QString::number(this->_maxOctave)+")" );
  return this;  
}

//restituisce la larghezza totale della tastiera
int keyBoard::width() 
{
  if(Xoffset<0)
    return qMin(this->cNotes.count() * this->cKeyWidth, -Xoffset);
  return
    this->cNotes.count() * this->cKeyWidth;
}

//restituisce l'altezza totale della tastiera
int keyBoard::height() 
{
  return (this->cKeyHeight*(Yoffset+1))+30;
}

//suona la nota e ne stampa il nome sul standard standard output
void keyBoard::playNote(Key* note)
{
    note->play();
    QTextStream out(stdout);
    out << note->name() << " ";
}


//stoppa la nota
void keyBoard::stopNote(Key* note)
{
  note->stop();
}


// genera la tastiera
keyBoard* keyBoard::generate(int minO, int maxO, QString keyFile, QString genN, double genF)
{
  //Prende un file in input
  QTextStream out(stdout);
  QFile file(keyFile);

  if(!file.open(QIODevice::ReadOnly)) {
    out << "File not found";
    return (new keyBoard());
  }

  this->_layout = keyFile;

  out << keyFile << "\n";
  QTextStream in(&file);
  int i;
  char* c;

  while(!in.atEnd()) {
    QString line = in.readLine();
    //trasforma i valori dei tasti (q,w,e,r,t,y), presi come string nel loro corrispondente int. 
    QStringList fields = line.split(" ");
    QByteArray ba = fields[0].toLocal8Bit();
    c = ba.data();
    //Trasforma il valore del tasto nel corrispondente keycode (numeri e lettere hanno differenze diverse)
    i = c[0] - (fields[0].contains(*(new QRegExp("[0-9]")))?0:32);
    //metto nel vettore code i keycode
    code.push_back(i);
    //e nel vettore K le note
    K.push_back(fields[1]);
  }
  
  //Chiude il file
  file.close();
  //Considero solo i primi tre caratteri di genN
  genN = genN.left(3);
  
  //Se non contiene le cose giuste, butta via??
  if(!genN.contains(QRegExp("[a-g][1-8][#]{0,1}")) ) 
  {
    return this;
  }
  
  //Setta un po di variabili
  this->_generatorNote = genN;
  this->_generatorFreq = genF;
  this->_curOctave = genN.mid(1,1).toInt();
  this->_minOctave = minO;
  this->_maxOctave = maxO;
  this->_generated = true;
 
  //Mette i diesis
  QString h = "";
  if(genN.right(1)=="#") h="#";
  QString startN = genN.left(1) + h;
  QString notes="cdefgab";

  QVector<QString> allNotes;
  QString tmp;
 
 //Crea le note a partire dalla ottava precedente alla minima
 for (int i = 5; i<7; ++i)
 {
   tmp = notes.at(i)+QString::number(minO-1);
   allNotes.push_back(tmp);
   if(tmp.left(1)!="b"&&tmp.left(1)!="e") {
     tmp += "#";
     allNotes.push_back(tmp);
   }
 }
 
 //Crea le altre nore, fino all'ottava massima
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
 
 //Aggiungo il do della ottava sopra la massima 
 allNotes.push_back( "c"+QString::number(maxO+1) );

 int n = allNotes.indexOf(genN);
 double f, a = 1.05946309436; //Distanza in frequenza tra 2 note
 for(int i = 0; i<allNotes.size();++i) 
 {
  //Do' la frequenza giusta ad ogni nota
  f = genF * pow(a, (i-n));
  //aNotes e cNotes sono qmap, che collega un double (f) ad una stringa (il nome della nota)
  (allNotes.at(i).right(1)=="#") ? this->aNotes[f]=allNotes.at(i) : this->cNotes[f]=allNotes.at(i); 
 }
 return this;
}

//Disegna la tastiera
keyBoard* keyBoard::draw() 
{
  QDesktopWidget desktop;
  QTextStream out(stdout);

  //Prendo la larghezza dell schermo
  int desktopWidth=desktop.geometry().width();
  if( this->_generated == false ) {
    this->generate(4, 4);
  }

  int left = 0, top = 20;
  QString last = "";
  bool checked = false;

    //Creo tastiera partendo dalle cNotes
    for( auto i : this->cNotes.keys()) //keys restituisce solo le chiavi, non il valore (qMap(chiave,valore))
    {
      Key* t = new Key(cNotes.value(i), this);
      this->_keys.push_back(t);
      t->setGeometry(left, top, this->cKeyWidth, this->cKeyHeight)->setFrequency(i);
      //aumento left della larghezza di un tasto
      left += this->cKeyWidth;
      //se ho l'ultimo elemento della riga, metto il mio nome in  last
      if (checked==true) {
        last = cNotes.value(i);
        checked = false;
      }

      //Se fino a tre note in più sono più largo dello schermo e se sono un si o un mi, vado a capo
      if (left+3*this->cKeyWidth >= desktopWidth && (cNotes.value(i).left(1)=="e" || cNotes.value(i).left(1)=="b")) {
        //Aumeno l'Yoffset di uno
        Yoffset++;
        //E aumento l'Xoffset di left
        Xoffset -= left;
        left = 0;
        //aumento l'altezza della tastiera dell'altezza di un tasto
        top += this->cKeyHeight;
        //metto un flag sull'ultima nota 
        checked = true;
      } 
    }

    //Setto left come la distanza dal bordo del primo alterato
    left = this->cKeyWidth - ( this->aKeyWidth / 2 );
    top = 20;

    //Setto le note alterate
    for( auto j : this->aNotes.keys() )
    {
      //Se sono un do o un fa, aumento left di una larghezza dei tasti puliti
      if(aNotes.value(j).left(1) == "c" || aNotes.value(j).left(1) == "f") left += this->cKeyWidth;
      //Se sono l'ultima delle note pulite vado a capo anche con quelle alterate
      if (aNotes.value(j).left(2) == last) {
        left = this->cKeyWidth - ( this->aKeyWidth / 2 );
        top += this->cKeyHeight;
      }
    
      Key* t = new Key(aNotes.value(j), this);
      this->_keys.push_back(t);
      t->setGeometry(left, top, this->aKeyWidth, this->aKeyHeight)->setFrequency( j );
      left += this->cKeyWidth;
    }
    QLabel* fb = new QLabel(this);
    this->_topBar = fb;
    this->updateTopBar();
  return this;
}

//funzione che prende il keycode e lo trasforma in note utilizzabili
Key* keyBoard::getNoteByKeyCode(int keyCode)
{
  int cur = this->_curOctave;

  if(code.indexOf(keyCode)==-1) return (new Key());
  
  int index = code.indexOf(keyCode);
  QString note = K.at(index);
  
  // sostituisce la regex PCS con l'ottava corrente -1,+0,+1
  note = note.replace("$c",QString::number(cur)).replace("$p",QString::number(cur-1)).replace("$n",QString::number(cur+1));

  for (int i= 0; i< this->_keys.size(); ++i)
  {
    if(note==this->_keys.at(i)->name()) { return this->_keys.at(i); }
  }
  return (new Key());
}

//Funzione che permette di alzare o abbassare l'ottava con ctrl e shift, e da playNote con le altre XD
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

void keyBoard::chOctEventUp(){
  QTextStream o(stdout);
  o << _curOctave;
  this->_curOctave = _curOctave+1;
  if(_curOctave>_maxOctave) _curOctave = _maxOctave;
  this->updateTopBar();
  o << _curOctave;
}

void keyBoard::chOctEventDown(){
  this->_curOctave = _curOctave-1;
  if(_curOctave<_minOctave) _curOctave = _minOctave;
  this->updateTopBar();
}
