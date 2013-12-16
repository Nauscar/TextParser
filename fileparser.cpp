#include "fileparser.h"

FileParser::FileParser()
{
    path = QDir::currentPath();
}

void FileParser::ReadDefault()
{
    QDir defaultDocs(path + DEFAULT);
    QStringList fileNames = defaultDocs.entryList();
    fileNames.pop_front(); //Remove "." directory
    fileNames.pop_front(); //Remove ".." directory
    fileNames.removeAt(fileNames.indexOf(QRegExp("license.txt")));
    foreach(QString fileName, fileNames)
    {
        QFile* file = new QFile(path + DEFAULT + fileName);
        read(file);
        pause();
    }
}

void FileParser::ReadLicense()
{
    QFile* file = new QFile(path + LICENSE);
    read(file);
}

void FileParser::read(QFile* file)
{
    if(!file->open(QIODevice::ReadOnly))
    {
        qCritical() << "Critical Error: " << file->errorString() << endl;
        file->deleteLater();
        return;
    }
    QTextStream fileIn(file);
    QTextStream qtOut(stdout);
    while(!fileIn.atEnd())
    {
        QString line = fileIn.readLine();
        foreach(QChar character, line)
        {
            qtOut << character;
            QThread::msleep(10);
            qtOut.flush();
        }
        qtOut << endl;
    }
    file->close();
    file->deleteLater();
}

void FileParser::pause()
{
    QTextStream qtOut(stdout);
    QTextStream qtIn(stdin);
    qtOut << "\nPress enter to continue..." << endl;
    qtIn.readLine();
    clear();
}

void FileParser::clear()
{
#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif
    system(CLEAR);
}
