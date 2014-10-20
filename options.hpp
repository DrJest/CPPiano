/**
 * 
 * 
 * 
 * */

#ifndef OPTIONS_H

  #define OPTIONS_H
  #include <QDesktopWidget>
  #include <QWidget>
  #include <QTextStream>
  #include <QKeyEvent>
  #include <QMap>
  #include <QLabel>

  class mainWindow;
  class keyBoard;

  class options : public QObject
  {
    Q_OBJECT
    public:
      options(QWidget*);
      ~options() {};
    
    public slots:
      void setDefaultLayout();
      void setCompleteLayout();

    private:
      mainWindow* _mainwindow;
      keyBoard* _keyboard;
  };

#endif
