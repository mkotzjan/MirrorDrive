#include "errorhelpertest.h"

ErrorHelperTest::ErrorHelperTest(QObject *parent) :
    QObject(parent)
{
}

void ErrorHelperTest::Constructor()
{
    ErrorHelper errorHelper;
    QVERIFY2(errorHelper.getMessage() == "", "Message should be empty");
    QVERIFY2(errorHelper.getState() == 0, "State should be 0");
}

void ErrorHelperTest::setState()
{
    ErrorHelper errorHelper;
    errorHelper.setState(1);
    QVERIFY2(errorHelper.getState() == 1, "State should be 1");
}

void ErrorHelperTest::setMessage()
{
    ErrorHelper errorHelper;
    errorHelper.setMessage("Test");
    QVERIFY2(errorHelper.getMessage() == "Test", "Message should be 'Test'");
}

void ErrorHelperTest::getState()
{
    ErrorHelper errorHelper;
    errorHelper.setState(1);
    QVERIFY2(errorHelper.getState() == 1, "State should be 1");
}

void ErrorHelperTest::getMessage()
{
    ErrorHelper errorHelper;
    errorHelper.setMessage("Test");
    QVERIFY2(errorHelper.getMessage() == "Test", "Message should be 'Test'");
}
