#ifndef EXPECTED_STRINGS_H
#define EXPECTED_STRINGS_H

#include <QString>
#include <QList>

class ExpectedStrings
{
public:
    ExpectedStrings();

    void append(const QString& str);
    QString current() const;
    void succedOne();
    void reset();
    void resetIndex();
    bool areAllSucceded();

private:
    QList<QString> m_expectedStrings;
    int m_expectedStringIndex;
};

#endif // EXPECTED_STRINGS_H
