cmake_minimum_required (VERSION 2.8)
project (minigame)

#项目选项
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set (COORD_HOME "/root/coord/coord")

#编译选项
add_compile_options (-std=c++17 -Wall -O2 -g) 

#头文件
include_directories (${COORD_HOME}/src)
include_directories (${COORD_HOME}/include)
include_directories (${COORD_HOME}/include/lua)
include_directories (${COORD_HOME}/include/tolua++)
include_directories (${PROJECT_SOURCE_DIR}/src)

#库文件
find_library(COORD_LIB coord HINTS ${COORD_HOME}/lib/)
find_library(LUA_LIB lua HINTS ${COORD_HOME}/lib/)
find_library(TOLUA_LIB tolua++ HINTS ${COORD_HOME}/lib/)
find_library(HTTP_PARSER_LIB http_parser HINTS ${COORD_HOME}/lib/)
find_library(PROTOBUF_LIB protobuf HINTS ${COORD_HOME}/lib/)
find_library(UV_LIB uv HINTS ${COORD_HOME}/lib/)
find_library(HIREDIS_LIB hiredis HINTS ${COORD_HOME}/lib/)
find_library(MYSQLCLIENT_LIB mysqlclient HINTS ${COORD_HOME}/lib/)
find_library(CCRONEXPR_LIB ccronexpr HINTS ${COORD_HOME}/lib/)
find_library(CJSON_LIB cjson HINTS ${COORD_HOME}/lib/)

add_subdirectory (src/loginsvr)
add_subdirectory (src/gamesvr)
