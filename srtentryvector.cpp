#include "srtentryvector.h"

#include <QDebug>

SrtEntryVector::SrtEntryVector(QObject *parent) :
    QObject(parent), currentIndex(-1), isSubActive(false)
{
}

SrtEntryVector::~SrtEntryVector()
{
    this->clean();
    currentIndex = -1;
    isSubActive = false;
}

void SrtEntryVector::clean()
{
    entryList.clear();
}


int SrtEntryVector::searchSubInTime(float t)
{
    int index = -1;

    for (int i = 0; i<getEntryListSize(); i++)
    {
        if (getEntryListElement(i).isTimeIncluded(t))
        {
            index = i;
            break;
        }
    }

    return index;

}

int SrtEntryVector::searchSubInTimeFromCurrent(float t)
{
    int index = -1;

    for (int i = currentIndex; i<getEntryListSize(); i++)
    {
        if (getEntryListElement(i).isTimeIncluded(t))
        {
            index = i;
            break;
        }
    }

    return index;

}

void SrtEntryVector::syncroTimeAndSub(float time)
{
    int index = searchSubInTime(time);

    // No Sub right now
    if (index == -1)
    {
        setIsSubActive(false);
        emit sendCurrentStringSignal(QString(""));
    }
    // Sub Right Now
    else
    {
        setIsSubActive(true);
        setCurrentIndex(index);

        emit sendCurrentStringSignal(getCurrentEntry().getText());
    }
}
