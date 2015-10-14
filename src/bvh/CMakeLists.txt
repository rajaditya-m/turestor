set(headers
  bvh.h
  collision_util.h
  tet_collider.h
  util.h
)

set(sources
  bvh.cpp
  tet_collider.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
