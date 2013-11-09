/**
 * mainWindow.hpp
 * 
 * THE FATHER, THE SON AND THE HOLY SPIRIT!
 * CLASS, OBJECT AND FUNCTION, UNO E TRINO
 * 
 * Contains ALL Methods called on the main window
 * 
 * **/ 

#ifndef MAINWINDOW_H
  #define MAINWINDOW_H

  #include <QMainWindow>
  #include <QApplication>
  #include <QPushButton>
  #include <QMenu>
  #include <QMenuBar>
  #include <QTextStream>
  #include <QKeyEvent>
  #include "key.hpp"
  #include "note.hpp"

  class mainWindow : public QMainWindow
  {
    public:
      mainWindow(QWidget *parent = 0);
      void addKey(int left, QString nt);
      
    public slots:
      void onKeyClick(QString nt);
  };
  
#endif
