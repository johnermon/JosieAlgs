cmake_minimum_required(VERSION 3.31.6)
project(JosieAlgs LANGUAGES C)
add_executable(JosieAlgs 
  src/main.c
  src/josielib_impl.c
)

include_directories(
  include/josielib
)
