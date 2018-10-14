#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QObject>
#include <QTimer>

#define INTERLEAVE 100

class TimerThread : public QObject
{
    Q_OBJECT
public:
    explicit TimerThread(QObject *parent = nullptr);

signals:
    void sigTimeout();

public slots:
    void startTiming(bool firstRun);
    void stopTiming();

private slots:
    void timeout();

private:
    QTimer *timer;
    int i;

};

#endif // TIMERTHREAD_H
