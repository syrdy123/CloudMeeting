#ifndef PARTNER_H
#define PARTNER_H

#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QHostAddress>

class Partner : public QLabel
{
    Q_OBJECT

public:
    Partner(QWidget * parent = nullptr, quint32 = 0);
    void setpic(QImage img);

private:
    quint32 m_ip;

    void mousePressEvent(QMouseEvent *ev) override;
    int w;

signals:
    void sendip(quint32); //发送ip
};

#endif // PARTNER_H
