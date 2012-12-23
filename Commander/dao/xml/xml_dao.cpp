#include "xml_dao.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "status_print.h"

#define XML_ROOT  "root"

QDomDocument Dao::XmlDao::dsDoc;
QString Dao::XmlDao::dsPath;

void Dao::XmlDao::init(const QString& path)
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
        STATUS_PRINT::ERROR_(str);
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
            STATUS_PRINT::ERROR_(QObject::tr("Wrong config root"));
            loadOk = false;
        }
    }

    if (loadOk == false)
    {
        STATUS_PRINT::DEBUG_(QObject::tr("Creating data source file"));
        createNew();
        sync();
    }
}

void Dao::XmlDao::createNew()
{
    QDomProcessingInstruction pi =
            dsDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    dsDoc.insertBefore(pi, QDomNode());

    QDomElement root = dsDoc.createElement(XML_ROOT);
    dsDoc.appendChild(root);
}

void Dao::XmlDao::clearUp()
{
    dsDoc.clear();
    QFile::remove(dsPath);
}

void Dao::XmlDao::sync()
{
    QFile file(dsPath);

    if(file.open(QIODevice::WriteOnly) == false)
    {
        QString str = QObject::tr("Could not open config file \"%1\" for writing").arg(dsPath);
        STATUS_PRINT::ERROR_(str);
        return;
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    ts << dsDoc.toString();
    file.close();
}
