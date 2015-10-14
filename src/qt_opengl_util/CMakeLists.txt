set(headers
  input_handler.h
  qt_gl_3d_scene_navigator.h
  qt_object_selector.h
  selectable_object.h
)

set(sources
  input_handler.cpp
  qt_gl_3d_scene_navigator.cpp
  qt_object_selector.cpp
  qt_object_selector.h.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
