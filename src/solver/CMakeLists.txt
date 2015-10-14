set(headers
  BLOCK_MATRIX_GRAPH.h
  MATRIX.h
  mixed_sparse_matrix.h
  SOLVER_MATH.h
)

set(sources
  BLOCK_MATRIX_GRAPH.cpp
  mixed_sparse_matrix.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
