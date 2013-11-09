/**
 * key.hpp
 * 
 * Contains and implements keyboard keys
 * 
 * **/ 

#ifndef KEY_H
  #define KEY_H

  #include "mainWindow.hpp"
  #include "note.hpp"
  #include "key.hpp"

  class key : public QPushButton
  {
    public:
      key(QString name, QWidget *parent);
      void assign(QString name);
      QString getN();
      
    private:
      QString name;
      note n;
  };

#endif
