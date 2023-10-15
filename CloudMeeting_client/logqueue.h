#ifndef LOGQUEUE_H
#define LOGQUEUE_H

#include <QThread>
#include <QMutex>
#include <queue>
#include <QDebug>

#include "netheader.h"


class LogQueue : public QThread
{
private:
    void run() override;

    QUEUE_DATA<Log> log_queue;
    FILE *logfile;
    QMutex m_lock;
    bool m_isCanRun;

public:
    explicit LogQueue(QObject *parent = nullptr);
    void stopImmediately();
    void pushLog(Log*);
};

#endif // LOGQUEUE_H
