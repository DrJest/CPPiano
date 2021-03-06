#include "options.hpp"
#include "mainWindow.hpp"
#include "keyboard.hpp"
#include <QFileDialog>
#include <QShortcut>
#include <QComboBox>

options::options(QWidget* mw)
{
	this->_mainwindow = (mainWindow*) mw;
	this->_keyboard = (keyBoard*) _mainwindow->getMainWidget();
	this->_layout = _keyboard->getLayout();
}

void options::spawnOptionsWindow()
{
	QWidget *wdg = new QWidget;
	this->_main = wdg;
	QTabWidget* tabs = new QTabWidget(wdg);

	tabs->setMinimumWidth(250);
	tabs->setMinimumHeight(250);

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
    connect(def, SIGNAL(toggled(bool)), this, SLOT(setDefaultLayout(bool)));

	QRadioButton *com = new QRadioButton("Complete", layoutTab);
    layoutL->addWidget(com);
    connect(com, SIGNAL(toggled(bool)), this, SLOT(setCompleteLayout(bool)));

	QRadioButton *cus = new QRadioButton("Custom", layoutTab);
    layoutL->addWidget(cus);
    connect(cus, SIGNAL(toggled(bool)), this, SLOT(toggleLayoutCustomField(bool)));
    
    
    QWidget* cusFieldBox = new QWidget(layoutTab);
    	QHBoxLayout* cusLayoutL = new QHBoxLayout();
	    QLineEdit* cusField = new QLineEdit(cusFieldBox);
	    QPushButton* cusFieldBrowse = new QPushButton("Browse");
	    connect(cusFieldBrowse, SIGNAL(clicked()), this, SLOT(cusBrowse()));
	    cusField->setText(_layout);
	    cusField->setMinimumWidth(240);
	    cusLayoutL->addWidget(cusField);
	    cusLayoutL->addWidget(cusFieldBrowse);
    	cusFieldBox->setLayout(cusLayoutL);
	    this->_cusLayoutFieldBox = cusFieldBox;
    layoutL->addWidget(cusFieldBox);
   	cusFieldBox->hide();


    if(_layout=="assets/default.keys")
        def->setChecked(true);
    else if (_layout=="assets/complete.keys")
        com->setChecked(true);
    else {
        cus->setChecked(true);
        cusFieldBox->show();
    }

    layoutL->addWidget(new QLabel("Ottava Minima"));
    QComboBox* minOct = new QComboBox(layoutTab);
    for(int i=1; i<8;++i)
        minOct->addItem(QString::number(i));
    minOctave = _keyboard->getMinOct();
    minOct->setCurrentIndex(_keyboard->getMinOct()-1);
    connect(minOct, SIGNAL(currentIndexChanged(int)), this, SLOT(setMinOctave(int)));
    layoutL->addWidget(minOct);

    layoutL->addWidget(new QLabel("Ottava Massima"));
    QComboBox* maxOct = new QComboBox(layoutTab);
    for(int i=1; i<8;++i)
        maxOct->addItem(QString::number(i));
    maxOctave = _keyboard->getMaxOct();
    maxOct->setCurrentIndex(_keyboard->getMaxOct()-1);
    connect(maxOct, SIGNAL(currentIndexChanged(int)), this, SLOT(setMaxOctave(int)));
    layoutL->addWidget(maxOct);

    // needed to reset stretch
   	layoutL->addWidget(new QLabel(""));

    layoutTab->setLayout(layoutL);
    /*** END LAYOUT TAB ***/

    /*** TIMBRE TAB ***/
    QWidget* timbreTab = new QWidget(tabs);
    tabs->addTab(timbreTab, "Timbre");
    QLabel *timbreLabel = new QLabel("Choose Timbre");
    QLineEdit* timbre = new QLineEdit(timbreTab);
    this->_timbre = timbre;
    timbre->setText(_keyboard->getTimbre());
    QLabel* timbrExplication = new QLabel("Inserisci nella casella la serie dei coefficenti che determinano il timbro.\nCiascun coefficente sara' assegnato all'armonica corrispondente. \nE.G. il violino e' determinato da:\n1-1-0.45-0.5-1-0.02-0.025-0.03\n E.G. il pianoforte e' dato da:\n1-0.2-0.25-0.1-0.1-0-0-0");
    timbrExplication->setTextInteractionFlags(Qt::TextSelectableByMouse);
    
    QVBoxLayout* timbreL = new QVBoxLayout();
    timbreL->addWidget(timbreLabel);
    timbreL->addWidget(timbre);
    timbreL->addWidget(timbrExplication);
    //impedisce agli altri widget di espandersi per riempire il genitore
    timbreL->addStretch();

    timbreTab->setLayout(timbreL);
    /*** END TIMBRE TAB ***/

    /*** HELP TAB ***/
    QWidget* helpTab = new QWidget(tabs);
    tabs->addTab(helpTab, "Informations");
    QVBoxLayout* helpL = new QVBoxLayout();
    QLabel *helpLabel = new QLabel(keyBoard::Usage());
    helpL->addWidget(helpLabel);
    helpTab->setLayout(helpL);
    /*** END HELP TAB ***/

    // OK BUTTON
    QPushButton* ok = new QPushButton("OK", wdg);
    optionsL->addWidget(ok,2,2);
    connect(ok, SIGNAL(clicked()), this, SLOT(saveOptions()));

    // CANCEL BUTTON
    QPushButton* canc = new QPushButton("Cancel", wdg);
    optionsL->addWidget(canc,2,3);
    connect(canc, SIGNAL(clicked()), wdg, SLOT(close()));
    new QShortcut(Qt::Key_Escape, wdg, SLOT(close()));

    wdg->setLayout(optionsL);
	wdg->show();
}

