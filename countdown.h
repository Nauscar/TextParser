#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QTextStream>
#include <qmath.h>

#include "delay.h"

#define DAY_IN_SECONDS 86400
#define HOUR_IN_SECONDS 3600
#define MINUTE_IN_SECONDS 60

class Countdown : public QObject
{
    Q_OBJECT
public:
    Countdown(QDateTime final);
    void Display(void);
signals:
    void tZero(void);
private:
    QDateTime final;
    bool isCounting;
private:
    void clear(void);
    QString getCountdown(QDateTime countdown);
};

#endif // COUNTDOWN_H
