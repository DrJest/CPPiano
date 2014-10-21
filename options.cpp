#include "options.hpp"
#include "mainWindow.hpp"
#include "keyboard.hpp"


options::options(QWidget* mw)
{
	this->_mainwindow = (mainWindow*) mw;
	this->_keyboard = (keyBoard*) _mainwindow->getMainWidget();
}

void options::spawnOptionsWindow()
{
	QWidget *wdg = new QWidget;
	this->_main = wdg;
	QTabWidget* tabs = new QTabWidget(wdg);

	tabs->setMinimumWidth(250);
	tabs->setMinimumHeight(220);

    QGridLayout *optionsL = new QGridLayout();
    optionsL->addWidget(tabs, 0, 0, 2, 0, Qt::AlignTop);

	/*** LAYOUT TAB ***/
	QWidget* layoutTab = new QWidget(tabs);
	tabs->addTab(layoutTab, "Layout");

    QVBoxLayout *layoutL = new QVBoxLayout();

	QLabel *layoutLabel = new QLabel("Choose Layout");
    layoutLabel->setMaximumHeight(20);
    layoutL->addWidget(layoutLabel);

	QRadioButton *def = new QRadioButton("Default", layoutTab);
    layoutL->addWidget(def);

	QRadioButton *com = new QRadioButton("Complete", layoutTab);
    layoutL->addWidget(com);

	QRadioButton *cus = new QRadioButton("Custom", layoutTab);
    layoutL->addWidget(cus);
    connect(cus, SIGNAL(toggled(bool)), this, SLOT(toggleLayoutCustomField(bool)));
    
    QWidget* cusFieldBox = new QWidget(layoutTab);
	    QLabel* cusFieldLabel = new QLabel("\n\nInserisci il percorso assoluto \no relativo all'eseguibile",cusFieldBox);
	    QLineEdit* cusField = new QLineEdit(cusFieldBox);
	    cusField->setText(_keyboard->getLayout());
	    cusField->setMinimumWidth(240);
	    this->_cusLayoutFieldBox = cusFieldBox;
    layoutL->addWidget(cusFieldBox);
   	cusFieldBox->hide();

    // needed to reset stretch
   	layoutL->addWidget(new QLabel(""));

	if(_keyboard->getLayout()=="assets/default.keys")
		def->setChecked(true);
	else if (_keyboard->getLayout()=="assets/complete.keys")
		com->setChecked(true);
	else {
		cus->setChecked(true);
		cusFieldBox->show();
	}


    layoutTab->setLayout(layoutL);
    /*** END LAYOUT TAB ***/


    /*** TIMBRE TAB ***/
    QWidget* timbreTab = new QWidget(tabs);
    tabs->addTab(timbreTab, "Timbre");
    QVBoxLayout* timbreL = new QVBoxLayout();
    QLabel *timbreLabel = new QLabel("Choose Timbre");
    timbreLabel->setMaximumHeight(20);
    timbreL->addWidget(timbreLabel);

    QRadioButton* piano = new QRadioButton("Piano", timbreTab);
    timbreL->addWidget(piano);

    QRadioButton* violin = new QRadioButton("Violin", timbreTab);
    timbreL->addWidget(violin);

    timbreL->addWidget(new QLabel(""));

	if(_keyboard->timbre()==1)
		piano->setChecked(true);
	else 
		violin->setChecked(true);

    timbreTab->setLayout(timbreL);
    /*** END TIMBRE TAB ***/

    // OK BUTTON
    QPushButton* ok = new QPushButton("OK", wdg);
    optionsL->addWidget(ok,2,2);
    connect(ok, SIGNAL(clicked()), this, SLOT(saveOptions()));

    // CANCEL BUTTON
    QPushButton* canc = new QPushButton("Cancel", wdg);
    optionsL->addWidget(canc,2,3);
    connect(canc, SIGNAL(clicked()), wdg, SLOT(close()));

    wdg->setLayout(optionsL);
	wdg->show();
}

void options::toggleLayoutCustomField(bool checked) {
	if(checked)
		_cusLayoutFieldBox->show();
	else
		_cusLayoutFieldBox->hide();
}

void options::saveOptions()
{

	_main->close();
}

void options::setLayout(QString layout)
{
	keyBoard* k = this->_keyboard = (keyBoard*) _mainwindow->getMainWidget();
	keyBoard* n = new keyBoard(_mainwindow);

	n->generate(k->getMinOct(), k->getMaxOct(), layout, k->getGeNote(), k->getGenFreq());
	n->draw();
	_mainwindow->setMainWidget<keyBoard*>(n);
	_mainwindow->setCentralWidget(n);
	n->grabKeyboard();
	
    int wHeight = 28 + (_mainwindow->getToolbars() * 30) + ((keyBoard*)(_mainwindow->getMainWidget()))->height();
    int wWidth  = ((keyBoard*)(_mainwindow->getMainWidget()))->width();
    _mainwindow->resize(wWidth, wHeight);
}