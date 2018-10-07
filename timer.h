#ifndef TIMER_H
#define TIMER_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

namespace Ui {
class Timer;
}

class Timer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();

private:
    Ui::Timer *ui;
    QTimer *timer;
    QTime time;
    int timeout;
    bool running;

private slots:
    void update();
    void startTimer();
};

#endif // TIMER_H
