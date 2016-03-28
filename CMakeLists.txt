cmake_minimum_required(VERSION 3.0.0)
project(OA C CXX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(OA_SOURCES ${OA_SOURCE_DIR}/src)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(jpeg REQUIRED)
find_package(png REQUIRED)
find_package(glew REQUIRED)
FIND_PACKAGE (Boost COMPONENTS filesystem system REQUIRED)


file(GLOB OA_SOURCE_FILES ${OA_SOURCES}/*.cpp) 
include_directories(${GLFW_INCLUDE_DIRS})



add_executable(orbital-adventure ${OA_SOURCE_FILES})
set(libs ${OPENGL_LIBRARY} 
    ${GLFW_LIBRARIES} 
    ${Boost_LIBRARIES}
    ${PNG_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    ${JPEG_LIBRARIES})
target_link_libraries(orbital-adventure ${libs})

