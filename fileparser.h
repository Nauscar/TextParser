#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QString>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QThread>

#include "encryption.h"

#define DEFAULT "/documentation/"
#define ENCRYPTED "/encrypt/"
#define LICENSE "/documentation/license.txt"

class FileParser
{
public:
    FileParser();
    ~FileParser();
    void EncryptFiles();
    void ReadDefault(void);
    void ReadLicense(void);
private:
    Encryption* encrypt;
    static unsigned long key[8];
    QString path;
private:
    void encryptFile(QFile* file, QString fileName);
    QByteArray encryptText(QString text);
    QString decryptText(QByteArray text);
    void read(QFile* file);
    void pause(void);
    void clear(void);
};

#endif // FILEPARSER_H
