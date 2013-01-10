# Platform-dependent defines
unix {
DEFINES += _UNIX_
}

win32 {
DEFINES += _WIN32_
DEFINES += _WIN32_WINNT=0x0501
DEFINES += WINVER=0x0501
}

PROJECT_ROOT_DIRECTORY = $$PWD

# Build paths
ROOT_BUILD_DIR = $$PROJECT_ROOT_DIRECTORY/bin

LIBS_BUILD_DIR = $$ROOT_BUILD_DIR/libs
NETWORK_LIB_BUILD_DIR = $$LIBS_BUILD_DIR/HorusNetwork
NETWORK_LIB_TEST_BUILD_DIR = $$LIBS_BUILD_DIR/HorusNetworkTest

EMULATOR_BUILD_DIR = $$ROOT_BUILD_DIR/ServerEmulator
EMULATOR_CORE_BUILD_DIR = $$EMULATOR_BUILD_DIR/Core
EMULATOR_CORE_TEST_BUILD_DIR = $$EMULATOR_BUILD_DIR/CoreTest

# Dependency libraries

# Libs for HorusNetwork
unix:HORUS_NETWORK_LIBS  = -L/usr/lib -lboost_system -lboost_thread
win32:HORUS_NETWORK_LIBS = -lboost_system-mgw44-mt-1_52 \
    -lboost_thread-mgw44-mt-1_52 -lws2_32 -lmswsock
