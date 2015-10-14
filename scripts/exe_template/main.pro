#TARGET = mesh_partitioner
INCLUDEPATH += $$PWD
include(../../path_info.pri)
include($$QMAKE_CONFIG_DIR/modules.pri)

PRO_FILE_NAME_FULL_PATH = $$_FILE_
PRO_FILE_BASE_NAME = $$basename(PRO_FILE_NAME_FULL_PATH)
MAIN_CPP = $$replace(PRO_FILE_BASE_NAME, .pro, .cpp)

PRO_FILE_NAME_FULL_PATH = $$_FILE_
PRO_FILE_BASE_NAME = $$basename(PRO_FILE_NAME_FULL_PATH)
MAIN_CPP = $$replace(PRO_FILE_BASE_NAME, .pro, .cpp)
EXE_NAME = $$replace(PRO_FILE_BASE_NAME, .pro, "")

DESTDIR = $$OUT_PWD/../../bin

LIBS += -L$$OUT_PWD/../bin -lcommon_library
SOURCES += \
  $$PWD/$$MAIN_CPP

