#include <QApplication>
#include <QTextCodec>

#include "widget.h"
#include "screen.h"

int main(int argc, char* argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QApplication app(argc, argv);
    Screen::init();

    Widget w;
    w.show();

    return app.exec();
}
