#ifndef AUDIOOUTPUTSTREAMER_H
    #define AUDIOOUTPUTSTREAMER_H

        #include <QObject>
        #include <QAudioOutput>
        #include <QAudioFormat>
        #include <QIODevice>
        #include <QAudioDeviceInfo>
        #include <QDebug>

        #include <math.h>
        #include <iostream>


        #define PI 3.14159265

        class Key;

        class AudioOutputStreamer : public QObject
        {
        	Q_OBJECT

        	public:
            	AudioOutputStreamer(double, Key*);
            	~AudioOutputStreamer();
            	void start();
                void stop();

        	public slots:
            	void slot_writeMoreData();

        	private:
            	QAudioOutput* _audio;
            	QIODevice* _pAudioIOBuffer;

            	float _samplingRate;

            	unsigned long _IDWrittenSample;
            	float _delta_t;
                double _frequency;
            	float _omega;
            	signed char* _buffer;
            	int _sizeNolBuffer;
                QVector<double> _timbre;
                Key* _key;
        };
        	
#endif
