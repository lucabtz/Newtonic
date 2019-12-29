# This files builds the Newtonic shared library

# Build Newtonic as shared library
file(GLOB newtonic-src "src/*.h" "src/*.cpp")
add_library(newtonic SHARED ${newtonic-src})

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
