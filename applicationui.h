#ifndef APPLICATIONUI_H
#define APPLICATIONUI_H

#include <QTextStream>
#include "fileparser.h"

class ApplicationUI
{
public:
    ApplicationUI();
    ~ApplicationUI();
    void Display(void);
private:
    FileParser* fileParser;
private:
};

#endif // APPLICATIONUI_H
