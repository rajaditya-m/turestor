set(headers
  hammock_support.h
)

set(sources
  hammock_support.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
