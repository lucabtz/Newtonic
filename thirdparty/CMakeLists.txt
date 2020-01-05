
file(GLOB stbimage-src "stb_image/*.c" "stb_image/*.h")

add_library(stb_image STATIC ${stbimage-src})
target_compile_options(stb_image PRIVATE -fPIC)
