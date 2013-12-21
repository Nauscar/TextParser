#include "fileparser.h"

unsigned long FileParser::key[8] = {
    378815420,
    238758577,
    1269162735,
    465261361,
    1915508353,
    1001566998,
    1439367518,
    1273291692
};

FileParser::FileParser()
{
    encrypt = new Encryption(MODE_ECB, 256);
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
    if(fileNames.length() == 0){
        return;
    }
    fileNames.pop_front(); //Remove "." directory
    fileNames.pop_front(); //Remove ".." directory
    foreach(QString fileName, fileNames)
    {
        QFile* file = new QFile(path + ENCRYPTED + fileName);
        encryptFile(file, fileName.left(fileName.length() - 3));
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

    QByteArray encryptedData = encryptText(fileIn.readAll());
    encryptedFile->write(encryptedData);

    file->close();
    file->deleteLater();
    encryptedFile->close();
    encryptedFile->deleteLater();
}

QByteArray FileParser::encryptText(QString text)
{
    return encrypt->Encrypt(text);
}

QString FileParser::decryptText(QByteArray text)
{
    QByteArray input;
    input.append(text);
    return encrypt->Decrypt(input);
}

void FileParser::ReadDefault()
{
    QDir defaultDocs(path + DEFAULT);
    QStringList fileNames = defaultDocs.entryList();
    if(fileNames.length() == 0){
        return;
    }
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

    QTextStream qtOut(stdout);
    QString text = decryptText(file->readAll());
    foreach(QChar character, text)
    {
        qtOut << character;
        QThread::msleep(10);
        qtOut.flush();
    }
    qtOut << endl;

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
