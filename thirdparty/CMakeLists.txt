
file(GLOB stbimage-src "stb_image/*.c" "stb_image/*.h")

add_library(stb_image STATIC ${stbimage-src})
