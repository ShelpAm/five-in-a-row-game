add_library(stb src/stb_image.cc)

target_include_directories(stb PRIVATE ${STB_INCLUDE_DIR})
