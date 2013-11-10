#include <QDesktopWidget>
#include <QWidget>
#include <QIcon>

#include "mainWindow.hpp"
#include "keyboard.hpp"

int main(int argc, char *argv[])
{    
    QApplication app(argc, argv);  
    
    mainWindow * window = new mainWindow;
    
    QDesktopWidget * dt = QApplication::desktop();

    keyBoard * kb = new keyBoard(window);
    
    window->setMainWidget<keyBoard*>(kb);
    
    kb->addKey("a4");
    kb->addKey("b4");
    kb->addKey("c5");
    kb->addKey("d5");
    kb->addKey("e5");
    kb->addKey("f5");
    kb->addKey("g5");
    kb->addKey("a5");
    kb->addKey("b5");
    kb->addKey("c6");
    
    kb->addKey("a4#");
    kb->addKey("c5#");
    kb->addKey("d5#");
    kb->addKey("f5#");
    kb->addKey("g5#");
    kb->addKey("a5#");
    
    kb->draw();
    //set Height and Width of the main window
    int wHeight = 230;
    int wWidth  = 400;
    
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
