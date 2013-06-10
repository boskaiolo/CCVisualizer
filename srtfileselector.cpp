#include "srtfileselector.h"

#include <QObject>
#include <QWidget>
#include <QFileDialog>

SrtFileSelector::SrtFileSelector()
{
}


QString SrtFileSelector::openFileDialog(QWidget * parent)
{
    QString fileName = QFileDialog::getOpenFileName(parent, QObject::tr("Open Subtitle file"), QDir::homePath(), QObject::tr("SRT File (*.srt)"));
    return fileName;
}
