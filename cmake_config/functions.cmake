function(ExtractLastPartFromFullPath path name)
  string(FIND ${path} "/" last_slash REVERSE)
  string(LENGTH ${path} dir_length)
  MATH(EXPR sub_str_length "${dir_length} - ${last_slash} - 1" )
  MATH(EXPR last_slash "${last_slash} + 1")
  string(SUBSTRING ${path} ${last_slash} ${sub_str_length} ${name})
  set(${name} ${${name}} PARENT_SCOPE)
endfunction()
