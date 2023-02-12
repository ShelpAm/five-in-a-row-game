cmake_minimum_required(VERSION 3.20)
project(imgui)

set(IMGUI_DIR ${PROJECT_SOURCE_DIR})

if(NOT IMGUI_DIR)
  message(FATAL_ERROR "IMGUI_DIR must be set to the imgui root directory")
endif()

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(ROOT ${IMGUI_DIR})

add_library(imgui STATIC
  ${ROOT}/imgui.cpp
  ${ROOT}/imgui.h
  ${ROOT}/imstb_rectpack.h
  ${ROOT}/imstb_textedit.h
  ${ROOT}/imstb_truetype.h
  ${ROOT}/imgui_demo.cpp
  ${ROOT}/imgui_draw.cpp
  ${ROOT}/imgui_internal.h
  ${ROOT}/imgui_tables.cpp
  ${ROOT}/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC
  $<BUILD_INTERFACE:${ROOT}>
  $<INSTALL_INTERFACE:include>)

message(STATUS "LIBOPENGL is ${LIB_OPENGL}")
add_executable(example1 examples/example_glfw_opengl3/main.cpp)
target_include_directories(example1 PRIVATE . backends ${GLFW_INCLUDE_DIR})
target_link_libraries(example1 PRIVATE imgui imgui_impl_glfw
  imgui_impl_opengl3
  ${LIB_OPENGL})

foreach(BACKEND glfw opengl3)
  set(NAME imgui_impl_${BACKEND})
  set(HEADER ${ROOT}/backends/${NAME}.h)
  add_library(${NAME} STATIC ${ROOT}/backends/${NAME}.cpp ${HEADER})
  target_link_libraries(${NAME} PUBLIC imgui)
  target_include_directories(${NAME} PUBLIC
    $<BUILD_INTERFACE:${ROOT}/backends>
    $<INSTALL_INTERFACE:include>)
  LIST(APPEND INSTALL_TARGETS ${NAME})
  LIST(APPEND INSTALL_HEADERS ${HEADER})
endforeach()

target_link_libraries(imgui_impl_glfw PRIVATE glfw)
