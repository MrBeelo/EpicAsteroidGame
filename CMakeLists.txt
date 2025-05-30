cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Set the program name as a variable
set(PROGRAM_NAME "MyProgram")

# User input for language (C or C++) and OS (win, linux, osx, web)
set(LANGUAGE "c" CACHE STRING "Choose language: c or cpp")
set(OS_TYPE "win" CACHE STRING "Choose OS: win, linux, osx, web")

# Set C or C++ flags based on user input
if(LANGUAGE STREQUAL "cpp")
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
elseif(LANGUAGE STREQUAL "c")
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED True)
else()
    message(FATAL_ERROR "Invalid language specified. Choose 'c' or 'cpp'.")
endif()

# Determine output and library directories based on OS
set(BUILD_DIR "build")
set(BIN_DIR "bin/${OS_TYPE}")
set(LIB_DIR "lib/${OS_TYPE}")
set(ASSETS_DIR "assets")

# Add the program source files from the src directory
file(GLOB SOURCES "src/*.c")  # This will grab all C files in src/
add_executable(${PROGRAM_NAME} ${SOURCES})

# Include Raylib headers (adjust the path if needed)
include_directories("/path/to/raylib/include")  # Adjust this to Raylib include path

# Link libraries from the lib/<os_I_chose> directory
file(GLOB LIBRARIES "${LIB_DIR}/*.so" "${LIB_DIR}/*.a" "${LIB_DIR}/*.dll" "${LIB_DIR}/*.lib")  # Modify for your library types
target_link_libraries(${PROGRAM_NAME} ${LIBRARIES} m)

# Set the runtime output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BIN_DIR})

# Copy the assets directory to the bin directory after the build
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Set the output directory for binaries
set_target_properties(${PROGRAM_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Custom command for cleaning build directory
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/${BIN_DIR}
    COMMENT "Cleaning build and bin directories")

# Custom command for cleaning the bin directory
add_custom_target(clean-this
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BIN_DIR}
    COMMENT "Cleaning the bin directory")

# Custom command for running the program
add_custom_target(run
    COMMAND ${BIN_DIR}/${PROGRAM_NAME}
    DEPENDS ${PROGRAM_NAME}
    COMMENT "Running the program")

# Add custom targets to be available in the cmake command
add_dependencies(run ${PROGRAM_NAME})
