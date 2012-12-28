#ifndef DOMAIN_HELPER_H
#define DOMAIN_HELPER_H

namespace Domain
{

template<class T> class DomainHelper
{
public:
    virtual T* clone() const = 0;
    virtual ~DomainHelper(){}
};

}

#endif // DOMAIN_HELPER_H
