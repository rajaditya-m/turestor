ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
set(sources
  ${dir_name}.cpp
)
add_executable(${dir_name} ${headers} ${sources})
target_link_libraries(${dir_name} ${LIBS})
