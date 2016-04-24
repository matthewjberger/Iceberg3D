cmake_minimum_required(VERSION 3.0)
project(Iceberg3D_Demo_Basic_Triangle)

# Group files
file(GLOB PROJECT_HEADERS *.h)
file(GLOB PROJECT_SOURCES *.cpp)
file(GLOB PROJECT_SHADERS resources/shaders/*.glsl)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

# Specify Visual Studio solution filters				 
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})

# Specify the executable to create using the file globs 
add_executable(${PROJECT_NAME} ${PROJECT_HEADERS}
			       ${PROJECT_SOURCES}
                               ${PROJECT_SHADERS}
                               ${PROJECT_CONFIGS})
# Link against Iceberg3D
target_link_libraries(${PROJECT_NAME} Iceberg3D)

# This will add a post-build event to copy the "resources" folder to the output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>)
