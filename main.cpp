#include <QDesktopWidget>
#include <QWidget>
#include <QIcon>
#include "mainWindow.hpp"

int main(int argc, char *argv[])
{    
    QApplication app(argc, argv);  
    
    mainWindow window;
    
    QDesktopWidget * dt = QApplication::desktop();
    
    window.addKey(0,"a4");
    window.addKey(40,"b4");
    window.addKey(80,"c5");
    window.addKey(120,"d5");
    window.addKey(160,"e5");
    window.addKey(200,"f5");
    window.addKey(240,"g5");
    window.addKey(280,"a5");
    window.addKey(320,"b5");
    window.addKey(360,"c6");
    
    window.addKey(25,"a4#");
    window.addKey(105,"c5#");
    window.addKey(145,"d5#");
    window.addKey(225,"f5#");
    window.addKey(265,"g5#");
    window.addKey(305,"a5#");
    
    //set Height and Width of the main window
    int wHeight = 200;
    int wWidth  = 400;
    
    //centering the window
    int x,y;
    x = ( dt->width() - wWidth ) / 2;
    y = ( dt->height() - wHeight ) / 2;
       
    
    window.resize(wWidth, wHeight);
    window.move( x , y );    
    window.setWindowTitle("CPPiano");
    window.setWindowIcon(QIcon("assets/icon.png"));   
    window.show();

    return app.exec();
}
