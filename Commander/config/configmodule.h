#ifndef CONFIGMODULE_H
#define CONFIGMODULE_H

#include <QList>
#include <QDomElement>

class ConfigModule;

class ConfigModule
{
public:
    ConfigModule();

    void addChild(ConfigModule* child);
    void rmChild(ConfigModule* child);
    bool isChanged();

    virtual void save(QDomElement* root, QDomDocument* doc) = 0;
    virtual void load(QDomElement* root) = 0;
    virtual void loadDefaults() = 0;

protected:
    void saveChildren(QDomElement* root, QDomDocument* doc);
    void loadChildren(QDomElement* root);
    void loadChildrenDefaults();
    bool areChildrenChanged();

    void changed();
    void notChanged();

    bool m_changed;

private:
    QList<ConfigModule*> m_children;
};

#endif // CONFIGMODULE_H
