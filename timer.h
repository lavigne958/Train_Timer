#ifndef TIMER_H
#define TIMER_H

#include <QMainWindow>
#include <QThread>
#include <QTime>
#include <QElapsedTimer>

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
    void timerStart(bool firstRun, int minutes);
    void timerStop();

private:
    Ui::Timer *ui;
    TimerThread *timer;
    QThread *workerThread;
    bool running;
    bool finished;

    void setUp();

private slots:
    void update(QString);
    void startTimer();
};

#endif // TIMER_H
