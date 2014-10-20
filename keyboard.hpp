/**
 * 
 * 
 * 
 * */

#ifndef KEYBOARD_H

  #define KEYBOARD_H
  
  #include <QWidget>
  #include <QTextStream>
  #include <QKeyEvent>
  #include <QMap>
  #include <QLabel>
  #include "key.hpp"

  class keyBoard : public QWidget
  {
    Q_OBJECT
    
    public:
      keyBoard(QWidget* = 0);
      ~keyBoard() {};
      
      keyBoard* setCKeyWidth(int);
      keyBoard* setAKeyWidth(int);
      keyBoard* setCKeyHeight(int);
      keyBoard* setAKeyHeight(int);
      keyBoard* setKeyGeometry(int,int,int,int);
      keyBoard* updateTopBar();
      
      int width();
      int height();
            
      void playNote(Key*);
      void stopNote(Key*);
      Key* getNoteByKeyCode(int);
      
      keyBoard* generate(int,int,QString="assets/default.keys",QString="a4",double=440.);
      keyBoard* sort();
      keyBoard* draw();

    public slots:
      void chOctEventUp();
      void chOctEventDown();
      
    protected:
      void keyPressEvent(QKeyEvent *);
      void keyReleaseEvent(QKeyEvent *);
    
    private:
    // frequency is first due to qmap auto sorting
      QMap<double,QString> cNotes;
      QMap<double,QString> aNotes;
      
      QVector<Key*> _keys;
            
      // keys default dimensions
      int cKeyWidth = 40;
      int cKeyHeight = 160;
      int aKeyWidth = 30;
      int aKeyHeight = 80;
      
      int Xoffset = 0;
      int Yoffset = 0;

      int _curOctave;
      int _minOctave;
      int _maxOctave;
      
      QString _generatorNote;
      double  _generatorFreq;
      
      bool _generated = false;
      
      QLabel* _topBar;
      
      QVector<int> code;
      QVector<QString> K;
  };

#endif
