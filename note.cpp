#include "note.hpp"

note::note()
{
  
}

void note::setNote(QString name)
{
  QMap<QString, double> freqs;
   freqs["a"] = 440.00; //LA4
   freqs["w"] = 466.16;
   freqs["s"] = 493.88;
   freqs["d"] = 523.25;
   freqs["r"] = 554.37;
   freqs["f"] = 587.33;
   freqs["t"] = 622.25;
   freqs["g"] = 659.26;
   freqs["h"] = 698.46;
   freqs["u"] = 739.99;
   freqs["j"] = 783.99;
   freqs["i"] = 830.61;
   freqs["k"] = 880.00; //LA5
   freqs["o"] = 932.33;
   freqs["l"] = 987.77;
   freqs["p"] = 1046.5;
   
  double f;
  QString l;
  QVector<QString> notes{"a4","a4#","b4","c5","c5#","d5","d5#","e5","f5","f5#","g5","g5#","a5","a5#","b5","c6"};
  //FU**ING QMAP/STDMAP that makes no index access to their key/value pair
  //also, too lazy to extend qmap with this feature
  //so I use another vector to pass from index to key before access QMap
  QVector<QString> keys{"a","w","s","d","r","f","t","g","h","u","j","i","k","o","l","p"};
  
  int i = notes.indexOf(name);
  l = keys[i];
  f = freqs[l];
  
  this->name = name;
  this->letter = l;
  this->freq = f;
}
