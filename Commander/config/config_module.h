#ifndef CONFIGMODULE_H
#define CONFIGMODULE_H

#include <QList>
#include <QDomElement>

#define CFG_SET_VALUE(oldValue, newValue) \
            do { if(oldValue!=newValue){oldValue=newValue; changed();} } while(0);

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

    void appendTextNode(QDomElement* root, QDomDocument* doc, const QString& name, const QString& value);

    void changed();
    void notChanged();

    bool m_changed;

private:
    QList<ConfigModule*> m_children;
};

#endif // CONFIGMODULE_H
