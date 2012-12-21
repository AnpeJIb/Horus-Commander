#include "xml_dao.h"
#include "status_print.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

using namespace Dao;

template <class T> QDomDocument XmlDao<T>::dsDoc;
template <class T> QString XmlDao<T>::dsPath;

template <class T> void XmlDao<T>::init(const QString& dsPath)
{

    QFileInfo dsFileInfo(dsPath);

    QDir d = dsFileInfo.dir();
    if (d.exists()==false)
        d.mkpath(d.path());

    QFile file(dsPath);

    if(file.open(QIODevice::ReadWrite) == false)
    {
        QString str = QObject::tr("Could not open config file \"%1\" for reading").arg(dsPath);
        STATUS_PRINT::ERROR_(str);
        return;
    }

    dsDoc.clear();
    if (dsDoc.setContent(&file) == false)
        STATUS_PRINT::DEBUG_(QObject::tr("Bad data source file"));

    file.close();
}

template <class T> void XmlDao<T>::clearUp()
{
    dsDoc.clear();
    QFile::remove(dsPath);
}

template <class T> void XmlDao<T>::sync()
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
