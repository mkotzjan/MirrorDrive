#include "errorhelper.h"

// ____________________________________________________________________________
ErrorHelper::ErrorHelper()
{
    state = 0;
    message = "";
}

// ____________________________________________________________________________
void ErrorHelper::setState(int s)
{
    this->state = s;
}

// ____________________________________________________________________________
void ErrorHelper::setMessage(QString m)
{
    this->message = m;
}

// ____________________________________________________________________________
int ErrorHelper::getState()
{
    return this->state;
}

// ____________________________________________________________________________
QString ErrorHelper::getMessage()
{
    return this->message;
}
