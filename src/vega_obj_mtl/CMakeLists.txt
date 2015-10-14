set(headers
  macros.h
  objMesh.h
  objMesh-disjointSet.h
  objMeshRender.h
)

set(sources
  objMesh.cpp
  objMesh-disjointSet.cpp
  objMeshRender.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
