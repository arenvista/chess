cmake_minimum_required(VERSION 3.8)
project(my_project)

set(CMAKE_C_COMPILER g++)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# A globbing expression to capture all .c and .cpp files in the src directory, including subdirectories
file(GLOB_RECURSE sources
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/pieces/*.cpp"
)

# Add precompiler definitions like that:
add_definitions(-DSOME_DEFINITION)

# Create the executable target with the collected source files
add_executable(my_app ${sources})
set_target_properties(my_app PROPERTIES COMPILE_FLAGS "-g")

# Add the base 'src' directory and the 'src/pieces' sub-directory to the include path
target_include_directories(my_app PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/pieces"
)

