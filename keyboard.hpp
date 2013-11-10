/**
 * 
 * 
 * 
 * */

#ifndef KEYBOARD_H

  #define KEYBOARD_H
  
  #include <QWidget>
  #include <QTextStream>
  
  class keyBoard : public QWidget
  {
    Q_OBJECT
    
    public:
      keyBoard(QWidget* = 0);
      void addKey(int, QString);
  };

#endif
