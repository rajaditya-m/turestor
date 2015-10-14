set(headers
  global.h
)

set(sources
  global.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
