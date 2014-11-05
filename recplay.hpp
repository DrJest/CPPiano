#ifndef REC_H
  #define REC_H

  #include <QPushButton>
  #include <QTextStream>
  #include <QWidget>
  #include <QMouseEvent>
  #include <QTimer>
  #include <chrono>
  #include <QMap>
  #include <QPair>
  #include <QAction>

  class keyBoard;
  class Key;

  class RecPlay : public QObject
  {
    Q_OBJECT
    
    public:
      RecPlay(QWidget*);
      ~RecPlay(){};
      bool recording();
      bool playing();
      void send(Key*, std::chrono::high_resolution_clock::time_point,std::chrono::high_resolution_clock::time_point);
      void setButtons(QAction*,QAction*,QAction*,QAction*,QAction*);
      int status();

    public slots:
      void startRec();
      void stopRec();
      void Play();
      void Pause();
      void Stop();
      void PlayNextNote();
      void Open();
      void Save();

    protected:

    private:
      QAction* _startRec;
      QAction* _stopRec;
      QAction* _pause;
      QAction* _startPlay;
      QAction* _stopPlay;
      std::chrono::high_resolution_clock::time_point _start;
      std::chrono::high_resolution_clock::time_point _pausedAt;
      bool _recording = false;
      bool _playing = false;
      bool _paused = false;
      keyBoard* _kb;
      QMap<int, QPair<Key*, int>> _registration;
      int _ms = 0;
      QTimer* _timer;
  };

#endif