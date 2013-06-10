#ifndef SRTENTRYVECTOR_H
#define SRTENTRYVECTOR_H

#include <QObject>
#include <QList>
#include "srtentry.h"


class SrtEntryVector : public QObject
{
    Q_OBJECT
public:

    // Constructors and destructor
    explicit SrtEntryVector(QObject *parent = 0);
    ~SrtEntryVector();

    // clean
    void clean();

    // get Methods
    QList<SrtEntry>& getEntryList() {return entryList; }
    const SrtEntry getEntryListElement(int i) const {return entryList.at(i); }
    const SrtEntry getCurrentEntry() const {return entryList.at(currentIndex); }
    int getEntryListSize() const {return entryList.size(); }
    int getCurrentIndex() const {return currentIndex; }
    bool getIsSubActive() const {return isSubActive; }

    // set Methods
    void entryListCreator(QList<SrtEntry>& el) {entryList.clear(); entryList << el; }
    void setCurrentIndex(int i) {currentIndex = i; }
    void increaseCurrentIndex() {currentIndex++; }
    void setIsSubActive(bool isa) {isSubActive = isa; }


    // film length [seconds] (the time_end of the last element in the qlist)
    float getFilmLength() const {return entryList.last().getTimeEnd(); }

    // check if the currentIndex is valid
    bool isCurrentIndexValid() const {return (currentIndex >= 0 && currentIndex<getEntryListSize())? true: false; }

    // search the subtitle (if so) to be visualized during time T
    int searchSubInTime(float t);
    int searchSubInTimeFromCurrent(float t);


signals:
    void sendCurrentStringSignal(QString s);

public slots:
    void syncroTimeAndSub(float time);


private:
    int currentIndex;
    bool isSubActive;
    QList<SrtEntry> entryList;

};

#endif // SRTENTRYVECTOR_H
