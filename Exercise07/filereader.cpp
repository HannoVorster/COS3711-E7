#include "filereader.h"

#include <QFile>
#include <QTextStream>

FileReader::FileReader(QString fName)
    : fileName(fName)
{
}

QString FileReader::read() const
{
    QFile inFile(fileName);
    if (!inFile.open(QIODevice::ReadOnly)) {
        return "";
    }

    QTextStream inStream(&inFile);
    QString inStr(inFile.readAll());

    inFile.close();
    return inStr;
}
