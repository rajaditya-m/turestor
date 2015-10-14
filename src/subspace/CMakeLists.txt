set(headers
  basis_io.h
  mixed_multi_domain_simulator.h
  mixed_multi_domain_tet.h
  multi_domain_subspace_simulator.h
  multi_domain_tet.h
  partitioned_mesh_generator.h
  random_subspace_pose_viewer.h
  subspace_pose_sample_simulator.h
  subspace_pose_viewer.h
  subspace_simulator.h
  subspace_tet.h
)

set(sources
  basis_io.cpp
  mixed_multi_domain_simulator.cpp
  mixed_multi_domain_tet.cpp
  multi_domain_subspace_simulator.cpp
  multi_domain_tet.cpp
  partitioned_mesh_generator.cpp
  random_subspace_pose_viewer.cpp
  subspace_pose_sample_simulator.cpp
  subspace_pose_viewer.cpp
  subspace_simulator.cpp
  subspace_tet.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
