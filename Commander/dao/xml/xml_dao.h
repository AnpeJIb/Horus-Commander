#ifndef XML_DAO_H
#define XML_DAO_H

#include "generic_domain.h"
#include "generic_dao.h"
#include <QString>

#include <QDomDocument>

namespace Dao {

class XmlDao
{
public:
    virtual ~XmlDao() = 0;

    static void init(const QString& path);
    static void clearUp();
    static void sync();

protected:
    static QDomDocument dsDoc;

private:
    static void createNew();
    static QString dsPath;
};

inline XmlDao::~XmlDao(){}

}

#endif // XML_DAO_H
