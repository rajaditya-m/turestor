set(headers
  Common.h
  Constraint.h
  Force.h
  LSSolver.h
  shape_op_tet.h
  Solver.h
  Types.h
)

set(sources
  Constraint.cpp
  Force.cpp
  LSSolver.cpp
  shape_op_tet.cpp
  Solver.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
