cmake_minimum_required(VERSION 3.0)
project(Iceberg3D)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Iceberg3D/dependencies/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Iceberg3D/dependencies/assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(Iceberg3D/dependencies/bullet)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    # Hide the console in visual studio projects in debug and release
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O -w -std=c++14")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(Iceberg3D/source/
                    Iceberg3D/dependencies/assimp/include/
                    Iceberg3D/dependencies/bullet/src/
                    Iceberg3D/dependencies/glad/include/
                    Iceberg3D/dependencies/glfw/include/
                    Iceberg3D/dependencies/glm/
                    Iceberg3D/dependencies/stb/)

file(GLOB DEPENDENCY_SOURCES Iceberg3D/dependencies/glad/src/glad.c)
file(GLOB PROJECT_FILES Iceberg3D/source/*.*)
file(GLOB PROJECT_SHADERS Iceberg3D/resources/shaders/*.*)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Source" FILES ${PROJECT_FILES})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Dependencies" FILES ${DEPENDENCY_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${PROJECT_FILES}
                               ${PROJECT_SHADERS}
                               ${PROJECT_CONFIGS}
                               ${DEPENDENCY_SOURCES})

target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>)
