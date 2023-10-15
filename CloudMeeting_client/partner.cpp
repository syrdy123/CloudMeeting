#include "partner.h"

Partner::Partner(QWidget *parent, quint32 ip):QLabel(parent),m_ip(ip)
{

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    w = static_cast<QWidget*>(this->parent())->size().width();
    this->setPixmap(QPixmap::fromImage(QImage(":/myImage/1.jpg").scaled(w-10, w-10)));
    this->setFrameShape(QFrame::Box);

    this->setStyleSheet("border-width: 1px; border-style: solid; border-color:rgba(0, 0 , 255, 0.7)");

    this->setToolTip(QHostAddress(m_ip).toString());
}


void Partner::mousePressEvent(QMouseEvent *)
{
    emit sendip(m_ip);
}

void Partner::setpic(QImage img)
{
    this->setPixmap(QPixmap::fromImage(img.scaled(w-10, w-10)));
}
