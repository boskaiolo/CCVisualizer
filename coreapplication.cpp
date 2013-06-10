#include "coreapplication.h"
#include "srtfileselector.h"
#include "mainwindow.h"

#include <QWidget>
#include <QDebug>


CoreApplication::CoreApplication(QWidget * mainWin) :
    sfp(NULL), srtev(NULL), metronome(NULL)
{

    SrtFileSelector * sfs = new SrtFileSelector();
    srtFileName = sfs->openFileDialog(mainWin);

    sfp = new SrtFileParser(srtFileName);

    QList<SrtEntry> srtEntryList;
    bool readError = sfp->parseFile(srtEntryList);
    if (!readError)
    {
        for (int i=0; i<srtEntryList.size(); i++)
            ;//qWarning() << srtEntryList.at(i).toString();
    }
    else
    {
        qWarning() << sfp->getErrorString();
        return;
    }

    srtev = new SrtEntryVector(mainWin);
    srtev->entryListCreator(srtEntryList);
    srtEntryList.clear();


    metronome = new Metronome(mainWin);
    metronome->setTimer(50);

}

CoreApplication::~CoreApplication()
{
    if (sfp) delete sfp;
    if (srtev) delete srtev;
    if (metronome) delete metronome;
}
