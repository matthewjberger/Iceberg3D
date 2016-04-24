cmake_minimum_required(VERSION 3.0)
project(Iceberg3D_Full_Scene_Example)

file(GLOB PROJECT_HEADERS *.h)
file(GLOB PROJECT_SOURCES *.cpp)
file(GLOB PROJECT_SHADERS resources/shaders/*.glsl)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)
						 
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS}
			       ${PROJECT_SOURCES}
                               ${PROJECT_SHADERS}
                               ${PROJECT_CONFIGS})

target_link_libraries(${PROJECT_NAME} Iceberg3D)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>)