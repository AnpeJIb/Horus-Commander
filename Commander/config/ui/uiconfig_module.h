#ifndef UICONFIGMODULE_H
#define UICONFIGMODULE_H

#include <QList>

class UIConfigModule;

class UIConfigModule
{
public:
    void addChild(UIConfigModule* child);
    void rmChild(UIConfigModule* child);

    virtual bool isValid() = 0;
    virtual void save() = 0;
    virtual void load() = 0;
    virtual void loadDefaults() = 0;
    virtual void setConfigEnabled(bool value) = 0;

protected:
    bool areChildrenValid();
    void saveChildren();
    void loadChildren();
    void loadChildrenDefaults();
    void setConfigChildrenEnabled(bool value);

private:
    QList<UIConfigModule*> children;
};

#endif // UICONFIGMODULE_H
