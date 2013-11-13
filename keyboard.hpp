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
  #include "audiooutputstreamer.hpp"

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
      void playNoteByKeyCode(int);
      
      keyBoard* generate(int,int,QString="a4",double=440.);
      keyBoard* sort();
      keyBoard* draw();
      
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
      
      // keyboard access is based on layout. default layout is "base"
      QString _layout="base";
      int _curOctave;
      int _minOctave;
      int _maxOctave;
      
      QString _generatorNote;
      double  _generatorFreq;
      
      bool _generated = false;
      
      QLabel* _topBar;
      
      AudioOutputStreamer* _aOutput;

  };

#endif
