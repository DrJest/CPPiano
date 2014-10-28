#include "recplay.hpp"
#include "key.hpp"
#include "keyboard.hpp"

RecPlay::RecPlay(QWidget* parent) 
{
	this->_kb = (keyBoard*)parent;
}

void RecPlay::startRec()
{
	QTextStream o(stdout);
	if(recording())
		return;
	this->_start = std::chrono::high_resolution_clock::now();
	_recording = true;
	_kb->updateTopBar();
}

void RecPlay::stopRec() 
{
	if(!recording())
		return;
	this->_recording = false;
	_kb->updateTopBar();
}

void RecPlay::Pause() 
{

}

void RecPlay::Stop() 
{

} 

void RecPlay::Play()
{

}

bool RecPlay::recording()  
{
	return this->_recording;
}

void RecPlay::send(Key* key, std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point stop) {
	QTextStream o(stdout);
	if(!recording())
		return;
	std::chrono::duration<double> start_relative = start - _start;
	std::chrono::duration<double> stop_relative = stop - _start;

	o << key->name() << " " << start_relative.count() << " " << stop_relative.count() << "\n";
}
