# Platform-dependent defines
unix {
DEFINES += _UNIX_
}

win32 {
DEFINES += _WIN32_
}

# Boost libs
unix {
LIBS += -L/usr/lib/
}

win32 {
LIBS += -L/path/to/boost
}
