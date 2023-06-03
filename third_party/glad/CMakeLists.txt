add_library(glad src/gl.c)

target_include_directories(glad PRIVATE ${GLAD_INCLUDE_DIR})
