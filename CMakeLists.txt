cmake_minimum_required(VERSION 2.8)
project(cpp_concurrency)

set(ROOT ${PROJECT_SOURCE_DIR})

add_compile_options(-O3 -fPIC -g -std=c++14 -Wall)

# add_subdirectory(${ROOT}/src/01)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${ROOT}/src)

FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${ROOT}/src/${subdir})
ENDFOREACH()