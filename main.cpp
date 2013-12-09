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

    kb->generate(3,5)->draw();
    // set Height and Width of the main window
    int wHeight = 28 + (window->getToolbars() * 30) + ((keyBoard*)(window->getMainWidget()))->height();
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
