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
  #include "recplay.hpp"

  class keyBoard : public QWidget
  {
    Q_OBJECT
    
    public:
      keyBoard(QWidget* = 0);
      ~keyBoard() {};

      QWidget* parent() {return _parent;}
      
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
      Key* getNoteByName(QString);
      
      keyBoard* generate(int,int,QString="assets/default.keys",QString="a4",double=440.);
      keyBoard* sort();
      keyBoard* draw();
      keyBoard* timbre(QString);
      QVector<double> timbre();
      QString getTimbre();

      static QString Usage();

      int getMinOct() {
        return this->_minOctave;
      }
      int getMaxOct() {
        return this->_maxOctave;
      }
      QString getGeNote() {
        return this->_generatorNote;
      }
      double getGenFreq() {
        return this->_generatorFreq;
      }
      QString getLayout() {
        return this->_layout;
      }

      RecPlay* rec();
      void setKeyLetters();

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

      QVector<double> _timbre;

      int _curOctave;
      int _minOctave;
      int _maxOctave;
      
      QString _generatorNote;
      double  _generatorFreq;
      
      bool _generated = false;
      
      QLabel* _topBar;
      
      QString _layout = "";

      QVector<QString> letters;
      QVector<int> code;
      QVector<QString> K;

      QWidget* _parent;
  };

#endif
