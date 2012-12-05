#ifndef FILETEST_H
#define FILETEST_H

#include <QObject>

class FileTest: public QObject
{
    Q_OBJECT
public:
    explicit FileTest(QObject *parent = 0);

private slots:
    void testRmDoubleSymbolsInFile();
};

#endif // FILETEST_H
