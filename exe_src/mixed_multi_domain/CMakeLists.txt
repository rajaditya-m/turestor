set(sources
  mixed_multi_domain.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_executable(${dir_name} ${headers} ${sources})
target_link_libraries(${dir_name} ${LIBS})
