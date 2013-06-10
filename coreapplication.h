#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include "srtfileparser.h"
#include "srtentry.h"
#include "srtentryvector.h"
#include "metronome.h"

#include <QWidget>


class CoreApplication
{
public:
    CoreApplication(QWidget * mainWin);
    ~CoreApplication();

public:
    SrtFileParser * sfp;
    QString srtFileName;
    SrtEntryVector * srtev;
    //QList<SrtEntry> srtEntryList;
    Metronome * metronome;
};

#endif // COREAPPLICATION_H
