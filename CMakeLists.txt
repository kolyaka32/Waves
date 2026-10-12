# Setting minimum required for cmake versions
cmake_minimum_required(VERSION 3.5)

# Setting minimal c++ version for work
set(CMAKE_CXX_STANDARD 14)

# Creating project
project(Waves)

# Special for windows
if (WIN32)
    # Hidding console, static linking, all flags, remove debug
    set(CMAKE_CXX_FLAGS "-mwindows -static -Wall -s")
else (WIN32)
    set(CMAKE_CXX_FLAGS "-static -Wall -s")
endif (WIN32)

# Setting to link standart libraries statickly
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

# Add all source files (that needed) under the src directory
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.rc")
add_executable(${PROJECT_NAME} ${SOURCES})


# Look for a SDL3 library (static variant)
# Special for windows
if (WIN32)
    find_package(SDL3 REQUIRED PATHS "C:/Program Files (x86)/SDL3-static/lib/cmake/SDL3" NO_DEFAULT_PATH)
else (WIN32)
    find_package(SDL3 REQUIRED)
endif (WIN32)

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-static)
