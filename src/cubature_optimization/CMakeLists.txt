set(headers
  CubatureObjDomain.h
  CubatureObjInterface.h
  multi_domain_cubature.h
  single_domain_cubature.h

  cubature_base/GreedyCubop.h
cubature_base/MATRIX.h
cubature_base/MATRIX3.h
cubature_base/MERSENNETWISTER.h
cubature_base/nnls.h
cubature_base/SETTINGS.h
cubature_base/steve.h
cubature_base/TYPES.h
cubature_base/VEC3.h
cubature_base/VECTOR.h

)

set(sources
  CubatureObjDomain.cpp
  CubatureObjInterface.cpp
  multi_domain_cubature.cpp
  single_domain_cubature.cpp
  cubature_base/GreedyCubop.cpp
cubature_base/MATRIX_DEBUG.cpp
cubature_base/MATRIX3.cpp
cubature_base/nnls.cpp
cubature_base/steve.cpp
cubature_base/VECTOR_DEBUG.cpp

)

include_directories(cubature_base)
ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
