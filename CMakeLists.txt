cmake_minimum_required(VERSION 3.0.2)
project(OA C CXX)
include(ExternalProject)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
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


add_subdirectory(${OA_EXTS}/nanogui)
set(rocket_includes ${OA_EXTS}/libRocket/Include)


file(GLOB OA_SOURCE_FILES ${OA_SOURCES}/*.cpp) 
file(GLOB ENGINE_SOURCE_FILES ${OA_SOURCES}/engine/src/*.cpp) 
file(GLOB Celestial_SOURCE_FILES ${OA_SOURCES}/Celestial/*.cpp) 
file(GLOB GUI_SOURCE_FILES ${OA_SOURCES}/Gui/*.cpp) 
set(EngineIncludes ${OA_SOURCES}/engine/)
include_directories(
    ${GLFW_INCLUDE_DIRS}
    ${rocket_includes}
    ${EngineIncludes}
    )



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
    nanogui
)
target_link_libraries(orbital-adventure ${libs})

