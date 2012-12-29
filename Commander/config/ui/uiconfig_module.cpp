#include "uiconfig_module.h"

void UIConfigModule::addChild(UIConfigModule *child)
{
    if (children.contains(child)) return;
    children << child;
}

void UIConfigModule::rmChild(UIConfigModule *child)
{
    if (children.contains(child)==false) return;
    children.removeOne(child);
}

bool UIConfigModule::areChildrenValid()
{
    bool result = true;

    foreach (UIConfigModule * ch, children)
        result &= ch->isValid();

    return result;
}

void UIConfigModule::saveChildren()
{
    foreach (UIConfigModule * ch, children)
        ch->save();
}

void UIConfigModule::loadChildren()
{
    foreach (UIConfigModule * ch, children)
        ch->load();
}

void UIConfigModule::loadChildrenDefaults()
{
    foreach (UIConfigModule * ch, children)
        ch->loadDefaults();
}

void UIConfigModule::setConfigChildrenEnabled(bool value)
{
    foreach (UIConfigModule * ch, children)
        ch->setConfigEnabled(value);
}
