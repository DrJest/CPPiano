/**
 * note.hpp
 * 
 * Contains declarations of notes type and methods to create and assign them
 * 
 * **/ 

#ifndef NOTE_H
  #define NOTE_H
  
  #include <QTextStream>
  #include <QMap>
  #include <QVector>

  class note
  {
    public:
      note();
      void setNote(QString name);
      double getFrequency();
      
    private:
      QString name;
      double freq;
      QString letter;
  };

#endif
