#ifndef MAINWINDOW_H
  #define MAINWINDOW_H

  #include <QMainWindow>
  #include <QTextStream>
  #include <QApplication>
  #include <QVector>
  #include <QToolBar>
  #include <QMenu>
  #include <QMenuBar>
  #include <QMenu>
  #include <QTextStream>
  #include <QMap>
  #include "keyboard.hpp"
  #include "options.hpp"
  #include "recplay.hpp"

  class mainWindow : public QMainWindow
  {
    Q_OBJECT
    public:
      mainWindow(QWidget *parent = 0); 
      QWidget* getMainWidget();
       
      template<class C>
      QWidget* setMainWidget(C w) {
        this->mainWidget = (QWidget*) w;
        return this->mainWidget;
      };

      mainWindow* defaultMenus();
      mainWindow* draw();
      
      int getToolbars();
      int getMenus();

    private:
      QWidget* mainWidget;
      QVector<QMenu*> menus;
      QVector<QMenu*> tbars;
  };
  
#endif
