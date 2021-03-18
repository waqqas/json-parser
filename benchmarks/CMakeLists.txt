project(benchmarks)

file(GLOB TEST_SOURCES *.cpp *.h)
add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${ANTLR4_SRC_FILES_JSON_PARSER})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

find_package(benchmark REQUIRED)
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# add directories for generated include files
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR} ${ANTLR4_INCLUDE_DIR} ${ANTLR4_INCLUDE_DIR_JSON_PARSER} )

add_dependencies( ${PROJECT_NAME} antlr4_static )

target_link_libraries( ${PROJECT_NAME} antlr4_static)
