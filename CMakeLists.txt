cmake_minimum_required(VERSION 3.7)

project(Snake)


#--- SDL2 location on Windows ---
if(WIN32)
    # Specify downloaded SDL2 library folder location
    set(SDL2_FOLDER "${CMAKE_SOURCE_DIR}/SDL2/")

    set(SDL2_INCLUDE_DIRS "${SDL2_FOLDER}/include")
    set(SDL2_LIBS "${SDL2_FOLDER}/lib/x64/SDL2.lib")
    set(SDL2_DLLS "${SDL2_FOLDER}/lib/x64/SDL2.dll")
    set(SDL2_DIR "${SDL2_FOLDER}/cmake/")
    # On Linux, the library is found automatically if installed
endif()


# --- Locate SDL2 ---
# Uses SDL2_DIR on Windows, on Linux it's found automatically
find_package(SDL2 REQUIRED) 


#--- Include directories ---
include_directories(${SDL2_INCLUDE_DIRS} ./)


# --- Source files ---
# Note: When new files are added, CMake has to be re-run
# Alternatively, list files manually here
file(GLOB SOURCES
    "*.cpp"
    "*.c"
)
add_executable(Snake main.cpp)
target_link_libraries(Snake ${SDL2_LIBRARIES})


# --- Copy SDL2 DLLs to the output folder on Windows ---
if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET Snake POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:Snake>)
    endforeach()
endif()