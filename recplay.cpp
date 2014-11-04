#include "recplay.hpp"
#include "key.hpp"
#include "keyboard.hpp"
#include <QFileDialog>
#include <QMessageBox>

RecPlay::RecPlay(QWidget* parent) 
{
	this->_kb = (keyBoard*)parent;
}

void RecPlay::startRec()
{
	//se l'utente ha gia' una registrazione chiedo se sovrascriverla
	if(!this->_registration.isEmpty()) 
	{
	  QMessageBox::StandardButton reply;
	  reply = QMessageBox::question(this->_kb, "Test", "Unsaved recording will be deleted. Continue?",
	                                QMessageBox::Yes|QMessageBox::No);
	  if (reply == QMessageBox::Yes) {
	    this->_registration.clear();
	  } else {
	    return;
	  }
	}
//	this->_startRec = (QAction*)QObject::sender();
//	this->_startRec->setEnabled(false);
	if(recording())
		return;
	this->_start = std::chrono::high_resolution_clock::now();
	_recording = true;
	_kb->updateTopBar();
	this->_timer = new QTimer();
	connect(this->_timer, SIGNAL(timeout()), this, SLOT(PlayNextNote()));
}

void RecPlay::stopRec() 
{
	if(!recording())
		return;
//	this->_stopRec = (QAction*)QObject::sender();
//	this->_startRec->setEnabled(true);
//	this->_stopRec->setEnabled(false);
	this->_recording = false;
	_kb->updateTopBar();
}

void RecPlay::Pause() 
{

}

void RecPlay::Play()
{
	if(this->_registration.isEmpty())
		return;
	QTextStream o(stdout);
	o << "Start Play\n";
	this->_playing = true;
	_timer->setInterval(1);
	this->_ms = 0;
	_kb->updateTopBar();
	_timer->start();
}

void RecPlay::Stop() 
{
	this->_playing = false;
	this->_timer->stop();
	this->_ms = this->_registration.keys().last();
	QTextStream o(stdout);
	o << "Stop Play\n";
	_kb->updateTopBar();
} 

void RecPlay::PlayNextNote()
{
	this->_ms++;
	if(this->_ms > this->_registration.keys().last())
	{
		this->Stop();
		return;
	}
	if(_registration.contains(this->_ms))
	{
		Key* k = _registration[this->_ms].first;
		int duration = _registration[this->_ms].second;
		k->play();
		QTimer::singleShot(duration, k, SLOT(stop()));
	}
}

void RecPlay::Open() {
	QString fileName = QFileDialog::getOpenFileName(this->_kb, 
						"Open File",
                                             	".",
                                             	"CPPiano Recorded Files (*.crf)");
}

void RecPlay::Save() {

}

bool RecPlay::recording()  
{
	return this->_recording;
}

bool RecPlay::playing()  
{
	return this->_playing;
}

void RecPlay::send(Key* key, std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point stop) {
	if(!recording())
		return;
	std::chrono::duration<double,std::milli> start_relative = start - _start;
	std::chrono::duration<double,std::milli> stop_relative = stop - _start;
	int tstart = start_relative.count();
	int tduration = stop_relative.count() - start_relative.count();
	_registration.insert(tstart, qMakePair(key, tduration));
}
