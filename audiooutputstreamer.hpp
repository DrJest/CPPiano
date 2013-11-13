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

using namespace std;

class AudioOutputStreamer : public QObject
{
	Q_OBJECT

	public:
    	AudioOutputStreamer();
    	~AudioOutputStreamer();
    	void start(int);
      void stop();

	public slots:
    	void slot_writeMoreData();

	private:
    	QAudioOutput* _audio;
    	QIODevice* _pAudioIOBuffer;

    	float _samplingRate;

    	unsigned long _IDWrittenSample;
    	float _amplitude;
    	float _delta_t;
    	float _omega;
    	signed char* _buffer;
    	int _sizeNolBuffer;

};
        	
#endif
