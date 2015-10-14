set(headers
  main_window.h
  open_gl_qt.h
)

SET(CMAKE_AUTOMOC ON)
QT5_WRAP_UI(ui_headers
  main_window.ui
)

set(sources
  main_window.cpp
  open_gl_qt.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources} ${ui_headers})
target_link_libraries(${dir_name} Qt5::Widgets Qt5::OpenGL)
