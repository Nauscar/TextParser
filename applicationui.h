#ifndef APPLICATIONUI_H
#define APPLICATIONUI_H

#include <QObject>
#include <QTextStream>
#include <QDateTime>

#include "fileparser.h"
#include "countdown.h"

class ApplicationUI : QObject
{
    Q_OBJECT
public:
    ApplicationUI();
    virtual ~ApplicationUI();
    void Display(void);
private:
    FileParser* fileParser;
    Countdown* countdown;
private slots:
    void countdownFinished(void);
private:
    void showText(void);
    void showCountdown(QDateTime final);
};

#endif // APPLICATIONUI_H
