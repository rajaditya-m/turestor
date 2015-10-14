set(headers
  camera.h
  enviroment_cube_map.h
  opengl_header.h
  opengl_helper.h
  opengl_material.h
  opengl_soft_shadow_render.h
  opengl_video_recorder.h
  ppm_io.h
  rainbow_color.h
  reflective_object_renderer.h
  scene.h
  textured_triangle_mesh_renderer.h
  triangle_mesh_render.h
)

set(sources
  camera.cpp
  enviroment_cube_map.cpp
  opengl_helper.cpp
  opengl_material.cpp
  opengl_soft_shadow_render.cpp
  opengl_video_recorder.cpp
  ppm_io.cpp
  rainbow_color.cpp
  reflective_object_renderer.cpp
  scene.cpp
  textured_triangle_mesh_renderer.cpp
  triangle_mesh_render.cpp
)

ExtractLastPartFromFullPath(${CMAKE_CURRENT_LIST_DIR} dir_name)
add_library(${dir_name} ${headers} ${sources})
