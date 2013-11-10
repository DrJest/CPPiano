/**
 * mainWindow.hpp
 * **/ 

#ifndef MAINWINDOW_H
  #define MAINWINDOW_H

  #include <QMainWindow>
  #include <QTextStream>
  #include <QApplication>
  #include <QVector>
  #include <QToolBar>
  #include <QMenu>
  #include <QMenuBar>
  #include <QKeyEvent>
  #include <QMenu>
  #include <QTextStream>

template<class type1, class type2>
struct mainWindowItem
{
  type1 name;
  QVector<type2> data;
};

  class mainWindow : public QMainWindow
  {
    Q_OBJECT
    public:
      mainWindow(QWidget *parent = 0); 
      //AS jQuery teaches, void functions are useless.Make each function
      //return the instantied elemnt's pointer itself
      QWidget* getMainWidget();
      QWidget* setMainWidget(QWidget*);
      bool disableDefaultMenus();
      //returns the object itself
      mainWindow* draw();
      
    protected:
      void keyPressEvent(QKeyEvent *);
      void keyReleaseEvent(QKeyEvent *);
    
    private:
      QWidget* mainWidget;
      QVector<mainWindowItem> toolbars;
      QVector<mainWindowItem> menus;
      bool defaultMenusDisabled = false;
  };
  
#endif
