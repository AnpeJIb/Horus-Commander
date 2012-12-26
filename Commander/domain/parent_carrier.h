#ifndef PARENT_CARRIER_H
#define PARENT_CARRIER_H

#include <QtCore>

namespace Domain {

template <class T> class ParentCarrier
{
public:
    ParentCarrier() : m_parent(NULL){}
    virtual T* parent() = 0;
    virtual void setParent(T* parent) = 0;

protected:
    T* m_parent;
};

}

#endif // PARENT_CARRIER_H
