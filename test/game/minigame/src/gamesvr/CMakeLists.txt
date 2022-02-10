
#源文件
aux_source_directory (. SRC_LIST)

#gamesvr
add_executable (gamesvr ${SRC_LIST})

#库文件
target_link_libraries (gamesvr ${COORD_LIB})
target_link_libraries (gamesvr ${LUA_LIB})
target_link_libraries (gamesvr ${TOLUA_LIB})
target_link_libraries (gamesvr ${HTTP_PARSER_LIB})
target_link_libraries (gamesvr ${PROTOBUF_LIB})
target_link_libraries (gamesvr ${UV_LIB})
target_link_libraries (gamesvr ${HIREDIS_LIB})
target_link_libraries (gamesvr ${MYSQLCLIENT_LIB})
target_link_libraries (gamesvr ${CCRONEXPR_LIB})
target_link_libraries (gamesvr ${CJSON_LIB})
target_link_libraries (gamesvr ssl)
target_link_libraries (gamesvr crypto)
target_link_libraries (gamesvr dl)
target_link_libraries (gamesvr m)
target_link_libraries (gamesvr ncurses)
target_link_libraries (gamesvr readline)
target_link_libraries (gamesvr pthread)

add_custom_target(gamesvr_tolua
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/gamesvr
    COMMAND ${PROJECT_SOURCE_DIR}/../../coord/bin/tolua++/tolua++ -n gamesvr -o interface.cc interface.pkg
)
