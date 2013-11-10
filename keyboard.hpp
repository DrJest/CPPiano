/**
 * 
 * 
 * 
 * */

#ifndef KEYBOARD_H

  #define KEYBOARD_H
  
  #include <QWidget>
  #include <QTextStream>
  #include "key.hpp"
  
  class keyBoard : public QWidget
  {
    Q_OBJECT
    
    public:
      keyBoard(QWidget* = 0);
      Key* addKey(QString);
      void playNote(Key*);
      void getNote(int);
      
      keyBoard* sort();
      keyBoard* draw();
      
      int getWidth();
      int getHeight();
      
      bool isPresent(QString);
      
      keyBoard* setCKeyWidth(int);
      keyBoard* setAKeyWidth(int);
      keyBoard* setCKeyHeight(int);
      keyBoard* setAKeyHeight(int);
      keyBoard* setKeyGeometry(int,int,int,int);
      
    private:
      QVector<Key*> cKeys;
      QVector<Key*> aKeys;
      
      QString firstNote = "";
      
      int cKeyWidth = 40;
      int cKeyHeight = 160;
      int aKeyWidth = 30;
      int aKeyHeight = 80;
      
      
  };

#endif
