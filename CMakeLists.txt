# CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(filevault VERSION 1.0 LANGUAGES CXX)

# Specify C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include/controllers ${PROJECT_SOURCE_DIR}/include/models ${PROJECT_SOURCE_DIR}/include/views)
file(GLOB_RECURSE SRCS src/*.cpp)
# Find the GTKmm 4 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
# Add executable
add_executable(${PROJECT_NAME} ${SRCS})



# Link GTKmm libraries
target_link_libraries(filevault PRIVATE ${GTKMM_LIBRARIES})

# Include GTKmm headers
target_include_directories(filevault PRIVATE ${GTKMM_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include/controllers ${PROJECT_SOURCE_DIR}/include/views ${PROJECT_SOURCE_DIR}/include/models)
include_directories(include/controllers include/views include/models src/)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(include/controllers include/views include/models)

# Set the compile options
target_compile_options(filevault PRIVATE ${GTKMM_CFLAGS_OTHER})

# Optionally add some additional configurations for GTKmm (e.g., for GTK+ themes)
# set_target_properties(filevault PROPERTIES
#   CXX_STANDARD 17
#   CXX_STANDARD_REQUIRED ON
# )

# Install target
install(TARGETS filevault DESTINATION bin)
