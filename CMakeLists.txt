cmake_minimum_required(VERSION 3.0.2)
project(OA C CXX)
include(ExternalProject)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated -Wno-deprecated-declarations -Wall -Wextra")
set(OA_SOURCES ${OA_SOURCE_DIR}/src)
set(OA_EXTS ${OA_SOURCE_DIR}/external)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(GLEW REQUIRED)
FIND_PACKAGE (Boost COMPONENTS filesystem system REQUIRED)



if(APPLE)
    message(STATUS "Prepare Awesonium for mac os x")
else()
    if(WIN32)
    message(STATUS "Prepare Awesonium for win32")
    else()
        message(STATUS "Prepare awesonium for LINUX system")
        set(AWESONIUM_PATH ${OA_SOURCE_DIR}/external/awesomium/linux/)
        set(AWESONIUM_LIBS "awesomium-1-7")
        set(AWESONIUM_INCLUDE ${OA_SOURCE_DIR}/external/awesomium/include/)
    endif()
endif()
    

file(GLOB OA_SOURCE_FILES ${OA_SOURCES}/*.cpp) 
file(GLOB ENGINE_SOURCE_FILES ${OA_SOURCES}/engine/src/*.cpp) 
file(GLOB Celestial_SOURCE_FILES ${OA_SOURCES}/Celestial/*.cpp) 
file(GLOB GUI_SOURCE_FILES ${OA_SOURCES}/Gui/*.cpp) 
set(EngineIncludes ${OA_SOURCES}/engine/)

include_directories(
    ${GLFW_INCLUDE_DIRS}
    ${nanogui_includes}
    ${EngineIncludes}
    )

link_directories(${AWESONIUM_PATH})
add_executable(orbital-adventure 
    ${ENGINE_SOURCE_FILES}
    ${Celestial_SOURCE_FILES}
    ${GUI_SOURCE_FILES}
    ${OA_SOURCE_FILES}
    )

set(libs ${OPENGL_LIBRARY} 
    ${Boost_LIBRARIES}
    ${PNG_LIBRARIES} 
    ${JPEG_LIBRARIES}
    ${GLEW_LIBRARIES} 
    ${GLFW_STATIC_LIBRARIES} 
    ${AWESONIUM_LIBS} 
)
message(DEBUG ${AWESONIUM_PATH})

target_link_libraries(orbital-adventure ${libs})

