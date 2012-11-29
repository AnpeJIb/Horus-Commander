#include "configmodule.h"

ConfigModule::ConfigModule()
    : m_changed(false)
{
}

void ConfigModule::addChild(ConfigModule *child)
{
    if (m_children.contains(child)) return;
    m_children << child;
}

void ConfigModule::rmChild(ConfigModule *child)
{
    if (m_children.contains(child)==false) return;
    m_children.removeOne(child);
}

void ConfigModule::saveChildren(QDomElement* root, QDomDocument *doc)
{
    foreach (ConfigModule * ch, m_children)
        ch->save(root, doc);
}

void ConfigModule::loadChildren(QDomElement* root)
{
    foreach (ConfigModule * ch, m_children)
        ch->load(root);
}

void ConfigModule::loadChildrenDefaults()
{
    foreach (ConfigModule * ch, m_children)
        ch->loadDefaults();
}

bool ConfigModule::areChildrenChanged()
{
    bool result = false;

    foreach (ConfigModule * ch, m_children)
        result |= ch->isChanged();

    return result;
}

bool ConfigModule::isChanged()
{
    return m_changed | areChildrenChanged();
}

void ConfigModule::changed()
{
    m_changed = true;
}

void ConfigModule::notChanged()
{
    m_changed = false;
}