void options::setMinOctave(int currentindex) {
    this->minOctave = currentindex+1;
}

void options::setMaxOctave(int currentindex) {
    this->maxOctave = currentindex+1;
}

void options::toggleLayoutCustomField(bool checked) {
	if(checked) 
		_cusLayoutFieldBox->show();
	else
		_cusLayoutFieldBox->hide();
}

void options::saveOptions()
{
	if(_cusLayoutFieldBox->isVisible ())
		this->_layout = _cusLayoutFieldBox->findChild<QLineEdit*>()->text();
	this->setLayout(this->_layout);
	_keyboard->timbre(_timbre->text());
	_main->close();
}

void options::cusBrowse()
{
	QString fileName = QFileDialog::getOpenFileName(this->_mainwindow, 
													"Open File",
                                                 	".",
                                                 	"CPPiano Layout Files (*.keys)");
	_cusLayoutFieldBox->findChild<QLineEdit*>()->setText(fileName);
}

void options::setLayout(QString layout)
{
	keyBoard* k = this->_keyboard = (keyBoard*) _mainwindow->getMainWidget();
	keyBoard* n = this->_keyboard = new keyBoard(_mainwindow);
	n->generate(minOctave, maxOctave, layout, k->getGeNote(), k->getGenFreq());
	n->draw();
	_mainwindow->setMainWidget<keyBoard*>(n);
	_mainwindow->setCentralWidget(n);
	//n->grabKeyboard();
	
    int wHeight = 28 + (_mainwindow->getToolbars() * 30) + ((keyBoard*)(_mainwindow->getMainWidget()))->height();
    int wWidth  = ((keyBoard*)(_mainwindow->getMainWidget()))->width();
    _mainwindow->resize(wWidth, wHeight);
}

void options::setDefaultLayout(bool doit) {
	if(doit)
		this->_layout = "assets/default.keys";
}

void options::setCompleteLayout(bool doit) {
	if(doit)
		this->_layout = "assets/complete.keys";
}