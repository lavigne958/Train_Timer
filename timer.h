#ifndef TIMER_H
#define TIMER_H

#include <QMainWindow>
#include <QThread>
#include <QTime>

#include "timerthread.h"

namespace Ui {
class Timer;
}

class Timer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();

signals:
    void timerStart();
    void timerStop();

private:
    Ui::Timer *ui;
    QTime time; //displaying the time
    TimerThread *timer;
    QThread *workerThread;
    bool running;

private slots:
    void update();
    void startTimer();
};

#endif // TIMER_H
