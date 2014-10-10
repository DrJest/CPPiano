#include "audiooutputstreamer.hpp"

AudioOutputStreamer::AudioOutputStreamer(int f)
{
	// e' il sampling rate 
	_samplingRate = 44100;

	QAudioFormat format;
	// set up the format you want, eg.
	format.setFrequency(_samplingRate);
	format.setChannels(1);
	format.setSampleSize(8);
	format.setCodec("audio/ogg");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(format)) {
	  qWarning()<<"default format not supported try to use nearest";
   	  format = info.nearestFormat(format);
	}

	_audio = new QAudioOutput(format, this);
	_audio->setNotifyInterval(50);
	_audio->setBufferSize(32768);//in bytes

	_amplitude = 10.;
	_delta_t = 1/_samplingRate;

    _omega = 2*PI*f;

	_IDWrittenSample = 0;
	_sizeNolBuffer = 0;

}

AudioOutputStreamer::~AudioOutputStreamer()
{
}

void AudioOutputStreamer::start()
{
 	QObject::disconnect(_audio, SIGNAL(notify()), this, SLOT(slot_writeMoreData()));
	QObject::connect(_audio, SIGNAL(notify()), this, SLOT(slot_writeMoreData()));
  
	_pAudioIOBuffer = _audio->start();
	unsigned int periodSize = _audio->periodSize();
	_sizeNolBuffer = periodSize;
	_buffer = (signed char*) calloc(_sizeNolBuffer, sizeof(signed char));	

	slot_writeMoreData();

}

void AudioOutputStreamer::stop()
{
  _audio->stop();
  _audio->reset();
  _IDWrittenSample = 0;
}

void AudioOutputStreamer::slot_writeMoreData()
{   
	int nbBytes = _audio->bytesFree();
	if (nbBytes>0) {
  	if (_sizeNolBuffer<nbBytes) {
        	delete[] _buffer;
        	_sizeNolBuffer = nbBytes;
        	_buffer = (signed char*) calloc(_sizeNolBuffer, sizeof(signed char));
    	}
        	
    	short int value = 0;
    	for (int IDSample=0; IDSample<nbBytes; ++IDSample) {
        	float time = (float)_IDWrittenSample * _delta_t;
        	value = (signed char) (_amplitude*(float)(sin(_omega*time)));
        	_buffer[IDSample] = value;
        	++_IDWrittenSample;
    	}

    	_pAudioIOBuffer->write((const char*) _buffer, nbBytes);

    	if (_IDWrittenSample>_samplingRate) {
        	QObject::disconnect(_audio, SIGNAL(notify()), this, SLOT(slot_writeMoreData()));
        	_audio->stop();
    	}
	}
}
