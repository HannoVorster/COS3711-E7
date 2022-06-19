#include "filewriter.h"

#include <QFile>
#include <QTextStream>

FileWriter::FileWriter(QString fName)
    : fileName(fName)
{
}

bool FileWriter::write(QString str) const
{
    QFile outFile(fileName);
    if (!outFile.open(QIODevice::WriteOnly)) {
            return false;
    }

    QTextStream out(&outFile);
    out << str;
    out.flush();  // Flush buffer to ensure all data written to file

    outFile.close();

    return true;
}

