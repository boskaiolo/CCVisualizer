#include "metronome.h"

#include <QTimer>
#include <QDebug>

Metronome::Metronome(QObject *parent) :
    QObject(parent), timer(NULL), timerInterval(0), elapsedTime(0.0f), isTimerOn(false)
{
}


Metronome::~Metronome()
{
    if (timer) delete timer;
}


void Metronome::setTimer(int _timerInterval)
{
    this->timerInterval = _timerInterval;
    if (timer == NULL)
    {
        timer = new QTimer(this);
        timer->setSingleShot(false);
        connect (timer, SIGNAL(timeout()), this, SLOT(qtimerTimeoutSlot()));
    }

    timer->setInterval(timerInterval);
    isTimerOn = false;
    elapsedTime = 0.0f;
}


void Metronome::startQTimer()
{
    isTimerOn = true;
    timer->start();
}

void Metronome::qtimerTimeoutSlot()
{
    elapsedTime += (0.001f * timerInterval);
    emit timerTimeoutSignal(elapsedTime);
}

void Metronome::startTimer()
{
    if (isTimerOn == false)
    {
        qWarning() << "Timer on";
        isTimerOn = true;
        timer->start();
    }
    else
    {
        qWarning() << "QTimer is already on";
    }
}

void Metronome::stopTimer()
{
    if (isTimerOn == true)
    {
        qWarning() << "Timer off";
        timer->stop();
        isTimerOn = false;
    }
    else
    {
        qWarning() << "QTimer is already off";
    }
}
