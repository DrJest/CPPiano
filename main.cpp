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
    
    window->setMainWidget((QWidget*)kb);
    
    kb->addKey(0,"a4");
    kb->addKey(40,"b4");
    kb->addKey(80,"c5");
    kb->addKey(120,"d5");
    kb->addKey(160,"e5");
    kb->addKey(200,"f5");
    kb->addKey(240,"g5");
    kb->addKey(280,"a5");
    kb->addKey(320,"b5");
    kb->addKey(360,"c6");
    
    kb->addKey(25,"a4#");
    kb->addKey(105,"c5#");
    kb->addKey(145,"d5#");
    kb->addKey(225,"f5#");
    kb->addKey(265,"g5#");
    kb->addKey(305,"a5#");
    
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
    window->draw();
    window->show();

    return app.exec();
}
