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



set(ext_dir "${CMAKE_BINARY_DIR}/external")
set(nanovg_sources_dir "${OA_SOURCE_DIR}/external/nanovg/src")
#set(librocket_dir "${ext_dir}/libRocket")
#ExternalProject_Add(libRocket 
#GIT_REPOSITORY https://github.com/libRocket/libRocket
#SOURCE_DIR "${librocket_dir}"
#)

#add_subdirectory(${OA_EXTS}/libRocket/Build)
#set(rocket_includes ${OA_EXTS}/libRocket/Include)


file(GLOB OA_SOURCE_FILES ${OA_SOURCES}/*.cpp) 
file(GLOB ENGINE_SOURCE_FILES ${OA_SOURCES}/engine/src/*.cpp) 
file(GLOB Celestial_SOURCE_FILES ${OA_SOURCES}/Celestial/*.cpp) 
file(GLOB GUI_SOURCE_FILES ${OA_SOURCES}/Gui/*.cpp) 
file(GLOB NANOVG_SOURCE_FILES ${nanovg_sources_dir}/*.c) 
set(EngineIncludes ${OA_SOURCES}/engine/)
set(NanoVGIncludes ${nanovg_sources_dir})
message(DEBUG ${nanovg_sources_dir})
include_directories(
    ${GLFW_INCLUDE_DIRS}
    ${rocket_includes}
    ${EngineIncludes}
    ${NanoVGIncludes}
    )



add_executable(orbital-adventure 
    ${ENGINE_SOURCE_FILES}
    ${Celestial_SOURCE_FILES}
    ${GUI_SOURCE_FILES}
    ${OA_SOURCE_FILES}
    ${NANOVG_SOURCE_FILES}
    )
set(libs ${OPENGL_LIBRARY} 
    ${Boost_LIBRARIES}
    ${PNG_LIBRARIES} 
    ${JPEG_LIBRARIES}
    ${GLEW_LIBRARIES} 
    ${GLFW_STATIC_LIBRARIES} 
    #   RocketCore
    #RocketControls
    #RocketDebugger
)
target_link_libraries(orbital-adventure ${libs})

