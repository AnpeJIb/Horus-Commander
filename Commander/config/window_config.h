#ifndef WINDOW_CONFIG_H
#define WINDOW_CONFIG_H

#include <QRect>

namespace Config { namespace Window {

const bool defaultStartMinimized      = false;
const bool defaultIsMinimized         = false;
const bool defaultQuitOnlose          = false;
const bool defaultAskQuitConfirmation = true;
const bool defaultRunAsDaemon         = false;

const QRect defaultGeometry(-1, -1, 0, 0);

}}

#endif // WINDOW_CONFIG_H
