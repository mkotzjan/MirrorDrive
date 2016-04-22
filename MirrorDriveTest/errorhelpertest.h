#ifndef ERRORHELPERTEST_H
#define ERRORHELPERTEST_H

#include <QObject>
#include <QtTest/QTest>
#include <errorhelper.h>

class ErrorHelperTest : public QObject
{
    Q_OBJECT
public:
    explicit ErrorHelperTest(QObject *parent = 0);

signals:

private slots:
    void Constructor();
    void setState();
    void setMessage();
    void getState();
    void getMessage();
};

#endif // ERRORHELPERTEST_H
