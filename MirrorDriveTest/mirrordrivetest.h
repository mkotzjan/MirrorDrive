#ifndef MIRRORDRIVETEST_H
#define MIRRORDRIVETEST_H

#include <QObject>
#include <QtTest/QTest>

class MirrorDriveTest : public QObject
{
    Q_OBJECT
public:
    explicit MirrorDriveTest(QObject *parent = 0);

signals:

private slots:
    void mirrorDriveTestTest();
};

#endif // MIRRORDRIVETEST_H
