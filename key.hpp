/**
 * key.hpp
 * 
 * Contains and implements keyboard keys
 * 
 * for error Gtk-CRITICAL **: IA__gtk_widget_get_direction: assertion `GTK_IS_WIDGET (widget)' failed
 * https://bugzilla.redhat.com/show_bug.cgi?id=924683
 * 
 * **/ 

#ifndef KEY_H
  #define KEY_H

  #include <QPushButton>
  #include <QTextStream>
  #include <QWidget>
  #include <QMouseEvent>
  #include "audiooutputstreamer.hpp"

    
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
      void play();
      void stop();
      
      QString name();
      double frequency();
      bool sharp();
      bool valid();
      
    protected:
      //void mousePressEvent(QMouseEvent*);
    
    private:
      QString _name;
      QString _defaultStyle;
      QWidget* _parent;
      int _left, _top, _width, _height;
      double _frequency;
      bool _sharp = false;
      bool _valid = false;

      AudioOutputStreamer* _aOutput;

  };

#endif
