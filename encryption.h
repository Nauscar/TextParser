#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <QString>
#include <QDebug>
#include "twofish/AES.H"

class Encryption
{
public:
    Encryption(int mode, int keySize);
    ~Encryption();
    void SetKey(unsigned long (&key)[8]);
    QByteArray Encrypt(QString data);
    QString Decrypt(QByteArray data);

private:
    int mode; //MODE_ECB || MODE_CBC
    int keySize;
    keyInstance    ki;			/* key information, including tables */
    cipherInstance ci;			/* keeps mode (ECB, CBC) and IV */
    BYTE iv[BLOCK_SIZE/8];
};

#endif // ENCRYPTION_H
