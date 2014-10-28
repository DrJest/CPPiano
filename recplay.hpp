#ifndef REC_H
  #define REC_H

  #include <QPushButton>
  #include <QTextStream>
  #include <QWidget>
  #include <QMouseEvent>
  #include <QTimer>
  #include <chrono>
  #include <QMap>

  class keyBoard;
  class Key;

  class RecPlay : public QObject
  {
    Q_OBJECT
    
    public:
      RecPlay(QWidget*);
      ~RecPlay(){};
      bool recording();
      void send(Key*, std::chrono::high_resolution_clock::time_point,std::chrono::high_resolution_clock::time_point);
 
    public slots:
      void startRec();
      void stopRec();
      void Play();
      void Pause();
      void Stop();

    protected:

    private:
      void Open();
      void Save();
      std::chrono::high_resolution_clock::time_point _start;
      bool _recording = false;
      keyBoard* _kb;
      QMap<Key*, double> _registration;
  };

#endif