#include "applicationui.h"

ApplicationUI::ApplicationUI() {}

ApplicationUI::~ApplicationUI()
{
    delete fileParser;
    delete countdown;
}

void ApplicationUI::Display()
{
    QDateTime currTime = QDateTime::currentDateTime();
    QDateTime giftTime = QDateTime::fromString("2013-12-25T00:00:00", Qt::ISODate);
    if(currTime.toMSecsSinceEpoch() >= giftTime.toMSecsSinceEpoch()){
        showText();
    } else {
        showCountdown(giftTime);
    }
}

void ApplicationUI::showText()
{
    fileParser = new FileParser();
    fileParser->EncryptFiles();

    fileParser->ReadDefault();
    fileParser->ReadLicense();
}

void ApplicationUI::showCountdown(QDateTime finalTime)
{
    countdown = new Countdown(finalTime);
    connect(countdown, SIGNAL(tZero()), this, SLOT(countdownFinished()));
    countdown->Display();
}

void ApplicationUI::countdownFinished()
{
    showText();
}
