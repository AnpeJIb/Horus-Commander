#include "expected_strings.h"

ExpectedStrings::ExpectedStrings()
{
}

void ExpectedStrings::append(const QString &str)
{
    m_expectedStrings.append(str);
}

QString ExpectedStrings::current() const
{
    return ((m_expectedStrings.count()>0) && (m_expectedStringIndex<m_expectedStrings.count()))
           ? m_expectedStrings.at(m_expectedStringIndex)
           : QString();
}

void ExpectedStrings::succedOne()
{
    m_expectedStringIndex++;
}

void ExpectedStrings::reset()
{
    m_expectedStrings.clear();
    resetIndex();
}

void ExpectedStrings::resetIndex()
{
    m_expectedStringIndex=0;
}

bool ExpectedStrings::areAllSucceded()
{
    return m_expectedStringIndex == m_expectedStrings.count();
}
