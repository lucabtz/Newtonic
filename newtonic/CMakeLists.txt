# This files builds the Newtonic shared library

# Build Newtonic as shared library
file(GLOB newtonic-src "src/*.h" "src/*.cpp" "src/renderer/*.h" "src/renderer/*.cpp")

add_library(newtonic SHARED ${newtonic-src})

target_link_libraries(newtonic PRIVATE stb_image)
target_include_directories(newtonic PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/stb_image/")

# Debug build options
if(debug)
  target_compile_options(newtonic PRIVATE -ggdb)
endif()

# Sets the warnings
target_compile_options(newtonic PUBLIC -Wall)
target_compile_options(newtonic PUBLIC -Wextra)
target_compile_options(newtonic PUBLIC -pedantic)

# Use C++17
target_compile_options(newtonic PUBLIC --std=c++17)
