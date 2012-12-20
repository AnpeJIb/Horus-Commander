#ifndef WINDOWCONFIG_H
#define WINDOWCONFIG_H

#include <QRect>

class WindowConfig
{
public:
    WindowConfig(){}

    bool isMinimized()      {return m_minimized;}
    bool promtClose()       {return m_promtClose;}
    bool quitOnClose()      {return m_quitOnClose;}
    QRect geometry() const  {return m_geometry;}

    void setMinimized(bool value)   {m_minimized    = value;}
    void setPromtClose(bool value)  {m_promtClose   = value;}
    void setQuitOnClose(bool value) {m_quitOnClose  = value;}
    void setGeometry(const QRect &value) {m_geometry = value;}

private:
    QRect m_geometry;
    bool m_minimized;
    bool m_promtClose;
    bool m_quitOnClose;
};

#endif // WINDOWCONFIG_H
