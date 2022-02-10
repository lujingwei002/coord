cmake_minimum_required (VERSION 2.8)
project (host)

#项目选项
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set (COORD_HOME "/root/coord/coord")

#编译选项
add_compile_options (-std=c++17 -Wall -O2) 

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


#源文件
aux_source_directory (src SRC_LIST)
aux_source_directory (src/hostd SRC_LIST)

#hostd
add_executable (hostd ${SRC_LIST})

#库文件
target_link_libraries (hostd ${COORD_LIB})
target_link_libraries (hostd ${LUA_LIB})
target_link_libraries (hostd ${TOLUA_LIB})
target_link_libraries (hostd ${HTTP_PARSER_LIB})
target_link_libraries (hostd ${PROTOBUF_LIB})
target_link_libraries (hostd ${UV_LIB})
target_link_libraries (hostd ${HIREDIS_LIB})
target_link_libraries (hostd ${MYSQLCLIENT_LIB})
target_link_libraries (hostd ssl)
target_link_libraries (hostd crypto)
target_link_libraries (hostd dl)
target_link_libraries (hostd m)
target_link_libraries (hostd ncurses)
target_link_libraries (hostd readline)
target_link_libraries (hostd pthread)


add_custom_target(tolua
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src
    COMMAND ../../../coord/bin/tolua++/tolua++ -n hostd -o interface.cc interface.pkg
)

add_custom_target(run
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND ${PROJECT_SOURCE_DIR}/bin/hostd config/hostd.ini
)

#add_dependencies (hostd tolua)

