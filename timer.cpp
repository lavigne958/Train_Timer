#include "timer.h"
#include "ui_timer.h"

#include <QtDebug>

Timer::Timer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    this->timer = new QTimer(this);
    this->time = QTime(0, 0, 0);
    this->running = false;
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    ui->label->setText(this->time.toString("mm:ss:z"));
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(startTimer()));
}

Timer::~Timer()
{
    delete ui;
}

void Timer::startTimer()
{
    //first run or when a run is finished
    if (this->time == QTime(0,0)) {
        int minutes = ui->spinBox->value();
        this->time.setHMS(0, minutes, 0);
        this->timer->start(100);
        this->ui->pushButton->setText("Stop");
        this->running = true;
    } else {
        //countdown is running?
        if (this->running) {
            this->timer->stop();
            this->ui->pushButton->setText("Resume");
            this->running = false;
        } else {
            this->timer->start();
            this->ui->pushButton->setText("Stop");
            this->running = true;
        }
    }
}

void Timer::update()
{
    int rest = this->time.msecsSinceStartOfDay();
    if (rest <= 0) {
        //countdown is finished, stop the timer
        this->timer->stop();
        this->running = false;
        //force time to be set to 0 so startTimer() can start again for sure.
        this->time = QTime::fromMSecsSinceStartOfDay(0);
        this->ui->pushButton->setText("Start");
        return;
    }
    rest -= 100; //100 milliseconds past
    this->time = QTime::fromMSecsSinceStartOfDay(rest);
    this->ui->label->setText(this->time.toString("mm:ss:z"));
}
