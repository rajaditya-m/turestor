CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
include(cmake_config/functions.cmake)
include(cmake_config/open_mp.cmake)
ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} project_name)
project(${project_name})

# Installation specific folder path
IF(WIN32)
  SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\Qt\\Qt5.4.1\\5.4\\msvc2013_64_opengl")
  include_directories("c:\\lib\\include")
  link_directories("c:\\lib\\lib\\x64")
  SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\lib")
ELSEIF(APPLE)
    SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/Users/dj/Qt5.3.2/5.3/clang_64")
ELSE() # Linux 
    SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/home/dj/Qt5.4.0/5.4/gcc_64")
ENDIF()
include(cmake_config/qt5.cmake)

IF(WIN32)
  #------------------------------------------------------------------------------
  # Windows 
  #------------------------------------------------------------------------------
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DCURRENT_DIRECTORY=${CMAKE_CURRENT_SOURCE_DIR}/data/)
  set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j 8")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /opemmp")
  set(CORE_LIBS GlU32 freeglut glew32 OpenGL32 arpack_x64)
ELSE()
  add_definitions(-DROOT_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\" )
  add_definitions(-DDATA_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}/data\" )
  add_definitions(-DCONF_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}/conf\" )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  FIND_PACKAGE(OpenGL)
  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIRS})
  FIND_PACKAGE(GLEW)
  INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
  FIND_PACKAGE(GLUT REQUIRED)
  INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIRS})
  IF(APPLE)
    #------------------------------------------------------------------------------
    # Mac OS X 
    #------------------------------------------------------------------------------
    SET(CMAKE_CXX_COMPILER "/opt/local/bin/g++-mp-4.8")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
    LINK_DIRECTORIES(/opt/local/lib)
    include_directories(/opt/local/include)
    include_directories(/opt/local/include/eigen3)
  ELSEIF(UNIX)
    #------------------------------------------------------------------------------
    # Linux 
    #------------------------------------------------------------------------------
    SET(CMAKE_CXX_COMPILER "g++-4.8")
    #SET(CMAKE_CXX_COMPILER "ccache g++-4.8")
    include_directories(/usr/include/eigen3) 
  ENDIF()
ENDIF()

#------------------------------------------------------------------------------
# include path 
#------------------------------------------------------------------------------
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}) 
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#------------------------------------------------------------------------------
# modules
#------------------------------------------------------------------------------
include(cmake_config/modules.cmake)
foreach(dir ${modules})
  include_directories(src/${dir})
endforeach(dir)
foreach(dir ${modules})
  add_subdirectory(src/${dir})
endforeach(dir)


set(LIBS ${modules})
IF(UNIX)
  # resolve static library link order issue in Linux
  set(LIBS ${LIBS} ${LIBS})
ENDIF()
set(LIBS ${LIBS}
  ${CORE_LIBS}
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES}
)

#------------------------------------------------------------------------------
# executables 
#------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include(cmake_config/exes.cmake)
foreach(exe ${exes})
  add_subdirectory(exe_src/${exe})
endforeach(exe)
