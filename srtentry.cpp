#include "srtentry.h"

#include <iostream>
#include <sstream>

using namespace std;



std::ostream& operator<< (std::ostream& out, const SrtEntry &se)
{
    return out << "[" << se.getSequenceNumber() << "] " \
               << se.getTimeStart() << " -> " << se.getTimeEnd() << " ::" \
               << se.getText().toStdString().c_str();
}

QString SrtEntry::toString() const
{
    QString out;
    out = QString("[") + QString::number(getSequenceNumber()) + QString("] ") + \
          QString::number(getTimeStart()) + QString(" -> ") + QString::number(getTimeEnd()) + QString(" ::") + \
          getText();
    return out;
}
