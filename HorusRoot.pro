! include( root.pri ) {
    error( Couldn't find the root.pri file! )
}

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    libs \
    HorusTests

HorusTests.depends = libs

DESTDIR = $$ROOT_BUILD_DIR
