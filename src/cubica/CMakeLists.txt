set(headers
  cubica_simulator.h
  cubica_tet.h
)

set(sources
  cubica_simulator.cpp
  cubica_tet.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
