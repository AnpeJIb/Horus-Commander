#include "str_test.h"
#include "str.h"

#include <iostream>
using namespace std;

StrTest::StrTest(QObject *parent)
    : QObject(parent)
{
}

void StrTest::testRmDoubleSymbols()
{
    QString src = "\\\\mega\\\\value";
    cout << "source: " << qPrintable(src) << endl;

    char res[100];
    STR::rmDoubleSymb((char*)src.toStdString().c_str(), res, '\\');

    cout << "result: " << res << endl;
}
