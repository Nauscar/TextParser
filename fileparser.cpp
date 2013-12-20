#include "fileparser.h"

FileParser::FileParser()
{
    encrypt = new Encryption(MODE_ECB, 256);
    key = new unsigned long[8];
    key[0] = 378815420;
    key[1] = 238758577;
    key[2] = 1269162735;
    key[3] = 465261361;
    key[4] = 1915508353;
    key[5] = 1001566998;
    key[6] = 1439367518;
    key[7] = 1273291692;
    path = QDir::currentPath();
}

FileParser::~FileParser()
{
    delete encrypt;
}

void FileParser::EncryptFiles()
{
    encrypt->SetKey(key);
    QDir encryptDocs(path + ENCRYPTED);
    QStringList fileNames = encryptDocs.entryList();
    fileNames.pop_front(); //Remove "." directory
    fileNames.pop_front(); //Remove ".." directory
    foreach(QString fileName, fileNames)
    {
        QFile* file = new QFile(path + ENCRYPTED + fileName);
        encryptFile(file, fileName);
    }
}

void FileParser::encryptFile(QFile* file, QString fileName)
{
    QFile* encryptedFile = new QFile(path + DEFAULT + fileName);
    if(!file->open(QIODevice::ReadOnly))
    {
        qCritical() << "Critical Error: " << file->errorString() << endl;
        file->deleteLater();
        return;
    }
    if(!encryptedFile->open(QIODevice::WriteOnly))
    {
        qCritical() << "Critical Error: " << encryptedFile->errorString() << endl;
        encryptedFile->deleteLater();
        return;
    }
    QTextStream fileIn(file);
    QTextStream encryptedOut(encryptedFile);
    while(!fileIn.atEnd())
    {
        QString line = encryptLine(fileIn.readLine());
        encryptedOut << line;
    }
    file->close();
    file->deleteLater();
    encryptedFile->close();
    encryptedFile->deleteLater();
}

QString FileParser::encryptLine(QString line)
{
    return encrypt->Encrypt(QByteArray(line.toStdString().c_str()));
}

QString FileParser::decryptLine(QString line)
{
    return encrypt->Decrypt(QByteArray(line.toStdString().c_str()));
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
        QString line = decryptLine(fileIn.readLine());
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
