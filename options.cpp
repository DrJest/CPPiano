#include "options.hpp"
#include "mainWindow.hpp"
#include "keyboard.hpp"

options::options(QWidget* mw)
{
	this->_mainwindow = (mainWindow*) mw;
}

void options::setDefaultLayout() 
{
	keyBoard* k = this->_keyboard = (keyBoard*) _mainwindow->getMainWidget();
	keyBoard* n = new keyBoard(_mainwindow);

	n->generate(k->getMinOct(), k->getMaxOct(), "assets/default.keys", k->getGeNote(), k->getGenFreq());
	n->draw();
	_mainwindow->setMainWidget<keyBoard*>(n);
	_mainwindow->setCentralWidget(n);
	n->grabKeyboard();
	
    int wHeight = 28 + (_mainwindow->getToolbars() * 30) + ((keyBoard*)(_mainwindow->getMainWidget()))->height();
    int wWidth  = ((keyBoard*)(_mainwindow->getMainWidget()))->width();
    _mainwindow->resize(wWidth, wHeight);
}

void options::setCompleteLayout() 
{
	keyBoard* k = this->_keyboard = (keyBoard*) _mainwindow->getMainWidget();
	keyBoard* n = new keyBoard(_mainwindow);
	
	n->generate(k->getMinOct(), k->getMaxOct(), "assets/complete.keys", k->getGeNote(), k->getGenFreq());
	n->draw();
	_mainwindow->setMainWidget<keyBoard*>(n);
	_mainwindow->setCentralWidget(n);
	n->grabKeyboard();
	
    int wHeight = 28 + (_mainwindow->getToolbars() * 30) + ((keyBoard*)(_mainwindow->getMainWidget()))->height();
    int wWidth  = ((keyBoard*)(_mainwindow->getMainWidget()))->width();
    _mainwindow->resize(wWidth, wHeight);
}