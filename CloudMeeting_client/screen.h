#ifndef SCREEN_H
#define SCREEN_H

#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QDebug>

class Screen
{
public:
    static int width;
    static int height;

    static void init();
};

#endif // SCREEN_H
