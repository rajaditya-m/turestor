set(headers
  elastic_rod_shape.h
  frame_attachment.h
  pbd_elastic_rod.h
  pbd_rod_simulator.h
)

set(sources
  elastic_rod_shape.cpp
  frame_attachment.cpp
  pbd_elastic_rod.cpp
  pbd_rod_simulator.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
