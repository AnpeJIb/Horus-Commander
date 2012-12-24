#include "simple_parameter_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

domain_id_t SimpleParameterXmlDao::currentId = 0;
QString SimpleParameterXmlDao::tagName       = "SimpleParameter";

QMap<domain_id_t, SimpleParameter*> SimpleParameterXmlDao::cache;

SimpleParameterXmlDao::SimpleParameterXmlDao()
{
}

SimpleParameterXmlDao::~SimpleParameterXmlDao()
{
}

void SimpleParameterXmlDao::save(SimpleParameter *domain)
{
    /** Check existance in cache */
    if (cache[domain->id] != NULL) return;

    domain->id = newId();

    /** Put to cache */
    cache[domain->id] = domain;

    QDomElement root = dsDoc.documentElement();
    QDomElement elem = dsDoc.createElement(tagName);

    elem.setAttribute(XML_ATTR_ID,        QString::number(domain->id));
    elem.setAttribute(XML_ATTR_TITLE,     domain->title);
    elem.setAttribute(XML_ATTR_CODE_NAME, domain->codeName);

    root.appendChild(elem);
}

void SimpleParameterXmlDao::all(QList<SimpleParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    SimpleParameter* parameter;
    domain_id_t id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        id = elem.attribute(XML_ATTR_ID, "0").toULongLong();

        /** Try to get from cache at first */
        parameter = cache[id];

        if (parameter == NULL)
        {
            parameter = new SimpleParameter;
            parameter->id       = id;
            parameter->title    = elem.attribute(XML_ATTR_TITLE, "");
            parameter->codeName = elem.attribute(XML_ATTR_CODE_NAME, "");

            /** Put to cache */
            cache[id] = parameter;
        }

        (*result) << parameter;
    }
}

SimpleParameter *SimpleParameterXmlDao::find(domain_id_t id)
{
    /** Try to get from cache at first */
    SimpleParameter* result = cache[id];

    if (result != NULL) return result;

    QDomNode node = findXmlNode(id);
    if (node.isNull() == false)
    {
        QDomElement elem = node.toElement();

        result = new SimpleParameter;
        result->id       = id;
        result->title    = elem.attribute(XML_ATTR_TITLE, "");
        result->codeName = elem.attribute(XML_ATTR_CODE_NAME, "");

        /** Put to cache */
        cache[id] = result;
    }

    return result;
}

void SimpleParameterXmlDao::findByTitle(const domain_title_t &title, QList<SimpleParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t id;
    domain_title_t tmp_title;

    SimpleParameter* parameter;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_title = elem.attribute(XML_ATTR_TITLE, "");
        if (tmp_title == title)
        {
            id = elem.attribute(XML_ATTR_ID, "0").toULongLong();

            /** Try to get from cache at first */
            parameter = cache[id];

            if (parameter == NULL)
            {
                parameter = new SimpleParameter;

                parameter->id       = id;
                parameter->title    = QString(title);
                parameter->codeName = elem.attribute(XML_ATTR_CODE_NAME, "");

                /** Put to cache */
                cache[id] = parameter;
            }

            (*result) << parameter;
        }
    }
}

void SimpleParameterXmlDao::findByCodeName(const domain_codeName_t &codeName, QList<SimpleParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t id;
    domain_codeName_t tmp_codeName;

    SimpleParameter* parameter;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_codeName = elem.attribute(XML_ATTR_CODE_NAME, "");

        if (tmp_codeName == codeName)
        {
            id = elem.attribute(XML_ATTR_ID, "0").toULongLong();

            /** Try to get from cache at first */
            parameter = cache[id];

            if (parameter == NULL)
            {
                parameter = new SimpleParameter;

                parameter->id        = id;
                parameter->title     = elem.attribute(XML_ATTR_TITLE, "");
                parameter->codeName  = codeName;

                /** Put to cache */
                cache[id] = parameter;
            }

            (*result) << parameter;
        }
    }
}

void SimpleParameterXmlDao::update(const SimpleParameter *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        QDomElement elem = node.toElement();

        elem.setAttribute(XML_ATTR_TITLE,     domain->title);
        elem.setAttribute(XML_ATTR_CODE_NAME, domain->codeName);
    }
}

void SimpleParameterXmlDao::remove(const SimpleParameter *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        node.parentNode().removeChild(node);

        /** Remove from cache */
        SimpleParameter* cached = cache[domain->id];
        if (cached != NULL)
        {
            cache.remove(domain->id);
            delete cached;
        }
    }
}

QDomNode SimpleParameterXmlDao::findXmlNode(domain_id_t id)
{
    domain_id_t tmp_id;
    QDomElement elem;
    QDomNode node;

    QDomNode result;
    result.clear();

    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    for (int i = 0; i < lst.count(); ++i)
    {
        node = lst.at(i);
        elem = node.toElement();
        tmp_id = elem.attribute(XML_ATTR_ID, "0").toULongLong();
        if (tmp_id == id)
        {
            result = node;
            break;
        }
    }

    return result;
}

void SimpleParameterXmlDao::clearCache()
{
    cache.clear();
}

domain_id_t SimpleParameterXmlDao::newId()
{
    if (currentId==0)
        initId();

    return ++currentId;
}

void SimpleParameterXmlDao::initId()
{
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        tmp_id = lst.at(i).toElement().attribute(XML_ATTR_ID, "0").toULongLong();
        currentId = qMax(tmp_id, currentId);
    }
}
