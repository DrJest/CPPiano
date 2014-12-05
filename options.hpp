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
  #include <QTabWidget>
  #include <QRadioButton>
  #include <QVBoxLayout>
  #include <QLineEdit>
  #include <QGridLayout>

  class mainWindow;
  class keyBoard;

  class options : public QObject
  {
    Q_OBJECT
    public:
      options(QWidget*);
      ~options() {};
      void setLayout(QString);
    
    public slots:
      void spawnOptionsWindow();
      void toggleLayoutCustomField(bool);
      void saveOptions();
      void cusBrowse();
      void setDefaultLayout(bool);
      void setCompleteLayout(bool);
      void setMinOctave(int);
      void setMaxOctave(int);

    private:
      mainWindow* _mainwindow;
      keyBoard* _keyboard;
      QWidget* _cusLayoutFieldBox;
      QWidget* _main;
      QLineEdit* _timbre;
      int minOctave;
      int maxOctave;

      //a field for each option
      QString _layout;
  };

#endif
