#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QObject>
#include <QTimer>
#include <QTime>

#define STR_ZERO_TIME "00:00:00"
#define INTERLEAVE 100

class TimerThread : public QObject
{
    Q_OBJECT
public:
    explicit TimerThread(QObject *parent = nullptr);
    void init();

signals:
    void sigTimeout(QString);

public slots:
    void startTiming(bool firstRun, int minutes);
    void stopTiming();

private slots:
    void timeout();

private:
    QTimer *timer;
    QTime time;
};

#endif // TIMERTHREAD_H
