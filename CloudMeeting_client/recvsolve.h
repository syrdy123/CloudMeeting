#ifndef RECVSOLVE_H
#define RECVSOLVE_H

#include <QThread>
#include <QMutex>
#include <QMetaType>
#include <QDebug>
#include <QMutexLocker>

#include "netheader.h"
/*
 * 接收线程
 * 从接收队列拿取数据
 */
class RecvSolve : public QThread
{
    Q_OBJECT
public:
    RecvSolve(QObject *par = NULL);
    void run() override;

private:
    QMutex m_lock;
    bool m_isCanRun;

signals:
    void datarecv(MESG *);
public slots:
    void stopImmediately();
};

#endif // RECVSOLVE_H
