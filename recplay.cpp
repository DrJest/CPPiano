#include "recplay.hpp"
#include "key.hpp"
#include "keyboard.hpp"
#include "mainWindow.hpp"
#include <QFileDialog>
#include <QMessageBox>

RecPlay::RecPlay(QWidget* parent) 
{
	this->_mw = (mainWindow*)parent;
}

void RecPlay::setButtons(QAction* b1, QAction* b2, QAction* b3, QAction* b4, QAction* b5) 
{
	this->_startRec = b1;
	this->_stopRec = b2;
	this->_pause = b3;
	this->_startPlay = b4;
	this->_stopPlay = b5;
}

void RecPlay::startRec()
{
	//se l'utente ha gia' una registrazione chiedo se sovrascriverla
	if(!this->_registration.isEmpty() && !this->_paused && this->_unsavedChanges) 
	{
	  QMessageBox::StandardButton reply;
	  reply = QMessageBox::question(this->kb(), "Test", "Unsaved recording will be deleted. Continue?",
	                                QMessageBox::Yes|QMessageBox::No);
	  if (reply == QMessageBox::Yes) {
	    this->_registration.clear();
	  } else {
	    return;
	  }
	}
	if(this->_recording)
		return;

	this->_startRec->setEnabled(false);
	this->_stopRec->setEnabled(true);
	this->_pause->setEnabled(true);
	this->_startPlay->setEnabled(false);
	this->_stopPlay->setEnabled(false);
	
	if(!this->_paused)
		this->_start = std::chrono::high_resolution_clock::now();
	else {
		std::chrono::duration<double,std::milli> pausedFor = std::chrono::high_resolution_clock::now() - _pausedAt;
		this->_start = this->_start + std::chrono::duration_cast<std::chrono::milliseconds>(pausedFor);
	}

	this->_paused = false;
	this->_recording = true;
	this->_unsavedChanges = true;
	
	kb()->updateTopBar();
	
	this->_timer = new QTimer();
	connect(this->_timer, SIGNAL(timeout()), this, SLOT(PlayNextNote()));
}

void RecPlay::stopRec() 
{
	if(!recording() && !this->_paused)
		return;
	this->_startRec->setEnabled(true);
	this->_stopRec->setEnabled(false);
	this->_pause->setEnabled(false);
	this->_startPlay->setEnabled(true);
	this->_stopPlay->setEnabled(false);
	this->_paused = false;
	this->_recording = false;
	kb()->updateTopBar();
}

void RecPlay::Pause() 
{
	if(this->_recording) {
		this->_startRec->setEnabled(true);
		this->_stopRec->setEnabled(true);
		this->_pausedAt = std::chrono::high_resolution_clock::now();
		this->_recording = false;
	}
	else if(this->_playing) {
		this->_startPlay->setEnabled(true);
		this->_stopPlay->setEnabled(true);
		this->_playing = false;
		this->_timer->stop();
	}
	else return;
	this->_paused = true;
	this->_pause->setEnabled(false);
	kb()->updateTopBar();
}

void RecPlay::Play()
{
	if(this->_registration.isEmpty())
		return;
	
	QTextStream o(stdout);
	o << "Start Playing\n";
	this->_startRec->setEnabled(false);
	this->_stopRec->setEnabled(false);
	this->_pause->setEnabled(true);
	this->_startPlay->setEnabled(false);
	this->_stopPlay->setEnabled(true);

	this->_playing = true;
	this->_paused = false;
	_timer->setInterval(1);
	//this->_ms = 0;
	kb()->updateTopBar();
	_timer->start();
}

void RecPlay::Stop() 
{
	if(!this->_playing && !this->_paused)
		return;
	this->_startRec->setEnabled(true);
	this->_stopRec->setEnabled(false);
	this->_pause->setEnabled(false);

	if(!_registration.isEmpty())
		this->_startPlay->setEnabled(true);

	this->_stopPlay->setEnabled(false);

	this->_playing = false;
	this->_paused = false;
	this->_timer->stop();
	this->_ms = 0;
	QTextStream o(stdout);
	o << "Stop Play\n";
	kb()->updateTopBar();
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

keyBoard* RecPlay::kb() {
	return (keyBoard*)this->_mw->getMainWidget();
}


void RecPlay::Clear() {
	stopRec();
	Stop();
	kb()->parent()->setWindowTitle("CPPiano");
	_registration.clear();
}

void RecPlay::Open() {
	QString fileName = QFileDialog::getOpenFileName(0, 
						"Open File",
                     	".",
                     	"CPPiano Recorded Files (*.crf)");
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0,"Error",file.errorString());
		return;
	}

	QTextStream in(&file);
	QTextStream out(stdout);

	this->_registration.clear();

	startRec();
	while(!in.atEnd()) 
	{
		QString line = in.readLine();
		QStringList fields = line.split(" ");
		Key* k = kb()->getNoteByName(fields[0]);
		if(!k->valid()) {
			k = new Key(fields[0], kb());
			k->setFrequency(fields[1].toDouble());
		}
		_registration.insert(fields[2].toInt(), qMakePair(k, fields[3].toInt()));
	}
	stopRec();
	_currentFile = fileName;

	QString fName = fileName.split("/").last();
	kb()->parent()->setWindowTitle(fName + " - CPPiano");
	_unsavedChanges = false;
}

void RecPlay::Save() 
{
	if(this->_currentFile=="") {
		SaveAs();
		return;
	}
	writeFile(_currentFile);
}

void RecPlay::SaveAs() {
	if(_registration.isEmpty()) {
		QMessageBox::information(0,"Error","No registration found. Nothing to save.");
		return;
	}
	QString fileName = QFileDialog::getSaveFileName(0, "Save As", "", "CPPiano Recorded Files (*.crf)");
	if(fileName=="") {
		QMessageBox::information(0,"Error","No filename specified.");
		return;
	}
	if(fileName.right(4)!=".crf")
		fileName += ".crf";

	writeFile(fileName);
}

void RecPlay::writeFile(QString fileName) 
{
	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(0,"Error",file.errorString());
		return;
	}
	QTextStream out(&file);

	QString fName = fileName.split("/").last();
	kb()->parent()->setWindowTitle(fName + " - CPPiano");

	for (auto i : _registration.keys())
	{
		out << _registration[i].first->name() << " " 
			<< _registration[i].first->frequency() << " " 
			<< i << " " 
			<< _registration[i].second << "\n";
	}

	_currentFile = fileName;
	_unsavedChanges = false;
	file.close();	
}

bool RecPlay::recording()  
{
	return this->_recording;
}

bool RecPlay::playing()  
{
	return this->_playing;
}

int RecPlay::status()
{
	if(_registration.isEmpty() && !recording())
		return 0; //Nothing Recorded
	if(recording())
		return 1; //Recording
	if(this->_paused) {
		if(_startRec->isEnabled())
			return 2; //paused recording 
		else
			return 3; //paused play
	}
	if(playing())
		return 4; //playing
	return 0;
}

void RecPlay::send(Key* key, std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point stop) {
	if(!recording() || !key->valid())
		return;
	std::chrono::duration<double,std::milli> start_relative = start - _start;
	std::chrono::duration<double,std::milli> stop_relative = stop - _start;
	int tstart = start_relative.count();
	int tduration = stop_relative.count() - start_relative.count();
	_registration.insert(tstart, qMakePair(key, tduration));
}
