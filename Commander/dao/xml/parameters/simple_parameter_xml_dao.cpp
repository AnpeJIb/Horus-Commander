#include "simple_parameter_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

QString SimpleParameterXmlDao::m_tagName = "SimpleParameter";

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
    QDomElement elem = dsDoc.createElement(m_tagName);

    idToXmlElement(       domain->id,       &elem);
    titleToXmlElement(    domain->title,    &elem);
    codeNameToXmlElement( domain->codeName, &elem);

    root.appendChild(elem);
}

void SimpleParameterXmlDao::all(QList<SimpleParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    SimpleParameter* parameter;
    domain_id_t id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        id = idFromXmlElement(elem);

        /** Try to get from cache at first */
        parameter = cache[id];

        if (parameter == NULL)
        {
            parameter = new SimpleParameter;
            parameter->id       = id;
            parameter->title    = titleFromXmlElement(elem);
            parameter->codeName = codeNameFromXmlElement(elem);

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
        result->title    = titleFromXmlElement(elem);
        result->codeName = codeNameFromXmlElement(elem);

        /** Put to cache */
        cache[id] = result;
    }

    return result;
}

void SimpleParameterXmlDao::findByTitle(const domain_title_t &title, QList<SimpleParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    domain_id_t id;
    domain_title_t tmp_title;

    SimpleParameter* parameter;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_title = titleFromXmlElement(elem);
        if (tmp_title == title)
        {
            id = idFromXmlElement(elem);

            /** Try to get from cache at first */
            parameter = cache[id];

            if (parameter == NULL)
            {
                parameter = new SimpleParameter;

                parameter->id       = id;
                parameter->title    = QString(title);
                parameter->codeName = codeNameFromXmlElement(elem);

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
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    domain_id_t id;
    domain_codeName_t tmp_codeName;

    SimpleParameter* parameter;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_codeName = codeNameFromXmlElement(elem);

        if (tmp_codeName == codeName)
        {
            id = idFromXmlElement(elem);

            /** Try to get from cache at first */
            parameter = cache[id];

            if (parameter == NULL)
            {
                parameter = new SimpleParameter;

                parameter->id       = id;
                parameter->title    = titleFromXmlElement(elem);
                parameter->codeName = codeName;

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

        titleToXmlElement(   domain->title,    &elem);
        codeNameToXmlElement(domain->codeName, &elem);
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

QString SimpleParameterXmlDao::tagNameRaw()
{
    return m_tagName;
}
