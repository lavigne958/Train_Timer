#include "timerthread.h"

#include <QDebug>
#include <QElapsedTimer>

TimerThread::TimerThread(QObject *parent):
    QObject(parent)
{
    this->timer = new QTimer(this);
    this->timer->setTimerType(Qt::PreciseTimer);
}

void
TimerThread::startTiming(bool firstRun, int minutes)
{
    if (firstRun) {
        this->timer->setInterval(INTERLEAVE);
        connect(this->timer, &QTimer::timeout, this, &TimerThread::timeout);
        this->time.setHMS(0, minutes, 0, 0); //explicitly set to 0
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
