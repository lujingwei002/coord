MAKE=make
 .DEFAULT_GOAL := default


LIBUV_VERSION=1.42.0
LIBUV_DIR=libuv-$(LIBUV_VERSION)
LIBUV_LIB=$(LIBUV_DIR)/libuv/lib/libuv.a

$(LIBUV_DIR):
	@echo
	@echo "=== Downloading libuv $(LIBUV_VERSION) ==="
	@echo
	curl "https://codeload.github.com/libuv/libuv/tar.gz/refs/tags/v$(LIBUV_VERSION)" | tar xz

$(LIBUV_LIB): $(LIBUV_DIR)
	cd $(LIBUV_DIR);./autogen.sh
	cd $(LIBUV_DIR);./configure --prefix=`pwd`/libuv
	mkdir -p $(LIBUV_DIR)/libuv
	$(MAKE) -C $(LIBUV_DIR) 
	$(MAKE) -C $(LIBUV_DIR) install

$(LIBUV_DIR)/clean:
	$(MAKE) -C $(LIBUV_DIR) clean

$(LIBUV_DIR)/install:
	@echo
	@echo '=== install libuv ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(LIBUV_LIB) ../lib 
	rm -rf ../include/uv
	cp -rf $(LIBUV_DIR)/libuv/include/* ../include/


HIREDIS_VERSION=1.0.0
HIREDIS_DIR=hiredis-$(HIREDIS_VERSION)
HIREDIS_LIB=$(HIREDIS_DIR)/libhiredis.a

$(HIREDIS_DIR):
	@echo
	@echo "=== Downloading hiredis $(HIREDIS_VERSION) ==="
	@echo
	curl "https://codeload.github.com/redis/hiredis/tar.gz/refs/tags/v$(HIREDIS_VERSION)" | tar xz

$(HIREDIS_LIB): $(HIREDIS_DIR)
	$(MAKE) -C $(HIREDIS_DIR) 

$(HIREDIS_DIR)/clean:
	$(MAKE) -C $(HIREDIS_DIR) clean

$(HIREDIS_DIR)/install:
	@echo
	@echo '=== install hiredis ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(HIREDIS_LIB) ../lib 
	rm -rf ../include/hiredis;mkdir ../include/hiredis
	cp -rf $(HIREDIS_DIR)/*.h ../include/hiredis/
	cp -rf $(HIREDIS_DIR)/adapters ../include/hiredis/

HTTPPARSER_VERSION=2.9.4
HTTPPARSER_DIR=http-parser-$(HTTPPARSER_VERSION)
HTTPPARSER_LIB=$(HTTPPARSER_DIR)/libhttp_parser.a



$(HTTPPARSER_DIR):
	@echo
	@echo "=== Downloading http-parser $(HTTPPARSER_VERSION) ==="
	@echo
	curl "https://codeload.github.com/nodejs/http-parser/tar.gz/refs/tags/v$(HTTPPARSER_VERSION)" | tar xz

$(HTTPPARSER_LIB): $(HTTPPARSER_DIR)
	$(MAKE) -C $(HTTPPARSER_DIR) package

$(HTTPPARSER_DIR)/clean:
	$(MAKE) -C $(HTTPPARSER_DIR) clean

$(HTTPPARSER_DIR)/install:
	@echo
	@echo '=== install http-parser ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(HTTPPARSER_LIB) ../lib 
	rm -rf ../include/http-parser;mkdir ../include/http-parser
	cp -rf $(HTTPPARSER_DIR)/*.h ../include/http-parser




LUA_VERSION=5.1
LUA_DIR=lua-$(LUA_VERSION)
LUA_LIB=$(LUA_DIR)/src/liblua.a

$(LUA_DIR):
	@echo
	@echo "=== Downloading lua $(LUA_VERSION) ==="
	@echo
	curl "https://www.lua.org/ftp/lua-$(LUA_VERSION).tar.gz" | tar xz

$(LUA_LIB): $(LUA_DIR)
	$(MAKE) -C $(LUA_DIR) linux
	@mkdir -p ../lib
	cp $(LUA_LIB) ../lib 

$(LUA_DIR)/clean:
	$(MAKE) -C $(LUA_DIR) clean

$(LUA_DIR)/install:
	@echo
	@echo '=== install lua ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(LUA_LIB) ../lib 
	rm -rf ../include/lua;mkdir ../include/lua
	cp -rf $(LUA_DIR)/src/*.h ../include/lua



TOLUA_VERSION=1.0.92
TOLUA_DIR=tolua++-$(TOLUA_VERSION)
TOLUA_LIB=$(TOLUA_DIR)/tolua++.a

$(TOLUA_DIR):
	@echo
	@echo "=== Downloading tolua++ $(TOLUA_VERSION) ==="
	@echo
	tar xzf archive/tolua++-$(TOLUA_VERSION).tar.gz

$(TOLUA_LIB): $(TOLUA_DIR)
	$(MAKE) -C $(TOLUA_DIR) 

$(TOLUA_DIR)/clean:
	$(MAKE) -C $(TOLUA_DIR) clean

$(TOLUA_DIR)/install:
	@echo
	@echo '=== install tolua++ ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	@mkdir -p ../bin
	cp $(TOLUA_LIB) ../lib/libtolua++.a
	rm -rf ../include/tolua++;mkdir ../include/tolua++
	cp -rf $(TOLUA_DIR)/*.h ../include/tolua++
	rm -rf ../bin/tolua++;mkdir ../bin/tolua++
	cp -rf $(TOLUA_DIR)/tolua++ ../bin/tolua++
	cp -rf $(TOLUA_DIR)/testfile ../bin/tolua++
	cp -rf $(TOLUA_DIR)/tests ../bin/tolua++
	cp -rf $(TOLUA_DIR)/lua ../bin/tolua++



PROTOBUF_VERSION=3.17.1
PROTOBUF_DIR=protobuf-$(PROTOBUF_VERSION)
PROTOBUF_LIB=$(PROTOBUF_DIR)/libprotobuf/lib/libprotobuf.a

$(PROTOBUF_DIR):
	@echo
	@echo "=== Downloading protobuf $(PROTOBUF_VERSION) ==="
	@echo
	curl "https://codeload.github.com/protocolbuffers/protobuf/tar.gz/refs/tags/v$(PROTOBUF_VERSION)" | tar xz

$(PROTOBUF_LIB): $(PROTOBUF_DIR)
	cd $(PROTOBUF_DIR);./autogen.sh
	cd $(PROTOBUF_DIR);./configure --prefix=`pwd`/libprotobuf
	$(MAKE) -C $(PROTOBUF_DIR) 
	$(MAKE) -C $(PROTOBUF_DIR) install

$(PROTOBUF_DIR)/clean:
	$(MAKE) -C $(PROTOBUF_DIR) clean

$(PROTOBUF_DIR)/install:
	@echo
	@echo '=== install protobuf ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	@mkdir -p ../bin
	@mkdir -p ../include/google
	cp $(PROTOBUF_LIB) ../lib
	cp $(PROTOBUF_DIR)/libprotobuf/bin/protoc ../bin/protoc
	rm -rf ../include/google/protobuf
	cp -rf $(PROTOBUF_DIR)/libprotobuf/include/google/protobuf ../include/google


GTEST_VERSION=1.11.0
GTEST_DIR=googletest-release-$(GTEST_VERSION)
GTEST_LIB=$(GTEST_DIR)/build/lib/libgtest.a

$(GTEST_DIR):
	@echo
	@echo "=== Downloading Google Test $(GTEST_VERSION) ==="
	@echo
	curl "https://codeload.github.com/google/googletest/tar.gz/refs/tags/release-$(GTEST_VERSION)" | tar xz

$(GTEST_LIB): $(GTEST_DIR)
	mkdir -p $(GTEST_DIR)/build
	cd $(GTEST_DIR)/build;cmake ..
	$(MAKE) -C $(GTEST_DIR)/build 

$(GTEST_DIR)/clean:
	$(MAKE) -C $(GTEST_DIR) clean

$(GTEST_DIR)/install:
	@echo
	@echo '=== install Google Test ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(GTEST_DIR)/build/lib/libgmock.a ../lib 
	cp $(GTEST_DIR)/build/lib/libgmock_main.a ../lib 
	cp $(GTEST_DIR)/build/lib/libgtest.a ../lib 
	cp $(GTEST_DIR)/build/lib/libgtest_main.a ../lib 
	rm -rf ../include/gtest
	cp -rf $(GTEST_DIR)/googletest/include/gtest ../include/
	cp -rf $(GTEST_DIR)/googlemock/include/gmock ../include/


BENCHMARK_VERSION=1.6.1
BENCHMARK_DIR=benchmark-$(BENCHMARK_VERSION)
BENCHMARK_LIB=$(BENCHMARK_DIR)/build/src/libbenchmark.a

$(BENCHMARK_DIR):
	@echo
	@echo "=== Downloading Benchmark $(BENCHMARK_VERSION) ==="
	@echo
	curl "https://codeload.github.com/google/benchmark/tar.gz/refs/tags/v$(BENCHMARK_VERSION)" | tar xz

$(BENCHMARK_LIB): $(BENCHMARK_DIR)
	cd $(BENCHMARK_DIR);cmake3 -E make_directory "build"
	cd $(BENCHMARK_DIR);cmake3 -E chdir "build" cmake3 -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_GTEST_TESTS=OFF ../
	cd $(BENCHMARK_DIR);cmake3 -DCMAKE_BUILD_TYPE=Release -S . -B "build"
	cd $(BENCHMARK_DIR);cmake3 --build "build" --config Release 

$(BENCHMARK_DIR)/clean:
	$(MAKE) -C $(BENCHMARK_DIR) clean

$(BENCHMARK_DIR)/install:
	@echo
	@echo '=== install Benchmark ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(BENCHMARK_LIB) ../lib 
	rm -rf ../include/benchmark
	cp -rf $(BENCHMARK_DIR)/include/benchmark ../include/



CCRONEXPR_VERSION=20190415
CCRONEXPR_DIR=ccronexpr-$(CCRONEXPR_VERSION)
CCRONEXPR_LIB=$(CCRONEXPR_DIR)/libccronexpr.a

$(CCRONEXPR_DIR):
	@echo
	@echo "=== Downloading ccronexpr $(CCRONEXPR_VERSION) ==="
	@echo
	curl "https://codeload.github.com/staticlibs/ccronexpr/tar.gz/refs/tags/v$(CCRONEXPR_VERSION)" | tar xz

$(CCRONEXPR_LIB): $(CCRONEXPR_DIR)
	cp -rf ccronexpr/makefile $(CCRONEXPR_DIR)
	$(MAKE) -C $(CCRONEXPR_DIR)

$(CCRONEXPR_DIR)/clean:
	$(MAKE) -C $(CCRONEXPR_DIR) clean

$(CCRONEXPR_DIR)/install:
	@echo
	@echo '=== install ccronexpr ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(CCRONEXPR_DIR)/libccronexpr.a ../lib 
	rm -rf ../include/ccronexpr;mkdir -p ../include/ccronexpr
	cp -rf $(CCRONEXPR_DIR)/*.h ../include/ccronexpr

JSON_VERSION=3.10.5
JSON_DIR=json-$(JSON_VERSION)

$(JSON_DIR):
	@echo
	@echo "=== Downloading nlohmann json $(JSON_VERSION) ==="
	@echo
	curl "https://codeload.github.com/nlohmann/json/tar.gz/refs/tags/v$(JSON_VERSION)" | tar xz

$(JSON_DIR)/install:
	@echo
	@echo '=== install nlohmann json ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	rm -rf ../include/json;mkdir -p ../include/json
	cp -rf $(JSON_DIR)/single_include/nlohmann/*.hpp ../include/json

MYSQL_VERSION=c64
MYSQL_DIR=mysql-connector-$(MYSQL_VERSION)
MYSQL_LIB=$(MYSQL_DIR)/lib/libmysqlclient.a

$(MYSQL_DIR):
	@echo
	@echo "=== Downloading mysql connector $(MYSQL_VERSION) ==="
	@echo
	tar xzf archive/mysql-connector-$(MYSQL_VERSION).tar.gz

$(MYSQL_DIR)/install:
	@echo
	@echo '=== install mysql connector ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(MYSQL_LIB) ../lib 
	rm -rf ../include/mysql
	cp -rf $(MYSQL_DIR)/include/ ../include/mysql

INIPP_VERSION=1.0.12
INIPP_DIR=inipp-$(INIPP_VERSION)

$(INIPP_DIR):
	@echo
	@echo "=== Downloading mcmtroffaes inipp $(INIPP_VERSION) ==="
	@echo
	curl "https://codeload.github.com/mcmtroffaes/inipp/tar.gz/refs/tags/$(INIPP_VERSION)" | tar xz

$(INIPP_DIR)/install:
	@echo
	@echo '=== install mcmtroffaes inipp ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	rm -rf ../include/inipp;mkdir -p ../include/inipp
	cp -rf $(INIPP_DIR)/inipp/*.h ../include/inipp

JSON11_VERSION=1.0.0
JSON11_DIR=json11-$(JSON11_VERSION)

$(JSON11_DIR):
	@echo
	@echo "=== Downloading dropbox json11 $(JSON11_VERSION) ==="
	@echo
	curl "https://codeload.github.com/dropbox/json11/tar.gz/refs/tags/v$(JSON11_VERSION)" | tar xz

$(JSON11_DIR)/install:
	@echo
	@echo '=== install dropbox json11 ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	rm -rf ../src/json11;mkdir -p ../src/json11
	cp -rf $(JSON11_DIR)/*.hpp ../src/json11
	cp -rf $(JSON11_DIR)/*.cpp ../src/json11


CJSON_VERSION=2.1.0
CJSON_DIR=lua-cjson-$(CJSON_VERSION)
CJSON_LIB=$(CJSON_DIR)/libcjson.a

$(CJSON_DIR):
	@echo
	@echo "=== Downloading mpx cjson $(CJSON_VERSION) ==="
	@echo
	curl "https://codeload.github.com/mpx/lua-cjson/tar.gz/refs/tags/$(CJSON_VERSION)" | tar xz

$(CJSON_LIB): $(CJSON_DIR)
	cp -rf lua-cjson/Makefile $(CJSON_DIR)
	cp -rf lua-cjson/lua_cjson.c $(CJSON_DIR)
	$(MAKE) -C $(CJSON_DIR)

$(CJSON_DIR)/install:
	@echo
	@echo '=== install mpx cjson ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(CJSON_LIB) ../lib 
	rm -rf ../include/lua-cjson;mkdir -p ../include/lua-cjson
	cp -rf lua-cjson/lua_cjson.h ../include/lua-cjson

ARGPARSE_VERSION=2.5
ARGPARSE_DIR=argparse-$(ARGPARSE_VERSION)
ARGPARSE_LIB=$(ARGPARSE_DIR)/libargparse.a

$(ARGPARSE_DIR):
	@echo
	@echo "=== Downloading mpx argparse $(ARGPARSE_VERSION) ==="
	@echo
	curl "https://github.com/p-ranav/argparse/archive/refs/tags/v$(ARGPARSE_VERSION).tar.gz" | tar xz

$(ARGPARSE_DIR)/install:
	@echo
	@echo '=== install p-ranav/argparse ==='
	@echo
	@mkdir -p ../include
	rm -rf ../include/argparse;mkdir -p ../include/argparse
	cp -rf $(ARGPARSE_DIR)/include/argparse/argparse.hpp ../include/argparse/argparse.hpp

fetch: $(HIREDIS_DIR) $(HTTPPARSER_DIR) $(LUA_DIR) $(PROTOBUF_DIR) $(TOLUA_DIR) $(GTEST_DIR) $(LIBUV_DIR) $(CCRONEXPR_DIR) $(BENCHMARK_DIR) $(INIPP_DIR) $(JSON_DIR) $(MYSQL_DIR) $(INIPP_DIR) $(JSON11_DIR) $(CJSON_DIR) $(ARGPARSE_DIR)

default: $(HIREDIS_LIB) $(HTTPPARSER_LIB) $(LUA_LIB) $(PROTOBUF_LIB) $(TOLUA_LIB) $(GTEST_LIB) $(LIBUV_LIB) $(CCRONEXPR_LIB) $(BENCHMARK_LIB) $(CJSON_LIB)

install: $(HIREDIS_DIR)/install $(HTTPPARSER_DIR)/install $(LUA_DIR)/install $(PROTOBUF_DIR)/install $(TOLUA_DIR)/install $(GTEST_DIR)/install $(LIBUV_DIR)/install $(CCRONEXPR_DIR)/install $(BENCHMARK_DIR)/install $(JSON_DIR)/install $(MYSQL_DIR)/install $(INIPP_DIR)/install $(JSON11_DIR)/install $(CJSON_DIR)/install $(ARGPARSE_DIR)/install

.PYHON: default 

