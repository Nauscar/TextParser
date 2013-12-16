#include "applicationui.h"

ApplicationUI::ApplicationUI()
{
    fileParser = new FileParser();
}

ApplicationUI::~ApplicationUI()
{
    delete fileParser;
}

void ApplicationUI::Display()
{
    fileParser->ReadDefault();
    fileParser->ReadLicense();
}
