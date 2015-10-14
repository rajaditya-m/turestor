PRO_FILE_NAME_FULL_PATH = $$_FILE_
PRO_FILE_BASE_NAME = $$basename(PRO_FILE_NAME_FULL_PATH)
PRI_FILE_NAME = $$replace(PRO_FILE_BASE_NAME, .pro, ".pri")
include(../../path_info.pri)
include($$QMAKE_CONFIG_DIR/modules.pri)

include($$PWD/$$PRI_FILE_NAME)
LIBS = ""
PRE_TARGETDEPS = ""
TEMPLATE = lib
CONFIG += dll
DESTDIR = $$OUT_PWD/..
TARGET = $$PRO_FILE_BASE_NAME
