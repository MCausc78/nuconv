cmake_minimum_required(VERSION 3.22)
project(nuconv
  LANGUAGES C
  VERSION 1.0.0
  DESCRIPTION "Library for converting strings to integers with overflow protection and vice versa")
set(CMAKE_C_STANDARD 99)
include(GNUInstallDirs)
file(GLOB_RECURSE SOURCES "src/**.c")
add_library(nuconv SHARED ${SOURCES})
set_target_properties(nuconv PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER include/nuconv.h)

target_include_directories(nuconv PRIVATE include)
target_include_directories(nuconv PRIVATE src)

install(TARGETS nuconv
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
