#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QString>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QThread>

#define DEFAULT "/documentation/"
#define LICENSE "/documentation/license.txt"

class FileParser
{
public:
    FileParser();
    void ReadDefault(void);
    void ReadLicense(void);
private:
    QString path;
private:
    void read(QFile* file);
    void pause(void);
    void clear(void);
};

#endif // FILEPARSER_H
