#ifndef XML_DAO_H
#define XML_DAO_H

#include <QString>
#include <QDomElement>
#include <QDomDocument>

#include "generic_domain.h"
#include "generic_dao.h"

namespace Dao {

class XmlDaoBase
{
public:
    virtual ~XmlDaoBase() = 0;

    static void init(const QString& path);
    static void clearUp();
    static void sync();

protected:
    static QDomDocument dsDoc;

    static domain_id_t idFromXmlElement(const QDomElement &element);
    static void idToXmlElement(domain_id_t id, QDomElement *element);

private:
    static void createNew();
    static QString dsPath;
};

inline XmlDaoBase::~XmlDaoBase(){}

template <class T, class D> class XmlDao: public XmlDaoBase
{
public:
    static QDomNode findXmlNode(domain_id_t id);
    static void resetCurrentId();

protected:
    static domain_id_t newId();
    static void initId();

    virtual T* newDomain() = 0;
    virtual void domainToXmlElement(T* domain, QDomElement* element) = 0;
    virtual void domainFromXmlElement(const QDomElement& element, T* domain) = 0;
    virtual QDomNode parentNode(T *domain) = 0;

    void findByAttribute(const void* attribute,
                         bool (*isAttributeSuitable)(const void* attribute, const QDomElement& element),
                         QList<T *> *result);

    void doSave(T *domain);
    void doAll(QList<T *> *result);
    T*   doFind(domain_id_t id);
    void doUpdate(T *domain);
    void doRemove(T *domain);

    T* cachedOrNewDomain(const QDomElement& element);
    T* newCachedDomain(const QDomElement& element);

    static domain_id_t currentId;
};

template <class T, class D> domain_id_t XmlDao<T, D>::currentId = 0;

template <class T, class D> void XmlDao<T, D>::resetCurrentId()
{
    currentId = 0;
}

template <class T, class D> domain_id_t XmlDao<T, D>::newId()
{
    if (currentId==0)
        initId();

    return ++currentId;
}

template <class T, class D> void XmlDao<T, D>::initId()
{
    QDomNodeList lst = dsDoc.elementsByTagName(D::tagName());

    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        tmp_id = idFromXmlElement(lst.at(i).toElement());
        currentId = qMax(tmp_id, currentId);
    }
}

template <class T, class D> QDomNode XmlDao<T, D>::findXmlNode(domain_id_t id)
{
    domain_id_t tmp_id;
    QDomElement elem;
    QDomNode node;

    QDomNode result;
    result.clear();

    QDomNodeList lst = dsDoc.elementsByTagName(D::tagName());

    for (int i = 0; i < lst.count(); ++i)
    {
        node = lst.at(i);
        elem = node.toElement();
        tmp_id = idFromXmlElement(elem);
        if (tmp_id == id)
        {
            result = node;
            break;
        }
    }

    return result;
}

template <class T, class D>
void XmlDao<T, D>::findByAttribute(const void* attribute,
                                   bool (*isAttributeSuitable)(const void*, const QDomElement &),
                                   QList<T *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(D::tagName());

    QDomElement elem;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();

        if ((*isAttributeSuitable)(attribute, elem))
            (*result) << cachedOrNewDomain(elem);
    }
}

template <class T, class D> T* XmlDao<T, D>::cachedOrNewDomain(const QDomElement &element)
{
    domain_id_t id = idFromXmlElement(element);
    T* result = D::cacheGet(id);

    if (result == NULL)
        result = newCachedDomain(element);

    return result;
}

template <class T, class D> T* XmlDao<T, D>::newCachedDomain(const QDomElement& element)
{
    T* result = newDomain();
    domainFromXmlElement(element, result);
    D::cachePut(result);
    return result;
}

template <class T, class D> void XmlDao<T, D>::doSave(T *domain)
{
    if (D::cacheGet(domain->id) != NULL) return;

    QDomNode root = parentNode(domain);
    if (root.isNull()) return;

    QDomElement elem = dsDoc.createElement(D::tagName());

    domain->id = newId();
    domainToXmlElement(domain, &elem);

    root.appendChild(elem);

    D::cachePut(domain);
}

template <class T, class D> void XmlDao<T, D>::doAll(QList<T *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(D::tagName());

    for (int i = 0; i < lst.count(); ++i)
        (*result) << cachedOrNewDomain(lst.at(i).toElement());
}

template <class T, class D> T* XmlDao<T, D>::doFind(domain_id_t id)
{
    T* result = D::cacheGet(id);

    if (result != NULL) return result;

    QDomNode node = findXmlNode(id);
    if (node.isNull() == false)
        result = newCachedDomain(node.toElement());

    return result;
}

template <class T, class D> void XmlDao<T, D>::doUpdate(T *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        QDomNode root = parentNode(domain);
        if (root.isNull()) return;

        if (node.parentNode() != root)
        {
            node.parentNode().removeChild(node);
            root.appendChild(node);
        }

        QDomElement elem = node.toElement();
        domainToXmlElement(domain, &elem);
    }
}

template <class T, class D> void XmlDao<T, D>::doRemove(T *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        node.parentNode().removeChild(node);
        D::cacheRemoveAndDispose(domain->id);
    }
}

}

#endif // XML_DAO_H
