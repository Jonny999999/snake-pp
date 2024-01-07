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

    # Specify downloaded SDL2_ttf library folder location
    set(SDL2_TTF_FOLDER "${CMAKE_SOURCE_DIR}/SDL2_ttf/")

    set(SDL2_TTF_INCLUDE_DIRS "${SDL2_TTF_FOLDER}/include")
    set(SDL_TTF_LIBRARIES "${SDL2_TTF_FOLDER}/lib/x64/SDL2_ttf.lib")
    set(SDL2_TTF_LIBS "${SDL2_TTF_FOLDER}/lib/x64/SDL2_ttf.lib")
    set(SDL2_TTF_DLLS "${SDL2_TTF_FOLDER}/lib/x64/SDL2_ttf.dll")
    set(SDL2_TTF_DIR "${SDL2_TTF_FOLDER}/cmake/")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${SDL2_TTF_FOLDER}")
endif()
# Note: On Linux, the libraries are found automatically if installed


# --- Locate SDL2 ---
# Uses SDL2_DIR on Windows, on Linux it's found automatically
find_package(SDL2 REQUIRED)

# --- Locate SDL2_ttf ---
find_package(SDL2_ttf REQUIRED)

#--- Include directories ---
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ./include ./src)


# --- Source files ---
# Add all used source files here:
set(SOURCES
    src/main.cpp
    src/config.c
    src/food.c
    src/game.c
    src/input.c
    src/menu.c
    src/render.c
    src/snake.c
    src/map.c
    src/common.c
    src/sound.c
    src/difficulty.c
    src/files.c
)


#--- executable ---
add_executable(Snake ${SOURCES})


#--- link libraries ---
if(WIN32)
    # Link libraries statically on Windows to prevent missing basic libraries on other systems.
    target_link_options(Snake PRIVATE -static)
    target_link_libraries(Snake ${SDL2_LIBRARIES} ${SDL_TTF_LIBRARIES})
else()
    target_link_libraries(Snake SDL2::SDL2 SDL2_ttf::SDL2_ttf)
endif()


# --- Copy assets to output folder ---
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})


# --- Copy SDL2 DLLs to the output folder on Windows ---
if(WIN32)
    foreach(DLL ${SDL2_DLLS} ${SDL2_TTF_DLLS})
        add_custom_command(TARGET Snake POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:Snake>)
    endforeach()
endif()




############################################
######## generate release .zip file ########
############################################
# Generate a distributable ZIP archive for sharing the game.
# Note: currently only intended for windows systems
# Usage:
#   1. Build the project: cd build && cmake .. && make
#   2. Generate ZIP file: cpack
#   3. Share the ZIP file for others to run the game effortlessly.
if(WIN32)
# generator for zip archive TODO add other generator e.g. installer
set(CPACK_GENERATOR "ZIP")

# Specify to exclude the top-level directory from the archive.
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY ON)

# Specify the components to be included in the package
install(TARGETS Snake
        RUNTIME DESTINATION .
        COMPONENT Runtime
)

# copy DLL files
install(FILES ${SDL2_DLLS} ${SDL2_TTF_DLLS}
        DESTINATION .
        COMPONENT Runtime
)
# copy assets folder
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets
        DESTINATION .
        COMPONENT Assets
)

include(CPack)
endif()