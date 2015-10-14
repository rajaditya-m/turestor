#------------------------------------------------------------------------------
# Qt
#------------------------------------------------------------------------------
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5OpenGL)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})
#message(STATUS "GLINC:" ${Qt5OpenGL_INCLUDE_DIRS})
