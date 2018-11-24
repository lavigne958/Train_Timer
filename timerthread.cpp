#include "timerthread.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QMetaMethod>

TimerThread::TimerThread(QObject *parent):
    QObject(parent)
{
    this->timer = new QTimer(this);
    this->timer->setTimerType(Qt::PreciseTimer);
}

void
TimerThread::init()
{
    this->timer->setInterval(INTERLEAVE);
    connect(this->timer, &QTimer::timeout, this, &TimerThread::timeout);
}

void
TimerThread::startTiming(bool reset, int minutes)
{
    if (reset) {
        this->time = QTime(0,minutes,0); //explicitly set to 0
    }

    this->timer->start();
}

void
TimerThread::stopTiming()
{
    this->timer->stop();
}

void
TimerThread::timeout()
{
    int ms = this->time.msecsSinceStartOfDay();
    ms -= INTERLEAVE;
    this->time = QTime::fromMSecsSinceStartOfDay(ms);
    QString toDisplay = this->time.toString("mm:ss:z");
    emit sigTimeout(toDisplay);
}
