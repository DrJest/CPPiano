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
  #include <QMenu>
  #include <QTextStream>
  #include <QMap>

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
      // AS jQuery teaches, void functions are useless. I make each 
      // function return the instantied element's pointer itself
      QWidget* getMainWidget();
      
      // children could be ANY type of QObject.
      // template allows me to avoid overload this method for
      // each of the pretty INFINITE type of QObject tha could be
      // derived from the original class 
      template<class C>
      QWidget* setMainWidget(C w) {
        // dynamic_cast operator should be used instead!!
        // but since it's only me gonna be running this
        // i make an explicit cast in order to reduce runtime work
        this->mainWidget = (QWidget*) w;
        return this->mainWidget;
      };

      mainWindowMenu* addMenu(QString = "");
      
      mainWindow* defaultMenus();
      mainWindow* draw();
      
      int getToolbars();
      int getMenus();

    private:
      QWidget* mainWidget;
      QVector<mainWindowMenu> menus;
      QVector<mainWindowMenu> tbars;
  };
  
#endif
