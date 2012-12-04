#ifndef UICONFIGMODULE_H
#define UICONFIGMODULE_H

#include <QList>

class UIConfigModule;

class UIConfigModule
{
public:
    UIConfigModule();

    void addChild(UIConfigModule* child);
    void rmChild(UIConfigModule* child);

    virtual bool save() = 0;
    virtual void load() = 0;
    virtual void loadDefaults() = 0;

protected:
    bool saveChildren();
    void loadChildren();
    void loadChildrenDefaults();

private:
    QList<UIConfigModule*> children;
};

#endif // UICONFIGMODULE_H
