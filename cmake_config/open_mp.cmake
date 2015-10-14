#------------------------------------------------------------------------------
#  OpenMP 
#------------------------------------------------------------------------------
IF(APPLE)
  # find_package(OpenMP) fails on Mac, so set the flags manually
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
  #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
ELSE()
  enable_language(CXX)
  find_package(OpenMP)
  if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  else()
    message(STATUS "Failed to find OpenMP")	
  endif()
ENDIF()
