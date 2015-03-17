#include "exceptions.h"
#include "utils.h"

#include <QFile>

QString readAllText(QString filePath)
{
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw BadFile(filePath);
    }

    QTextStream in(&file);
    return in.readAll();
}
