cmake_minimum_required(VERSION 3.2)

project(Newtonic VERSION 0.0.1)

set(DEBUG, true)
set(BUILD_PLAYGROUND, true)

# third party code
add_subdirectory(thirdparty)

# Newtonic shared lib
add_subdirectory(newtonic)

# Newtonic playground
if (BUILD_PLAYGROUND)
  add_subdirectory(playground)
endif()
