cmake_minimum_required(VERSION 3.17)
set(PROJ_NAME "serwer_graficzny")
project(${PROJ_NAME} LANGUAGES CXX VERSION 1.0.0)

cmake_policy(SET CMP0100 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS Core Widgets Xml OpenGL OpenGLWidgets)
if (Qt6_FOUND)
    message("Building with Qt6")
    set(QtLibs Qt::Core Qt::Widgets Qt::Xml Qt::OpenGL Qt::OpenGLWidgets)
else()
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Widgets Xml OpenGL)
    message("Building with Qt5")
    find_package(OpenGL REQUIRED)
    set(QtLibs Qt::Core Qt::Widgets Qt::Xml Qt::OpenGL ${OPENGL_LIBRARIES})
endif()

# find_library(SOIL NAMES SOIL REQUIRED)


include_directories(${PROJECT_SOURCE_DIR}/inc)
add_executable(${PROJECT_NAME}
           src/gsv-BufferedScene.cpp
           src/gsv-CommandBuffer.cpp
           src/gsv-CommandInterpreter.cpp
           src/gsv-Cuboid.cpp
           src/gsv-GeomParams.cpp
           inc/gsv-GraphicsWindow.hh
           src/gsv-GraphicsWindow.cpp
           src/gsv-GraphObject.cpp
           src/gsv-Map4DescGeomObjs.cpp
           src/gsv-Map4SceneGeomObjs.cpp
           src/gsv-Scene.cpp
           src/gsv-SceneServer.cpp
           src/gsv-ServerCommand.cpp
           src/gsv-Tests.cpp
           inc/gsv-WgViewer3D.hh	   
           src/gsv-WgViewer3D.cpp
           src/gtsDebug.cpp
           src/main.cpp
)
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wl,-rpath=./../libQGLViewer")

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE QGLViewer ${QtLibs} OpenGL::GL OpenGL::GLU)
target_link_libraries(${PROJECT_NAME} QGLViewer ${QtLibs} OpenGL::GL OpenGL::GLU)

add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJ_NAME} ..
     COMMAND ${CMAKE_COMMAND} -E echo ""
     COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal program:  ${PROJ_NAME}"
     COMMAND ${CMAKE_COMMAND} -E echo " Wywołanie programu: ./${PROJ_NAME}"
     COMMAND ${CMAKE_COMMAND} -E echo ""
)
