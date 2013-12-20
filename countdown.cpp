#include "countdown.h"

Countdown::Countdown(QDateTime final)
{
    isCounting = true;
    this->final = final;
}

void Countdown::Display()
{
    QDateTime countdown = QDateTime::currentDateTime();
    while(isCounting)
    {
        QString formatted = getCountdown(countdown);
        QTextStream qtOut(stdout);
        qtOut << formatted;
        Delay::Sleep(1);
        countdown = countdown.addSecs(1);
        clear();
    }
    emit tZero();
}

QString Countdown::getCountdown(QDateTime current)
{
    qint64 seconds = current.secsTo(final);
    if(seconds <= 0) {
        isCounting = false;
        return "";
    }
    qint64 days = qFloor(seconds / DAY_IN_SECONDS);
    seconds -= days * DAY_IN_SECONDS;
    qint64 hours = qFloor(seconds / HOUR_IN_SECONDS);
    seconds -= hours * HOUR_IN_SECONDS;
    qint64 minutes = qFloor(seconds / MINUTE_IN_SECONDS);
    seconds -= minutes * MINUTE_IN_SECONDS;
    QString formatted = QString::number(days) + "d " \
            + QString::number(hours) + "h " \
            + QString::number(minutes) +  "m " \
            + QString::number(seconds) + "s";
    return formatted;
}

void Countdown::clear()
{
#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif
    system(CLEAR);
}
