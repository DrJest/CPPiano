#ifndef KEY_H
  #define KEY_H

  #include <QPushButton>
  #include <QTextStream>
  #include <QWidget>
  #include <QMouseEvent>
  #include "audiooutputstreamer.hpp"
  #include "recplay.hpp"
  #include <QTimer>
  #include <chrono>

  class keyBoard;
  
  class Key : public QPushButton
  {
    Q_OBJECT
    
    public:
      Key();
      Key(QString, QWidget*);
      ~Key(){};
      int left();
      Key* setGeometry(int,int,int,int);
      Key* setFrequency(double);
      Key* setDefaultStyle();
      
      QString name();
      double frequency();
      bool sharp();
      bool valid();
      
      keyBoard* parent();

      clock_t lastTriggered;
      bool _playing = false;
      QTimer* _timer;

    public slots:
      void play();
      void stop();

    protected:
      void mousePressEvent(QMouseEvent*);
      void mouseReleaseEvent(QMouseEvent*);

    private:
      QString _name;
      QString _defaultStyle;
      QWidget* _parent;
      int _left, _top, _width, _height;
      double _frequency;
      bool _sharp = false;
      bool _valid = false;

      RecPlay* _rec;
      std::chrono::high_resolution_clock::time_point _start;

      AudioOutputStreamer* _aOutput;
  };

#endif
