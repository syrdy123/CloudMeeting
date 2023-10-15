#include "screen.h"


int Screen::width = -1;
int Screen::height = -1;


void Screen::init()
{
    QScreen *s = QGuiApplication::primaryScreen();


    Screen::width = s->geometry().width();
    Screen::height = s->geometry().height();

}
