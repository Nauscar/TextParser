#include "encryption.h"
#include <math.h>

Encryption::Encryption(int mode, int keySize)
{
    this->mode = mode;
    this->keySize = keySize;

    //unsigned long key[8];
    //int i;
    //for (i=0;i<keySize/32;i++)	/* select key bits */
    //    key[i]=0x10003 * rand();
    //SetKey(key);
}

Encryption::~Encryption()
{
}

void Encryption::SetKey(unsigned long (&key)[8])
{
    int i;
    srand((unsigned) time(NULL));
    if (makeKey(&ki,DIR_ENCRYPT,keySize,NULL) != TRUE){
        qDebug() << "'dummy' setup for a 128-bit key" << endl;
    }
    if (cipherInit(&ci,mode,NULL) != TRUE){
        qDebug() << "'dummy' setup for cipher" << endl;
    }
    for (i=0;i<keySize/32;i++)	/* select key bits */
        ki.key32[i] = key[i];
    reKey(&ki);					/* run the key schedule */
}

QByteArray Encryption::Encrypt(QString data)
{
    int  i;
    if (mode != MODE_ECB)		/* set up random iv (if needed)*/
    {
        for (i=0;i<sizeof(iv);i++)
            iv[i]=(BYTE) rand();
        memcpy(ci.iv32,iv,sizeof(ci.iv32));	/* copy the IV to ci */
    }
    int byteCnt = (BLOCK_SIZE/8)*((floor(2 * (data.toStdString().length())/(BLOCK_SIZE/8))) + 1);
    BYTE plainText[byteCnt];
    BYTE cipherText[byteCnt];
    strcpy((char*)plainText, data.toStdString().c_str());

    /* encrypt the bytes */
    if (blockEncrypt(&ci,&ki, plainText,byteCnt*8,cipherText) != byteCnt*8){
        qDebug() << "encryption error" << endl;
        return NULL;
    }

    QByteArray cipherArray;
    for(int i = 0; i < byteCnt; i++){
        cipherArray.append(cipherText[i]);
        //qDebug() << "cipherText[" <<i<< "]: " << hex << cipherText[i];
    }
    return cipherArray;
}

QString Encryption::Decrypt(QByteArray data)
{
    int byteCnt = data.length();
    BYTE decryptOut[byteCnt];
    BYTE cipherText[byteCnt];

    for(int i = 0; i < byteCnt; i++){
        cipherText[i] = (BYTE)data.at(i);
        //qDebug() << hex << cipherText[i];
    }

    // decrypt the bytes
    if (mode != MODE_ECB)
        memcpy(ci.iv32,iv,sizeof(ci.iv32));

    if (blockDecrypt(&ci,&ki,cipherText,byteCnt*8,decryptOut) != byteCnt*8){
        qDebug() << "decryption error" << endl;
        return NULL;
    }
    return QString((char*)decryptOut);
}
