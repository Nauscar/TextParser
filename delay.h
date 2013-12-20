#ifndef DELAY_H
#define DELAY_H

#include <QThread>

class Delay
{
public:
    Delay();
    static void Sleep(unsigned long secs){QThread::sleep(secs);}
};

#endif // DELAY_H
