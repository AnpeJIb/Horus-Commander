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

# Build paths
ROOT_BUILD_DIR = $$PWD/bin
LIBS_BUILD_DIR = $$ROOT_BUILD_DIR/libs
NETWORK_LIB_BUILD_DIR = $$LIBS_BUILD_DIR/HorusNetwork
