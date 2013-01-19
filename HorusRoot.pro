! include( root.pri ) {
    error( Couldn't find the root.pri file! )
}

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    libs \
    TestUtil \
    ServerEmulator

ServerEmulator.depends += libs TestUtil

DESTDIR = $$ROOT_BUILD_DIR
