#ifndef WINDOWCONFIG_H
#define WINDOWCONFIG_H

#include "configmodule.h"
#include <QRect>

class WindowConfig : public ConfigModule
{
public:
    WindowConfig();

    void save(QDomElement* root, QDomDocument* doc);
    void load(QDomElement* root);
    void loadDefaults();

    QRect geometry() const;
    bool isMinimized();

    void setGeometry(const QRect& value);
    void setMinimized(bool value);

private:
    void saveGeometry(QDomElement *root, QDomDocument *doc);
    void saveMinimized(QDomElement *root);

    bool loadGeometry(QDomElement *root);
    void loadMinimized(QDomElement *root);

    QRect m_geometry;
    bool m_minimized;
};

#endif // WINDOWCONFIG_H
