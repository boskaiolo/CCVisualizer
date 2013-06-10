#ifndef SRTFILESELECTOR_H
#define SRTFILESELECTOR_H

class QWidget;
#include <QString>

class SrtFileSelector
{
public:
    SrtFileSelector();
    QString openFileDialog(QWidget * parent = 0);

};

#endif // SRTFILESELECTOR_H
