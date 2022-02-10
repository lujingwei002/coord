
#源文件
aux_source_directory (. SRC_LIST)

#loginsvr
add_executable (loginsvr ${SRC_LIST})

#库文件
target_link_libraries (loginsvr ${COORD_LIB})
target_link_libraries (loginsvr ${LUA_LIB})
target_link_libraries (loginsvr ${TOLUA_LIB})
target_link_libraries (loginsvr ${HTTP_PARSER_LIB})
target_link_libraries (loginsvr ${PROTOBUF_LIB})
target_link_libraries (loginsvr ${UV_LIB})
target_link_libraries (loginsvr ${HIREDIS_LIB})
target_link_libraries (loginsvr ${MYSQLCLIENT_LIB})
target_link_libraries (loginsvr ${CCRONEXPR_LIB})
target_link_libraries (loginsvr ${CJSON_LIB})
target_link_libraries (loginsvr ssl)
target_link_libraries (loginsvr crypto)
target_link_libraries (loginsvr dl)
target_link_libraries (loginsvr m)
target_link_libraries (loginsvr ncurses)
target_link_libraries (loginsvr readline)
target_link_libraries (loginsvr pthread)

add_custom_target(loginsvr_tolua
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/loginsvr
    COMMAND ${PROJECT_SOURCE_DIR}/../../coord/bin/tolua++/tolua++ -n loginsvr -o interface.cc interface.pkg
)
