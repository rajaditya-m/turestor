set(headers
  cbmp.h
  pconsole.h
  simOBJ.h
  strmanip.h
)

set(sources
  pconsole.cpp
  simobj.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
