cmake_minimum_required(VERSION 3.12)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

SET (CMAKE_CXX_STANDARD 17)

project("json-parser")

find_package(antlr4-generator REQUIRED)
find_package(antlr4-runtime REQUIRED)

set(ANTLR4_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-4.9-complete.jar)

antlr4_generate(
json_parser
${CMAKE_CURRENT_SOURCE_DIR}/grammar/JSON.g4
BOTH
FALSE
TRUE
"json"
)


add_executable(${PROJECT_NAME} main.cpp ${ANTLR4_SRC_FILES_json_parser})
# add directories for generated include files
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR} ${ANTLR4_INCLUDE_DIR} ${ANTLR4_INCLUDE_DIR_json_parser} )

add_dependencies( ${PROJECT_NAME} antlr4_static )

target_link_libraries( ${PROJECT_NAME} PRIVATE antlr4_static)