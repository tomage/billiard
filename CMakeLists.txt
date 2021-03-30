cmake_minimum_required( VERSION 3.0 )

set (CMAKE_CPP_STANDARD 17)

project( billiard )

# include files
include_directories(
    ./src
)

# target
add_executable(
    billiard
    ./src/main.cpp
    ./src/Billiard.cpp
    ./src/Matrix.cpp
    ./src/OpenAL.cpp
    ./src/OpenGL.cpp
)

CONFIGURE_FILE(data/doink.wav doink.wav COPYONLY)
CONFIGURE_FILE(data/click.wav click.wav COPYONLY)

# 3rd party libs
SET(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenAL REQUIRED)

SET(ALUT_DIR ./tools)
find_package(ALUT REQUIRED)

target_link_libraries(
    billiard
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${OPENAL_LIBRARY}
    ${ALUT_LIBRARY}
)
