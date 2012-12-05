#include "filetest.h"

#include <QSettings>
#include <QFile>

#include "file.h"
#include "file_util.h"

#include <iostream>
using namespace std;

FileTest::FileTest(QObject *parent)
    : QObject(parent)
{
}

void FileTest::testRmDoubleSymbolsInFile()
{
    QString fPath = "test.ini";

    QSettings setts(fPath, QSettings::IniFormat);
    setts.setIniCodec("utf8");

    setts.setValue("some0/key0", "some value0");
    setts.setValue("some0/key1", "\\some\\value1");
    setts.setValue("some0/key2", "some value2");
    setts.setValue("some0/key3", "some value3");
    setts.setValue("some1/key0", "some value0");
    setts.sync();

    cout << "Original file:" << endl;
    printFile(fPath);

    rmDoubleSymbInFile(fPath, '\\');

    cout << endl << "Processed file:" << endl;
    printFile(fPath);

    QFile::remove(fPath);
}
