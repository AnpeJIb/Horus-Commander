#ifndef XML_DAO_H
#define XML_DAO_H

#include <QString>
#include <QDomDocument>

#include "generic_domain.h"
#include "generic_dao.h"
#include "xml_dao_helper.h"

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

private:
    static void createNew();
    static QString dsPath;
};

inline XmlDaoBase::~XmlDaoBase(){}

template <class T, class D> class XmlDao: public XmlDaoBase
{
public:
    virtual ~XmlDao() = 0;

    QDomNode findXmlNode(domain_id_t id);

protected:
    static QString tagName() { return D::tagNameRaw(); }

    static domain_id_t newId();
    static void initId();

    static domain_id_t currentId;
};

template <class T, class D> inline XmlDao<T, D>::~XmlDao(){}

template <class T, class D> domain_id_t XmlDao<T, D>::currentId = 0;

template <class T, class D> domain_id_t XmlDao<T, D>::newId()
{
    if (currentId==0)
        initId();

    return ++currentId;
}

template <class T, class D> void XmlDao<T, D>::initId()
{
    QDomNodeList lst = dsDoc.elementsByTagName(tagName());

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

    QDomNodeList lst = dsDoc.elementsByTagName(tagName());

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

}

#endif // XML_DAO_H
