set(headers
  CIsoSurface.h
  hammock_level_set.h
  Vectors.h
)

set(sources
  CIsoSurface.cpp
  Vectors.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
