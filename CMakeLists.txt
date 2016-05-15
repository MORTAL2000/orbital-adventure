cmake_minimum_required(VERSION 2.8.0)
project(OA C CXX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(OA_SOURCES ${OA_SOURCE_DIR}/src)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(GLEW REQUIRED)
FIND_PACKAGE (Boost COMPONENTS filesystem system REQUIRED)


file(GLOB OA_SOURCE_FILES ${OA_SOURCES}/*.cpp) 
file(GLOB ENGINE_SOURCE_FILES ${OA_SOURCES}/engine/src/*.cpp) 
set(EngineIncludes ${OA_SOURCES}/engine/)
include_directories(
    ${GLFW_INCLUDE_DIRS}
    ${EngineIncludes}
    )



add_executable(orbital-adventure 
    ${ENGINE_SOURCE_FILES}
    ${OA_SOURCE_FILES}
    )
set(libs ${OPENGL_LIBRARY} 
    ${Boost_LIBRARIES}
    ${PNG_LIBRARIES} 
    ${JPEG_LIBRARIES}
    ${GLEW_LIBRARIES} 
    ${GLFW_STATIC_LIBRARIES} 
)
target_link_libraries(orbital-adventure ${libs})

