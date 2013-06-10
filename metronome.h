#ifndef METRONOME_H
#define METRONOME_H

#include <QObject>

class QTimer;


class Metronome : public QObject
{
    Q_OBJECT
public:
    explicit Metronome(QObject *parent = 0);
    ~Metronome();

    // set Methods
    void setTimerInterval(int ti) {timerInterval = ti; }
    void setIsTimerOn(bool to) {isTimerOn = to; }
    void setElapsedTime(float et) {elapsedTime = et; }
    void increaseElapsedTime(float increment) {elapsedTime += increment; }
    void setTimer(int timerInterval = 1);


    // get Methods
    int getTimerInterval() const {return timerInterval; }
    bool getIsTimerOn() const {return isTimerOn; }
    float getElapsedTime() const {return elapsedTime; }


    // start QTimer
    void startQTimer();

signals:
    void timerTimeoutSignal(float elapsedTime);

public slots:
    // slots for buttons
    void stopTimer();
    void startTimer();

private slots:
    // slot for qtimer
    void qtimerTimeoutSlot();

private:
    QTimer * timer;
    int timerInterval; // [ms]
    float elapsedTime;
    bool isTimerOn;

};

#endif // METRONOME_H
