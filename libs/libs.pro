! include( ../root.pri ) {
    error( Couldn't find the root.pri file! )
}

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    HorusNetwork \
    HorusNetworkTest \
    HorusFile \
    HorusFileTest

HorusNetworkTest.depends += HorusNetwork

DESTDIR = $$LIBS_BUILD_DIR
