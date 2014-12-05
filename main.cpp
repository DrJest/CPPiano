#include <QDesktopWidget>
#include <QWidget>
#include <QIcon>
#include <QString>
#include <string>
#include "mainWindow.hpp"
#include "keyboard.hpp"
#include <iostream> 
#include <unistd.h>

int main(int argc, char *argv[])
{
    QString layoutFile = "assets/default.keys";
    int opt;
    int min = 2, max = 5;
    std::string usage = keyBoard::Usage().toUtf8().constData();
    while ( (opt = getopt(argc, argv, "hvk:b:t:")) != -1 ) {  
        switch ( opt ) {
            case 'v':
                std::cout << "CPPiano v1.05 - Licensed under GNU/LGPL v3.0" << std::endl;
                return 0;
                break;
            case 'h':
                std::cout << "Usage:" << std::endl;
                std::cout << usage << std::endl;
                return 0;
                break;
            case 'k':
                layoutFile = QString::fromStdString(optarg);
                break;
            case 'b':
                min =  atoi(optarg);
                min = qMin(1, min);
                break;
            case 't':
                max = atoi(optarg);
                max = qMax(7, max);
                break;
            case '?':
                return 1;
                break;
        }
    }
    QApplication app(argc, argv);  
    mainWindow * window = new mainWindow;
    
    QDesktopWidget * dt = QApplication::desktop();

    keyBoard * kb = new keyBoard(window);
    
    window->setMainWidget<keyBoard*>(kb);
    
    kb->generate(min,max,layoutFile);
    
    kb->draw();
    // set Height and Width of the main window
    int wHeight = 20 + (window->getToolbars() * 30) + ((keyBoard*)(window->getMainWidget()))->height();
    int wWidth  = ((keyBoard*)(window->getMainWidget()))->width();
    
    //centering the window
    int x,y;
    x = ( dt->width() - wWidth ) / 2;
    y = ( dt->height() - wHeight ) / 2;
       
    
    window->resize(wWidth, wHeight);
    window->move( x , y );    
    window->setWindowTitle("CPPiano");
    window->setWindowIcon(QIcon("assets/icon.png"));   
    window->draw()->show();

    return app.exec();
}
