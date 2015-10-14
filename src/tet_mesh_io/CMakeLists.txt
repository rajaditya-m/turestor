set(headers
  binary_tet_mesh_io.h
  cubica_tet_mesh_io.h
  msh_tet_mesh_io.h
  neutral_format_io.h
  tet_gen_mesh_io.h
  tetrahedral_mesh_io.h
  vega_tet_mesh_io.h
)

set(sources
  binary_tet_mesh_io.cpp
  cubica_tet_mesh_io.cpp
  msh_tet_mesh_io.cpp
  neutral_format_io.cpp
  tet_gen_mesh_io.cpp
  tetrahedral_mesh_io.cpp
  vega_tet_mesh_io.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
