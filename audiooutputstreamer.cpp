/**
 * audiooutputstreamer.cpp
 * 
 * Oggetti che restituiscono un suono se gli passo una key.
 * Verranno usati nel Key.cpp per collegare pressione a suono
 *
 * **/ 


#include "audiooutputstreamer.hpp"
#include "key.hpp"
#include "keyboard.hpp"

//Creatore degli oggetti AudioOutputStreamer
//che ereditano pubblicamente da QObject
//che instanziano il motodo di output del suono.
AudioOutputStreamer::AudioOutputStreamer(double f, Key* key)
{
	_key = key;
	// e' il sampling rate 
	_samplingRate = 44100;

	QAudioFormat format;
	// set up the format you want, eg.
	format.setFrequency(_samplingRate);
	format.setChannels(1);
	format.setSampleSize(8);
	format.setCodec("audio/mp3");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	//Prende le info del hardware audio
	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(format)) {
	  qWarning()<<"default format not supported try to use nearest";
   	  format = info.nearestFormat(format);
	}

	//inizializza un nuovo canale output
	_audio = new QAudioOutput(format, this);
	_audio->setNotifyInterval(10);
	_audio->setBufferSize(32768);//in bytes

	//costanti utili
	_delta_t = 1/_samplingRate;
    _omega = 2*PI*f;

    //variabili globali usate nella funzione slot_writeMoreData()
	_IDWrittenSample = 0;
	_sizeNolBuffer = 0;

}

AudioOutputStreamer::~AudioOutputStreamer()
{
}

//Funzione che connette il canale audio  
void AudioOutputStreamer::start()
{
	this->_timbre = _key->parent()->timbre();
	//disconnetto per sicurezza
 	QObject::disconnect(_audio, SIGNAL(notify()), this, SLOT(slot_writeMoreData()));
	//Quando ho un segnale di tipo notify() connetti me, attraverso slot_writeMoreData al canale audio.
	QObject::connect(_audio, SIGNAL(notify()), this, SLOT(slot_writeMoreData()));
  
  	//ritorna un puntatore al device, mi permettete di usare scrivere direttamente i dati audio
	_pAudioIOBuffer = _audio->start();
	//creo un buffer di char che contiene la dimensione del periodo in bytes
	unsigned int periodSize = _audio->periodSize();
	_sizeNolBuffer = periodSize;
	_buffer = (signed char*) calloc(_sizeNolBuffer, sizeof(signed char));	

	slot_writeMoreData();

}

//Funzione che stoppa l'audio
void AudioOutputStreamer::stop()
{
  _audio->stop();
  _audio->reset();
  _IDWrittenSample = 0;
}

//Lei suona
void AudioOutputStreamer::slot_writeMoreData()
{   
	//Numero di bytes liberi nel buffer audio 
	int nbBytes = _audio->bytesFree();
	if (nbBytes>0) {
		
		//se il periodo è piu piccolo dei bytes liberi, rendo _sizeNolBuffer grosso quanto i bytesFree e rialloco _buffer 
  		if (_sizeNolBuffer<nbBytes) {
        	delete[] _buffer;
        	_sizeNolBuffer = nbBytes;
        	_buffer = (signed char*) calloc(_sizeNolBuffer, sizeof(signed char));
    	}

    	//riempio _buffer completamente con i valori di una funzione che mi fa il tono di un pianoforte.        	
    	for (int IDSample=0; IDSample<nbBytes; ++IDSample) {
        	float time = (float)_IDWrittenSample * _delta_t;
            float t = 0;
            for(int i=1; i<9; ++i)
            {
                t += _timbre[i-1]*sin(i*_omega*time);
            }
            _buffer[IDSample] = (signed char) 10.*t;
        	++_IDWrittenSample;
    	}

    	//scrivo il mio buffer nel canale audio
    	_pAudioIOBuffer->write((const char*) _buffer, nbBytes);
	}
}
