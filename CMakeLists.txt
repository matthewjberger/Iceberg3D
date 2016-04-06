cmake_minimum_required(VERSION 3.0)
project(Iceberg3D)

# Version
set (Iceberg3D_VERSION_MAJOR 0)
set (Iceberg3D_VERSION_MINOR 1)

# Assimp
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Iceberg3D/dependencies/assimp)

# Bullet
option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
option(BUILD_EXTRAS OFF)
add_subdirectory(Iceberg3D/dependencies/bullet)

# GLFW
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Iceberg3D/dependencies/glfw)

# Set warning level
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O -Wall -Weffc++ -pedantic  \
											-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
											-Wcast-qual -Wconversion \
											-Wdisabled-optimization \
											-Werror -Wfloat-equal -Wformat=2 \
											-Wformat-nonliteral -Wformat-security  \
											-Wformat-y2k \
											-Wimplicit  -Wimport  -Winit-self  -Winline \
											-Winvalid-pch   \
											-Wlong-long \
											-Wmissing-field-initializers -Wmissing-format-attribute   \
											-Wmissing-include-dirs -Wmissing-noreturn \
											-Wpacked  -Wpadded -Wpointer-arith \
											-Wredundant-decls \
											-Wshadow -Wstack-protector \
											-Wstrict-aliasing=2 -Wswitch-default \
											-Wswitch-enum \
											-Wunreachable-code -Wunused \
											-Wunused-parameter \
											-Wvariadic-macros \
											-Wwrite-strings \
											-std=c++14")
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

# Set up file globs					
file(GLOB DEPENDENCY_SOURCES Iceberg3D/dependencies/glad/src/glad.c)
file(GLOB PROJECT_FILES Iceberg3D/source/*.*)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

# Specify source groupings
source_group("source" FILES ${PROJECT_FILES})
source_group("dependencies" FILES ${DEPENDENCY_SOURCES})

# Add linker flags
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

# Add an executable target				
add_executable(${PROJECT_NAME} ${PROJECT_FILES}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${DEPENDENCY_SOURCES})

# Specify static link libraries for the linker							   
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)

# Set the output directory of the project					  
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Specify post-build event to copy application resources to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>)