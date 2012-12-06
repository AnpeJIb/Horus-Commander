#include "uiconfig_module.h"

UIConfigModule::UIConfigModule()
{
}

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

bool UIConfigModule::saveChildren()
{
    bool result = false;

    foreach (UIConfigModule * ch, children)
        result |= ch->save();

    return result;
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
