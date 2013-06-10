#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QWidget>
#include <QString>
#include "coreapplication.h"


class QLabel;
class QPushButton;




class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateTextSlot(QString str);
    void updateElapsedTimeSlot(float time);

signals:
    void playButtonPushed();
    void pauseButtonPushed();

private:
    QPushButton * playButton;
    QPushButton * pauseButton;
    QLabel * text;
    QLabel * elapsedTime;
    CoreApplication * ca;

};

#endif // MAINWINDOW_H
