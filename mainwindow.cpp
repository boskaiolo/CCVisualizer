#include "mainwindow.h"


#include "coreapplication.h"
#include <cmath>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    playButton  = new QPushButton("Play");
    pauseButton = new QPushButton("Pause");
    text = new QLabel("Label");
    elapsedTime = new QLabel("--:--:--:----");

    connect(playButton, SIGNAL(clicked()), this, SIGNAL(playButtonPushed()));
    connect(pauseButton, SIGNAL(clicked()), this, SIGNAL(pauseButtonPushed()));


    QFont textFont = text->font();
    textFont.setBold(true);
    textFont.setPointSizeF(textFont.pointSizeF()*1.3f);
    text->setFont(textFont);


    playButton->setStyleSheet("color: blue;"
                              "background-color: yellow;"
                              "selection-color: yellow;"
                              "selection-background-color: blue;");

    pauseButton->setStyleSheet("color: blue;"
                               "background-color: yellow;"
                               "selection-color: yellow;"
                               "selection-background-color: blue;");


    QHBoxLayout * hLayout = new QHBoxLayout();
    QVBoxLayout * vLayout = new QVBoxLayout(this);

    hLayout->addWidget(playButton, Qt::AlignVCenter);
    hLayout->addWidget(elapsedTime, Qt::AlignHCenter);
    hLayout->addWidget(pauseButton, Qt::AlignVCenter);


    vLayout->addWidget(text, 0, Qt::AlignCenter);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);

    //this->setAttribute(Qt::WA_TranslucentBackground);

    QPalette p(this->palette());
        // Set background colour to black
        p.setColor(QPalette::Background, QColor(255,0,0,100));
        this->setPalette(p);



   ca = new CoreApplication(this);



   connect(this, SIGNAL(playButtonPushed()), ca->metronome, SLOT(startTimer()));
   connect(this, SIGNAL(pauseButtonPushed()), ca->metronome, SLOT(stopTimer()));
   connect(ca->metronome, SIGNAL(timerTimeoutSignal(float)), ca->srtev, SLOT(syncroTimeAndSub(float)));
   connect(ca->srtev, SIGNAL(sendCurrentStringSignal(QString)), this, SLOT(updateTextSlot(QString)));
   connect(ca->metronome, SIGNAL(timerTimeoutSignal(float)), this, SLOT(updateElapsedTimeSlot(float)));
   ca->srtev->syncroTimeAndSub(0.0f);

}



MainWindow::~MainWindow()
{
    delete playButton;
    delete pauseButton;
    delete text;
    delete elapsedTime;
    delete ca;
}


void MainWindow::updateTextSlot(QString str)
{
    text->setText(str);
}

void MainWindow::updateElapsedTimeSlot(float time)
{
    elapsedTime->setText("");

    int h = floor(time/3600);
    time -= 3600.0f* floor(time/3600);

    int m = floor(time/60);
    time -= 60.0f* floor(time/60);

    float s = time;

    QString t   = QString::number(h) + QString(":") + \
                  QString::number(m) + QString(":") + \
                  QString::number(s, 3, 3) ;

    elapsedTime->setText(t);
}
