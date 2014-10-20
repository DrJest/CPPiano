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
  //#include "keyboard.cpp"



struct mainWindowMenuItem
{
  QString label;
  QString icoSrc = "";
  QKeySequence shortcut = 0;
  
};

class mainWindowMenu
{
  public:
    mainWindowMenu() {};
    
    mainWindowMenu* addItem(mainWindowMenuItem item)
    {
      this->items.push_back(item);
      this->itemsn++;
      return this;
    };
    QString type;
    QString label = "";
    QVector<mainWindowMenuItem> items;
    int itemsn; 
};

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

      mainWindowMenu* addMenu(QString = "");
      
      mainWindow* defaultMenus();
      mainWindow* draw();
      
      int getToolbars();
      int getMenus();

    private:
      keyBoard* keyboard;
      QWidget* mainWidget;
      QVector<mainWindowMenu> menus;
      QVector<mainWindowMenu> tbars;
  };
  
#endif
