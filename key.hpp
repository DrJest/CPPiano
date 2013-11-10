/**
 * key.hpp
 * 
 * Contains and implements keyboard keys
 * 
 * **/ 

#ifndef KEY_H
  #define KEY_H

  #include <QPushButton>
  #include <QTextStream>
  #include <QWidget>
  #include <QMouseEvent>
    
  class Key : public QPushButton
  {
    Q_OBJECT
    
    public:
      Key(QString, QWidget*);
      ~Key(){};
      int left();
      void setNote(QString);
      void setGeometry(int,int,int,int);
      QString getN();

    protected:
      void mousePressEvent(QMouseEvent*);
    
    private:
      QString name;
      QWidget* _parent;
      int _left, _top, _width, _height;
  };

#endif
