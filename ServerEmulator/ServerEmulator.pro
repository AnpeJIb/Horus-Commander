! include( ../root.pri ) {
    error( Couldn't find the root.pri file! )
}

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    Core \
    CoreTest \
    App

CoreTest.depends += Core

DESTDIR = $$EMULATOR_BUILD_DIR
