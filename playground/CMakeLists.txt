# This file builds the Newtonic playground executable

file(GLOB playground-src "src/*.h" "src/*.cpp")

# Debug build options
if(debug)
  target_compile_options(newtonic PRIVATE -ggdb)
endif()

add_executable(application ${playground-src})
target_include_directories(application PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../newtonic")
target_link_libraries(application PRIVATE newtonic)
target_link_libraries(application PRIVATE -lassimp)
target_link_libraries(application PRIVATE -lGL -lGLEW -lglfw -lstdc++fs)
