#include "timer.h"
#include "ui_timer.h"

#include <QtDebug>

Timer::Timer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    this->setUp();
    this->workerThread->start();
}

void Timer::setUp()
{
    this->workerThread = new QThread();
    this->timer = new TimerThread();
    this->timer->moveToThread(this->workerThread);
    this->running = false;
    this->finished = true;
    ui->label->setText(STR_ZERO_TIME);

    connect(ui->pushButton, &QPushButton::released, this, &Timer::startTimer);
    connect(this, &Timer::timerStart, this->timer, &TimerThread::startTiming);
    connect(this, &Timer::timerStop, this->timer, &TimerThread::stopTiming);
    connect(this->timer, &TimerThread::sigTimeout, this, &Timer::update);

}

Timer::~Timer()
{
    delete ui;
}

void Timer::startTimer()
{
    //first run or when a run is finished
    if (this->finished) {
        int minutes = ui->spinBox->value();
        emit timerStart(true, minutes);
        this->ui->pushButton->setText("Stop");
        this->running = true;
        this->finished = false;
    } else {
        //countdown is running?
        if (this->running) {
            emit timerStop();
            this->ui->pushButton->setText("Resume");
            this->running = false;
        } else {
            emit timerStart(false, 0);
            this->ui->pushButton->setText("Stop");
            this->running = true;
        }
    }
}

void Timer::update(QString time)
{
    this->ui->label->setText(time);

    //end of time, stop timer, set button text
    if (time.compare("") == 0) {
       this->resetTimer();
    }
}

void Timer::resetTimer()
{
    emit timerStop();
    this->running = false;
    this->finished = true;
    this->ui->pushButton->setText("Start");
    this->ui->label->setText(STR_ZERO_TIME);
}

void Timer::on_pushButton_2_clicked()
{
    this->resetTimer();
}
