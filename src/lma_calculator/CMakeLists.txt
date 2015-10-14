set(headers
  LMACalculator.h
)

set(sources
  LMACalculator.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
