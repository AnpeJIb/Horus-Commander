#include "xml_dao.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "log_service.h"

#define XML_ROOT    "root"
#define XML_ATTR_ID "id"

QDomDocument Dao::XmlDaoBase::dsDoc;
QString Dao::XmlDaoBase::dsPath;

void Dao::XmlDaoBase::init(const QString& path)
{
    dsPath = path;

    QFileInfo dsFileInfo(dsPath);

    QDir d = dsFileInfo.dir();
    if (d.exists() == false)
        d.mkpath(d.path());

    QFile file(dsPath);

    if(file.open (QIODevice::ReadWrite) == false)
    {
        QString str = QObject::tr("Could not open config file \"%1\" for reading").arg(dsPath);
        Service::LOGGER::msgError(str);
        return;
    }

    dsDoc.clear();

    bool loadOk = dsDoc.setContent(&file);
    file.close();

    if (loadOk)
    {
        QDomElement root = dsDoc.documentElement();

        if(root.tagName() != XML_ROOT)
        {
            Service::LOGGER::msgError(QObject::tr("Wrong config root"));
            loadOk = false;
        }
    }

    if (loadOk == false)
    {
        Service::LOGGER::msgDebug(QObject::tr("Creating data source file"));
        createNew();
        sync();
    }
}

void Dao::XmlDaoBase::createNew()
{
    QDomProcessingInstruction pi =
            dsDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    dsDoc.insertBefore(pi, QDomNode());

    QDomElement root = dsDoc.createElement(XML_ROOT);
    dsDoc.appendChild(root);
}

void Dao::XmlDaoBase::clearUp()
{
    dsDoc.clear();
    QFile::remove(dsPath);
}

void Dao::XmlDaoBase::sync()
{
    QFile file(dsPath);

    if(file.open(QIODevice::WriteOnly) == false)
    {
        QString str = QObject::tr("Could not open config file \"%1\" for writing").arg(dsPath);
        Service::LOGGER::msgError(str);
        return;
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    ts << dsDoc.toString();
    file.close();
}

domain_id_t Dao::XmlDaoBase::idFromXmlElement(const QDomElement &element)
{
    return element.attribute(XML_ATTR_ID, "0").toULongLong();
}

void Dao::XmlDaoBase::idToXmlElement(domain_id_t id, QDomElement *element)
{
    element->setAttribute(XML_ATTR_ID, QString::number(id));
}
