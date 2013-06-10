#ifndef SRTFILEPARSER_H
#define SRTFILEPARSER_H

#include "srtentry.h"
#include <QString>
#include <QList>

class QStringList;

class SrtFileParser
{
public:

    // Constructor and destructor
    SrtFileParser(QString fn);
    ~SrtFileParser();

    // clean attributes Method
    void cleanSrtFileParser();

    // set Methods
    void setFileName(QString fn) {fileName = fn; }
    void setErrorFlag() {isErrorSet = true; }
    void setFileParsed() {isFileParsed = true; }
    void setError (QString e) {errorString += e; setErrorFlag(); }

    // get Methods
    QString getFileName () const {return fileName; }
    QString getErrorString () const {return errorString; }
    bool hasError() const {return isErrorSet; }
    bool isParsed() const {return isFileParsed; }

    // parse File Method
    bool parseFile (QList<SrtEntry> & srtEntryList);
    bool parseFile (QList<SrtEntry> & srtEntryList, QString fn)
        {cleanSrtFileParser(); setFileName(fn); return parseFile(srtEntryList); }



protected:

    // read File into Memory
    QStringList readFileIntoMemory();

    // parse File lines (inside Memory)
    QList<SrtEntry> parseLines(QStringList & sl);



private:
    QString fileName;
    bool isFileParsed;
    bool isErrorSet;
    QString errorString;

};

#endif // SRTFILEPARSER_H
