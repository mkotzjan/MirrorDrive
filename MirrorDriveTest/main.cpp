#include <QtTest/QTest>
#include "errorhelpertest.h"

int main()
{
    ErrorHelperTest eht;

    QTest::qExec(&eht);

    return 0;
}
