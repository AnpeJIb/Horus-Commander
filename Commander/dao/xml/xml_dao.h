#ifndef XML_DAO_H
#define XML_DAO_H

#include "generic_dao.h"
#include <QString>

#include <QDomDocument>

namespace Dao {

template<class T> class XmlDao: public GenericDao<T>
{
public:
    static void init(const QString& dsPath);
    static void clearUp();
    static void sync();

protected:
    static QDomDocument dsDoc;

private:
    static QString dsPath;
};

}

#endif // XML_DAO_H
