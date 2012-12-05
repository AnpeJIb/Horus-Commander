#ifndef STRTEST_H
#define STRTEST_H

#include <QObject>

class StrTest: public QObject
{
    Q_OBJECT
public:
    explicit StrTest(QObject *parent = 0);

private slots:
    void testRmDoubleSymbols();
};

#endif // STRTEST_H
