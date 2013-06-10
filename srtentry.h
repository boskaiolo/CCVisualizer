
#ifndef SRTENTRY_H
#define SRTENTRY_H

#include <QString>
#include <QRegExp>

#include <iostream>


class SrtEntry
{
public:

    // Constructor and Destructor
    SrtEntry(float ts = 0.0f, float te = 0.0f) : sequenceNumber(0), timeStart(ts), timeEnd(te) {}
    ~SrtEntry() {text.clear();}


    // Set the SRT entry
    void setSRTEntry(int sn, float ts, float te, QString t)
        { sequenceNumber = sn; timeStart = ts; timeEnd = te; text = t; }

    void clearSrtEntry() {sequenceNumber = 0; timeStart = 0.0f; timeEnd = 0.0f; text.clear(); }

    void setSequenceNumber(unsigned int sn) { sequenceNumber = sn; }
    void setTimeStart(float ts) { timeStart = ts; }
    void setTimeEnd(float te) { timeEnd = te; }
    void setTimes(float ts, float te) {setTimeStart(ts); setTimeEnd(te); }
    void setText(QString s) { text = s; }
    void addText(QString s) { text += s; }


    // Get members
    unsigned int getSequenceNumber() const { return sequenceNumber; }
    float getTimeStart() const { return timeStart; }
    float getTimeEnd() const { return timeEnd; }
    QString getText() const { return text; }


    // Check if the query time is included the current SrtEntry
    bool isTimeIncluded(float time) const {return (time >= timeStart && time <= timeEnd); }


    // Remove (RegExp) from the text
    void removeRegExp(QString regExp) {text.remove(QRegExp(regExp)); }

    // Print operators
    friend std::ostream& operator<< (std::ostream &out, const SrtEntry &v);
    QString toString() const;



private:
    unsigned int sequenceNumber;
    float timeStart;
    float timeEnd;
    QString text;

};

#endif // SRTENTRY_H
