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
AudioOutputStreamer::AudioOutputStreamer(int f, Key* key)
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
	_audio->setNotifyInterval(50);
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
    	short int value = 0;
    	float v = 0.;
    	for (int IDSample=0; IDSample<nbBytes; ++IDSample) {
        	float time = (float)_IDWrittenSample * _delta_t;
        	switch(_timbre)
        	{
        		case 1: //piano
        			v = (10.*(float)(sin(_omega*time)+0.2*sin(2*_omega*time)+0.25*sin(3*_omega*time)+0.1*sin(4*_omega*time)+0.1*sin(5*_omega*time)));
        			break;
        		case 2: //violino
        			v = (10.*(float)(sin(_omega*time)+sin(2*_omega*time)+0.45*sin(3*_omega*time)+0.5*sin(4*_omega*time)+sin(5*_omega*time)+0.02*sin(6*_omega*time)+0.025*sin(7*_omega*time)+0.03*sin(8*_omega*time))); 
        			break;
        		default:
        			v = (float)(10.*sin(_omega*time));
        			break;
        	}
        	value = (signed char) v;
        	_buffer[IDSample] = value;
        	++_IDWrittenSample;
    	}

    	//scrivo il mio buffer nel canale audio
    	_pAudioIOBuffer->write((const char*) _buffer, nbBytes);

    	//Se ho superato il _samplingRate disconnetto il canale
    	//e stoppo la key.
    	if (_IDWrittenSample>_samplingRate) {
        	QObject::disconnect(_audio, SIGNAL(notify()), this, SLOT(slot_writeMoreData()));
        	_key->stop();
    	}
	}
}
