#ifndef WINDOWCONFIG_H
#define WINDOWCONFIG_H

#include "configmodule.h"
#include <QRect>

#define DEFAULT_MINIMIZED       false
#define DEFAULT_PROMPT_CLOSE    true
#define DEFAULT_QUIT_ON_CLOSE   false

class WindowConfig : public ConfigModule
{
public:
    WindowConfig();

    void save(QDomElement* root, QDomDocument* doc);
    void load(QDomElement* root);
    void loadDefaults();

    QRect geometry() const;
    bool isMinimized();
    bool promtClose();
    bool quitOnClose();

    void setGeometry(const QRect& value);
    void setMinimized(bool value);
    void setPromtClose(bool value);
    void setQuitOnClose(bool value);

private:
    void saveGeometry(QDomElement *root, QDomDocument *doc);
    void saveMinimized(QDomElement *root);
    void savePromtClose(QDomElement *root);
    void saveQuitOnClose(QDomElement *root);

    bool loadGeometry(QDomElement *root);
    void loadMinimized(QDomElement *root);
    void loadPromtClose(QDomElement *root);
    void loadQuitOnClose(QDomElement *root);

    QRect m_geometry;
    bool m_minimized;
    bool m_promtClose;
    bool m_quitOnClose;
};

#endif // WINDOWCONFIG_H
