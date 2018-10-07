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
    this->timeout = 0;
    this->running = false;
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    ui->label->setText(QString("00:00:00"));
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(startTimer()));
}

Timer::~Timer()
{
    delete ui;
}

void Timer::startTimer()
{
    if (!this->running) {
        int labValue = ui->label->text().toInt();
        if (labValue == 0) {
            this->timeout = ui->spinBox->value();
        }
        this->timer->start(100);
        this->running = true;
        ui->pushButton->setText("Stop");
    } else {
        this->timer->stop();
        this->running = false;
        ui->pushButton->setText("Resume");
    }
}

void Timer::update()
{
    if (this->time == QTime(0, this->timeout, 0, 0)) {
        this->timer->stop();
        ui->label->setText("00:00:00");
        return;
    }
    this->time = this->time.addMSecs(100);
    ui->label->setText(this->time.toString("mm:ss:z"));
}
