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
      void setNote(QString);
      QString getN();

    protected:
      void mousePressEvent(QMouseEvent*);
    
    private:
      QString name;
  };

#endif
