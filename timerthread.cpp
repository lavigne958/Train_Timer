#include "timerthread.h"

#include <QDebug>

TimerThread::TimerThread(QObject *parent):
    QObject(parent)
{
    this->timer = new QTimer(this);
}

void
TimerThread::startTiming(bool firstRun)
{
    if (firstRun) {
        qDebug() << "start timer";
        this->timer->setInterval(INTERLEAVE);
        connect(this->timer, SIGNAL(timeout()), this, SLOT(timeout()));
        this->i = 0;
    }

    this->timer->start();
}

void
TimerThread::stopTiming()
{
    qDebug() << "stop timing";
    this->timer->stop();
}

void
TimerThread::timeout()
{
    qDebug() << "timer timed out" << i++;
    emit sigTimeout();
}
