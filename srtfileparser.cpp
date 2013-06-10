#include "srtfileparser.h"
#include <QStringList>
#include <QFile>
#include <QDebug>

SrtFileParser::SrtFileParser(QString fn)
    : fileName(fn),
      isFileParsed(false),
      isErrorSet(false)
{
}



SrtFileParser::~SrtFileParser()
{
    cleanSrtFileParser();
}



void SrtFileParser::cleanSrtFileParser()
{
    fileName.clear();
    isFileParsed = false;
    isErrorSet = false;
    errorString.clear();
}




bool SrtFileParser::parseFile(QList<SrtEntry> & srtEntryList)
{
    qWarning() << "Parsing" + fileName;
    qWarning() << fileName.size();

    if (fileName.size()<2)
    {
        setError(QString("Empty File Name to Parse!"));
        return hasError();
    }

    QStringList lines = readFileIntoMemory();
    if (hasError())
    {
        lines.clear();
        return hasError();
    }

    srtEntryList = parseLines(lines);
    lines.clear();

    if (hasError())
    {
        srtEntryList.clear();
        return hasError();
    }

    qWarning() << srtEntryList.size();

    return hasError();

}



QStringList SrtFileParser::readFileIntoMemory()
{
    QStringList lines;
    QFile * fd = new QFile(fileName);


    if (!fd->exists())
    {
        setError( QString(fileName + " not found!") );
        return lines;
    }

    if (!fd->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        setError( QString(fileName + " is not readable!" ) );
        return lines;
    }

    while (!fd->atEnd())
    {
        lines.push_back( fd->readLine());
    }

    fd->close();
    delete fd;

    return lines;
}


QList<SrtEntry> SrtFileParser::parseLines(QStringList & sl)
{

    /*
      EXAMPLE OF ONE SRT entry

        5                               <-- entry index
        00:01:09,697 --> 00:01:11,058   <-- entry times
        - So!                           <-- entry text
        - So.                           <-- entry text

    */

    enum enumStatus {ENTRY_INDEX, ENTRY_TIMES, ENTRY_TEXT};

    enumStatus lineStatus = ENTRY_INDEX;
    unsigned int currentEntryIndex;
    SrtEntry entry;
    QList<SrtEntry> srtEntryVec;

    for (int i=0; i<sl.count(); i++)
    {
        QString currentString = sl[i].remove(QRegExp("[\n\r]"));


        // processig of the entry index number
        if (lineStatus == ENTRY_INDEX)
        {
            //remotion of 2 white lines (entry w/o text)
            if (currentString.size() == 0)
                continue;

            currentEntryIndex = currentString.toUInt();
            lineStatus = ENTRY_TIMES;

            if (currentEntryIndex == 9999)
                break;
            else
                entry.setSequenceNumber(currentEntryIndex);

        }


        // processing of the time line
        else if (lineStatus == ENTRY_TIMES)
        {
            //00:00:52,780 --> 00:00:56,779
            int n_times = currentString.count(QRegExp("[0-9]\{2}:[0-9]\{2}:[0-9]\{2},[0-9]\{3}"));
            if (n_times != 2)
            {
                setError( QString("Line ") + QString::number(i) + QString(" does not contain a start-stop time\n") +
                               QString("Dump: ") + currentString );
                break;
            }

            int h,m,s,ms;
            float timeStart, timeEnd;


            int idx = currentString.indexOf(QRegExp("[0-9]\{2}:[0-9]\{2}:[0-9]\{2},[0-9]\{3}"), 0);

            h = (currentString.mid(idx+0,2)).toInt();
            m = (currentString.mid(idx+3,2)).toInt();
            s = (currentString.mid(idx+6,2)).toInt();
            ms = (currentString.mid(idx+9,3)).toInt();

            timeStart = h * 3600.0f + \
                        m * 60.0f + \
                        s * 1.0f + \
                        ms * 0.001;

            entry.setTimeStart(timeStart);

            idx = currentString.indexOf(QRegExp("[0-9]\{2}:[0-9]\{2}:[0-9]\{2},[0-9]\{3}"), 12);

            h = (currentString.mid(idx+0,2)).toInt();
            m = (currentString.mid(idx+3,2)).toInt();
            s = (currentString.mid(idx+6,2)).toInt();
            ms = (currentString.mid(idx+9,3)).toInt();

            timeEnd = h * 3600.0f + \
                      m * 60.0f + \
                      s * 1.0f + \
                      ms * 0.001;

            entry.setTimeEnd(timeEnd);

            lineStatus = ENTRY_TEXT;
        }

        // processing of the text string (could be multiline)
        else if (lineStatus == ENTRY_TEXT)
        {
            // final empty line
            if (currentString.count(QRegExp("[0-9a-zA-Z]")) == 0)
            {

                entry.removeRegExp(QString("[\n\r]"));
                srtEntryVec.push_back(entry);


                // clean the local var & reset the enum
                entry.clearSrtEntry();
                lineStatus = ENTRY_INDEX;
            }
            else
            {
                entry.addText(currentString + QString(" "));
            }

        }


    }


    return srtEntryVec;
}
