cmake_minimum_required(VERSION 3.2)

project(Newtonic VERSION 0.0.1)

set(debug, true)

# Newtonic shared lib
add_subdirectory(newtonic)

# Newtonic playground
add_subdirectory(playground)
