cmake_minimum_required(VERSION 3.0)
project(Iceberg3D)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

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

add_subdirectory(Iceberg3D/dependencies/boxer)

add_subdirectory(Iceberg3D/dependencies/freetype2)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    # Hide the console in visual studio projects in debug and release
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O -w")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories( Iceberg3D/include/
                    Iceberg3D/dependencies/assimp/include/
					Iceberg3D/dependencies/boxer/include/
                    Iceberg3D/dependencies/bullet/src/
					Iceberg3D/dependencies/freetype2/include/
                    Iceberg3D/dependencies/glad/include/
                    Iceberg3D/dependencies/glfw/include/
                    Iceberg3D/dependencies/glm/
                    Iceberg3D/dependencies/stb/)

file(GLOB DEPENDENCY_SOURCES Iceberg3D/dependencies/glad/src/glad.c)
file(GLOB PROJECT_HEADERS Iceberg3D/include/*.*)
file(GLOB PROJECT_SOURCES Iceberg3D/source/*.*)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Dependencies" FILES ${DEPENDENCY_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_library(${PROJECT_NAME} ${PROJECT_HEADERS}
							${PROJECT_SOURCES}
                            ${PROJECT_SHADERS}
                            ${PROJECT_CONFIGS}
                            ${DEPENDENCY_SOURCES})

target_link_libraries(${PROJECT_NAME} assimp glfw Boxer freetype
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)

if (BUILD_SHARED_LIBS)
	target_compile_definitions( ${PROJECT_NAME} PRIVATE "ICEBERG_BUILD_DLL")
	target_compile_definitions( ${PROJECT_NAME} INTERFACE "ICEBERG_DLL")
endif()

option (ICEBERG_BUILD_SANDBOX "Build testing sandbox" OFF)
if (ICEBERG_BUILD_SANDBOX)
	add_subdirectory(Sandbox/)
endif()

option (ICEBERG_BUILD_DEMOS "Build demo programs" OFF)
if (ICEBERG_BUILD_DEMOS)
	add_subdirectory(Demos/full_scene/)
	add_subdirectory(Demos/basic_triangle/)
	add_subdirectory(Demos/textured_quad/)
endif()
