set(headers
  mesh_viewer.h
  obj_mesh_io.h
  off_mesh_io.h
  triangular_mesh.h
  triangular_mesh_io.h
)

set(sources
  mesh_viewer.cpp
  obj_mesh_io.cpp
  off_mesh_io.cpp
  triangular_mesh.cpp
  triangular_mesh_io.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
