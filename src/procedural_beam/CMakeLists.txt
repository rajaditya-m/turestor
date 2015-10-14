set(headers
  procedural_beam.h
)

set(sources
  procedural_beam.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
