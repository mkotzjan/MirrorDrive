#ifndef ERRORHELPER_H
#define ERRORHELPER_H

#include <QString>

class ErrorHelper
{
    // Represents the state:
    // 0 - No issue
    // 1 - Question
    // 2 - Error
    int state;
    QString message;

public:
    ErrorHelper();

    // Setter
    void setState(int s);
    void setMessage(QString m);

    // Getter
    int getState();
    QString getMessage();

};

#endif // ERRORHELPER_H
