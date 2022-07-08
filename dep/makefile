MAKE=make
 .DEFAULT_GOAL := default

CJSON_VERSION=2.1.0
JSON11_VERSION=1.0.0
INIPP_VERSION=1.0.12
MYSQL_VERSION=c64
JSON_VERSION=3.10.5
CCRONEXPR_VERSION=20190415
BENCHMARK_VERSION=1.6.1
GTEST_VERSION=1.11.0
PROTOBUF_VERSION=3.17.1
TOLUA_VERSION=1.0.92
LIBUV_VERSION=1.42.0
HIREDIS_VERSION=1.0.0
HTTPPARSER_VERSION=2.9.4
ARGPARSE_VERSION=2.6
LUA_VERSION=5.1

# ============================================= libuv ===================================================
LIBUV_DIR=libuv-$(LIBUV_VERSION)
LIBUV_LIB=$(LIBUV_DIR)/libuv/lib/libuv.a

$(LIBUV_DIR): archive/libuv-$(LIBUV_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(LIBUV_DIR)/download: archive/libuv-$(LIBUV_VERSION).tar.gz

archive/libuv-$(LIBUV_VERSION).tar.gz:
	@echo
	@echo "=== Downloading libuv $(LIBUV_VERSION) ==="
	@echo
	curl "https://codeload.github.com/libuv/libuv/tar.gz/refs/tags/v$(LIBUV_VERSION)" -o $@

$(LIBUV_LIB): $(LIBUV_DIR)
	cd $(LIBUV_DIR);./autogen.sh
	cd $(LIBUV_DIR);./configure --prefix=`pwd`/libuv
	mkdir -p $(LIBUV_DIR)/libuv
	$(MAKE) -C $(LIBUV_DIR) -j 10
	$(MAKE) -C $(LIBUV_DIR) install

$(LIBUV_DIR)/clean:
	$(MAKE) -C $(LIBUV_DIR) clean
	rm -rf $(LIBUV_DIR)/libuv

$(LIBUV_DIR)/remove:
	@rm -rf $(LIBUV_DIR) 

$(LIBUV_DIR)/install:
	@echo
	@echo '=== install libuv ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(LIBUV_LIB) ../lib 
	rm -rf ../include/uv
	cp -rf $(LIBUV_DIR)/libuv/include/* ../include/
# ============================================= libuv ===================================================


# ============================================= hiredis ===================================================
HIREDIS_DIR=hiredis-$(HIREDIS_VERSION)
HIREDIS_LIB=$(HIREDIS_DIR)/libhiredis.a

$(HIREDIS_DIR)/download: archive/hiredis-$(HIREDIS_VERSION).tar.gz

$(HIREDIS_DIR): archive/hiredis-$(HIREDIS_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

archive/hiredis-$(HIREDIS_VERSION).tar.gz:
	@echo
	@echo "=== Downloading hiredis $(HIREDIS_VERSION) ==="
	@echo
	curl "https://codeload.github.com/redis/hiredis/tar.gz/refs/tags/v$(HIREDIS_VERSION)" -o $@

$(HIREDIS_LIB): $(HIREDIS_DIR)
	$(MAKE) -C $(HIREDIS_DIR) 
	touch $@

$(HIREDIS_DIR)/clean:
	$(MAKE) -C $(HIREDIS_DIR) clean

$(HIREDIS_DIR)/remove:
	@rm -rf $(HIREDIS_DIR)

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
# ============================================= hiredis ===================================================


# ============================================= http-parser ===================================================
HTTPPARSER_DIR=http-parser-$(HTTPPARSER_VERSION)
HTTPPARSER_LIB=$(HTTPPARSER_DIR)/libhttp_parser.a

$(HTTPPARSER_DIR): archive/http-parser-$(HTTPPARSER_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(HTTPPARSER_DIR)/download: archive/http-parser-$(HTTPPARSER_VERSION).tar.gz

archive/http-parser-$(HTTPPARSER_VERSION).tar.gz:
	@echo
	@echo "=== Downloading http-parser $(HTTPPARSER_VERSION) ==="
	@echo
	curl "https://codeload.github.com/nodejs/http-parser/tar.gz/refs/tags/v$(HTTPPARSER_VERSION)" -o $@

$(HTTPPARSER_LIB): $(HTTPPARSER_DIR)
	$(MAKE) -C $(HTTPPARSER_DIR) package

$(HTTPPARSER_DIR)/clean:
	$(MAKE) -C $(HTTPPARSER_DIR) clean

$(HTTPPARSER_DIR)/remove:
	@rm -rf $(HTTPPARSER_DIR) 

$(HTTPPARSER_DIR)/install:
	@echo
	@echo '=== install http-parser ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(HTTPPARSER_LIB) ../lib 
	rm -rf ../include/http-parser;mkdir ../include/http-parser
	cp -rf $(HTTPPARSER_DIR)/*.h ../include/http-parser
# ============================================= http-parser ===================================================



# ============================================= lua ===================================================

LUA_DIR=lua-$(LUA_VERSION)
LUA_LIB=$(LUA_DIR)/src/liblua.a

$(LUA_DIR): archive/lua-$(LUA_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(LUA_DIR)/download: archive/lua-$(LUA_VERSION).tar.gz

archive/lua-$(LUA_VERSION).tar.gz:
	@echo
	@echo "=== Downloading lua $(LUA_VERSION) ==="
	@echo
	curl "https://www.lua.org/ftp/lua-$(LUA_VERSION).tar.gz" -o $@

$(LUA_LIB): $(LUA_DIR)
	$(MAKE) -C $(LUA_DIR) linux
	touch $@

$(LUA_DIR)/clean:
	$(MAKE) -C $(LUA_DIR) clean

$(LUA_DIR)/remove:
	@rm -rf $(LUA_DIR) 

$(LUA_DIR)/install:
	@echo
	@echo '=== install lua ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(LUA_LIB) ../lib 
	rm -rf ../include/lua;mkdir ../include/lua
	cp -rf $(LUA_DIR)/src/*.h ../include/lua

# ============================================= lua ===================================================


# ============================================= tolua++ ===================================================
TOLUA_DIR=tolua++-$(TOLUA_VERSION)
TOLUA_LIB=$(TOLUA_DIR)/tolua++.a

$(TOLUA_DIR): archive/tolua++-$(TOLUA_VERSION).tar.gz
	tar xzf $? -C .
	touch $@

$(TOLUA_LIB): $(TOLUA_DIR)
	$(MAKE) -C $(TOLUA_DIR) 
	touch $@

$(TOLUA_DIR)/clean:
	$(MAKE) -C $(TOLUA_DIR) clean

$(TOLUA_DIR)/remove:
	@rm -rf $(TOLUA_DIR)

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
# ============================================= tolua++ ===================================================


# ============================================= protobuf ===================================================

PROTOBUF_DIR=protobuf-$(PROTOBUF_VERSION)
PROTOBUF_LIB=$(PROTOBUF_DIR)/libprotobuf/lib/libprotobuf.a

$(PROTOBUF_DIR): archive/protobuf-$(PROTOBUF_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(PROTOBUF_DIR)/download: archive/protobuf-$(PROTOBUF_VERSION).tar.gz

archive/protobuf-$(PROTOBUF_VERSION).tar.gz:
	@echo
	@echo "=== Downloading protobuf $(PROTOBUF_VERSION) ==="
	@echo
	curl "https://codeload.github.com/protocolbuffers/protobuf/tar.gz/refs/tags/v$(PROTOBUF_VERSION)" -o $@

$(PROTOBUF_LIB): $(PROTOBUF_DIR)
	cd $(PROTOBUF_DIR);./autogen.sh
	cd $(PROTOBUF_DIR);./configure --prefix=`pwd`/libprotobuf
	$(MAKE) -C $(PROTOBUF_DIR) -j 10
	$(MAKE) -C $(PROTOBUF_DIR) install

$(PROTOBUF_DIR)/clean:
	$(MAKE) -C $(PROTOBUF_DIR) clean
	rm -rf $(PROTOBUF_DIR)/libprotobuf

$(PROTOBUF_DIR)/remove:
	@rm -rf $(PROTOBUF_DIR) 

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
# ============================================= protobuf ===================================================


# ============================================= googletest ===================================================
GTEST_DIR=googletest-release-$(GTEST_VERSION)
GTEST_LIB=$(GTEST_DIR)/build/lib/libgtest.a

$(GTEST_DIR): archive/googletest-release-$(GTEST_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(GTEST_DIR)/download: archive/googletest-release-$(GTEST_VERSION).tar.gz

archive/googletest-release-$(GTEST_VERSION).tar.gz:
	@echo
	@echo "=== Downloading Google Test $(GTEST_VERSION) ==="
	@echo
	curl "https://codeload.github.com/google/googletest/tar.gz/refs/tags/release-$(GTEST_VERSION)" -o $@

$(GTEST_LIB): $(GTEST_DIR)
	mkdir -p $(GTEST_DIR)/build
	cd $(GTEST_DIR)/build;cmake ..
	$(MAKE) -C $(GTEST_DIR)/build  -j 10

$(GTEST_DIR)/clean:
	$(MAKE) -C $(GTEST_DIR)/build clean
	rm -rf $(GTEST_DIR)/build

$(GTEST_DIR)/remove:
	@rm -rf $(GTEST_DIR)

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
# ============================================= googletest ===================================================


# ============================================= benchmark ===================================================
BENCHMARK_DIR=benchmark-$(BENCHMARK_VERSION)
BENCHMARK_LIB=$(BENCHMARK_DIR)/build/src/libbenchmark.a

$(BENCHMARK_DIR): archive/benchmark-$(BENCHMARK_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(BENCHMARK_DIR)/download: archive/benchmark-$(BENCHMARK_VERSION).tar.gz

archive/benchmark-$(BENCHMARK_VERSION).tar.gz:
	@echo
	@echo "=== Downloading Benchmark $(BENCHMARK_VERSION) ==="
	@echo
	curl "https://codeload.github.com/google/benchmark/tar.gz/refs/tags/v$(BENCHMARK_VERSION)" -o $@

$(BENCHMARK_LIB): $(BENCHMARK_DIR)
	cd $(BENCHMARK_DIR);cmake -E make_directory "build"
	cd $(BENCHMARK_DIR);cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_GTEST_TESTS=OFF ../
	cd $(BENCHMARK_DIR);cmake -DCMAKE_BUILD_TYPE=Release -S . -B "build"
	cd $(BENCHMARK_DIR);cmake --build "build" --config Release 

$(BENCHMARK_DIR)/clean:
	$(MAKE) -C $(BENCHMARK_DIR)/build clean
	rm -rf $(BENCHMARK_DIR)/build 

$(BENCHMARK_DIR)/remove:
	@rm -rf $(BENCHMARK_DIR)

$(BENCHMARK_DIR)/install:
	@echo
	@echo '=== install Benchmark ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(BENCHMARK_LIB) ../lib 
	rm -rf ../include/benchmark
	cp -rf $(BENCHMARK_DIR)/include/benchmark ../include/
# ============================================= benchmark ===================================================



# ============================================= ccronexpr ===================================================
CCRONEXPR_DIR=ccronexpr-$(CCRONEXPR_VERSION)
CCRONEXPR_LIB=$(CCRONEXPR_DIR)/libccronexpr.a

$(CCRONEXPR_DIR): archive/ccronexpr-$(CCRONEXPR_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(CCRONEXPR_DIR)/download: archive/ccronexpr-$(CCRONEXPR_VERSION).tar.gz

archive/ccronexpr-$(CCRONEXPR_VERSION).tar.gz:
	@echo
	@echo "=== Downloading ccronexpr $(CCRONEXPR_VERSION) ==="
	@echo
	curl "https://codeload.github.com/staticlibs/ccronexpr/tar.gz/refs/tags/v$(CCRONEXPR_VERSION)" -o $@

$(CCRONEXPR_LIB): $(CCRONEXPR_DIR)
	cp -rf archive/ccronexpr/makefile $(CCRONEXPR_DIR)
	$(MAKE) -C $(CCRONEXPR_DIR) -j 10
	touch $@

$(CCRONEXPR_DIR)/clean:
	$(MAKE) -C $(CCRONEXPR_DIR) clean

$(CCRONEXPR_DIR)/remove:
	@rm -rf $(CCRONEXPR_DIR) 

$(CCRONEXPR_DIR)/install:
	@echo
	@echo '=== install ccronexpr ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(CCRONEXPR_DIR)/libccronexpr.a ../lib 
	rm -rf ../include/ccronexpr;mkdir -p ../include/ccronexpr
	cp -rf $(CCRONEXPR_DIR)/*.h ../include/ccronexpr
# ============================================= ccronexpr ===================================================

# ============================================= nlohmann/json ===================================================
JSON_DIR=json-$(JSON_VERSION)

$(JSON_DIR): archive/json-$(JSON_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(JSON_DIR)/download: archive/json-$(JSON_VERSION).tar.gz

archive/json-$(JSON_VERSION).tar.gz:
	@echo
	@echo "=== Downloading nlohmann json $(JSON_VERSION) ==="
	@echo
	curl "https://codeload.github.com/nlohmann/json/tar.gz/refs/tags/v$(JSON_VERSION)" -o $@

$(JSON_DIR)/remove:
	@rm -rf $(JSON_DIR)

$(JSON_DIR)/install:
	@echo
	@echo '=== install nlohmann json ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	rm -rf ../include/json;mkdir -p ../include/json
	cp -rf $(JSON_DIR)/single_include/nlohmann/*.hpp ../include/json
# ============================================= nlohmann/json ===================================================

# ============================================= mysql connector ===================================================
MYSQL_DIR=mysql-connector-$(MYSQL_VERSION)
MYSQL_LIB=$(MYSQL_DIR)/lib/libmysqlclient.a

$(MYSQL_DIR): archive/mysql-connector-$(MYSQL_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(MYSQL_LIB): $(MYSQL_DIR)
	touch $@

$(MYSQL_DIR)/remove:
	@rm -rf $(MYSQL_DIR)

$(MYSQL_DIR)/install:
	@echo
	@echo '=== install mysql connector ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(MYSQL_LIB) ../lib 
	rm -rf ../include/mysql
	cp -rf $(MYSQL_DIR)/include/ ../include/mysql
# ============================================= mysql connector ===================================================

# ============================================= inipp ===================================================
INIPP_DIR=inipp-$(INIPP_VERSION)

$(INIPP_DIR): archive/inipp-$(INIPP_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(INIPP_DIR)/download: archive/inipp-$(INIPP_VERSION).tar.gz

archive/inipp-$(INIPP_VERSION).tar.gz:
	@echo
	@echo "=== Downloading mcmtroffaes inipp $(INIPP_VERSION) ==="
	@echo
	curl "https://codeload.github.com/mcmtroffaes/inipp/tar.gz/refs/tags/$(INIPP_VERSION)" -o $@

$(INIPP_DIR)/remove:
	@rm -rf $(INIPP_DIR)

$(INIPP_DIR)/install:
	@echo
	@echo '=== install mcmtroffaes inipp ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	rm -rf ../include/inipp;mkdir -p ../include/inipp
	cp -rf $(INIPP_DIR)/inipp/*.h ../include/inipp
# ============================================= inipp ===================================================

# ============================================= dropbox/json11 ===================================================
JSON11_DIR=json11-$(JSON11_VERSION)

$(JSON11_DIR): archive/json11-$(JSON11_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(JSON11_DIR)/download: archive/json11-$(JSON11_VERSION).tar.gz

archive/json11-$(JSON11_VERSION).tar.gz:
	@echo
	@echo "=== Downloading dropbox json11 $(JSON11_VERSION) ==="
	@echo
	curl "https://codeload.github.com/dropbox/json11/tar.gz/refs/tags/v$(JSON11_VERSION)" -o $@

$(JSON11_DIR)/remove:
	@rm -rf $(JSON11_DIR)

$(JSON11_DIR)/install:
	@echo
	@echo '=== install dropbox json11 ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	rm -rf ../src/json11;mkdir -p ../src/json11
	cp -rf $(JSON11_DIR)/*.hpp ../src/json11
	cp -rf $(JSON11_DIR)/*.cpp ../src/json11
# ============================================= dropbox/json11 ===================================================


# ============================================= mpx/lua-cjson ===================================================
CJSON_DIR=lua-cjson-$(CJSON_VERSION)
CJSON_LIB=$(CJSON_DIR)/libcjson.a

$(CJSON_DIR): archive/lua-cjson-$(CJSON_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(CJSON_DIR)/download: archive/lua-cjson-$(CJSON_VERSION).tar.gz

archive/lua-cjson-$(CJSON_VERSION).tar.gz:
	@echo
	@echo "=== Downloading mpx cjson $(CJSON_VERSION) ==="
	@echo
	curl "https://codeload.github.com/mpx/lua-cjson/tar.gz/refs/tags/$(CJSON_VERSION)" -o $@

$(CJSON_LIB): $(CJSON_DIR)
	cp -rf archive/lua-cjson/Makefile $(CJSON_DIR)
	cp -rf archive/lua-cjson/lua_cjson.c $(CJSON_DIR)
	$(MAKE) -C $(CJSON_DIR)

$(CJSON_DIR)/clean:
	$(MAKE) -C $(CJSON_DIR) clean

$(CJSON_DIR)/remove:
	@rm -rf $(CJSON_DIR) 

$(CJSON_DIR)/install:
	@echo
	@echo '=== install mpx cjson ==='
	@echo
	@mkdir -p ../lib
	@mkdir -p ../include
	cp $(CJSON_LIB) ../lib 
	rm -rf ../include/lua-cjson;mkdir -p ../include/lua-cjson
	cp -rf archive/lua-cjson/lua_cjson.h ../include/lua-cjson
# ============================================= mpx/lua-cjson ===================================================

# ============================================= p-ranav/argparse ===================================================
ARGPARSE_DIR=argparse-$(ARGPARSE_VERSION)
ARGPARSE_LIB=$(ARGPARSE_DIR)/libargparse.a

$(ARGPARSE_DIR): archive/argparse-$(ARGPARSE_VERSION).tar.gz
	tar xzvf $? -C .
	touch $@

$(ARGPARSE_DIR)/download: archive/argparse-$(ARGPARSE_VERSION).tar.gz

archive/argparse-$(ARGPARSE_VERSION).tar.gz:
	@echo
	@echo "=== Downloading mpx argparse $(ARGPARSE_VERSION) ==="
	@echo
	curl "https://codeload.github.com/p-ranav/argparse/tar.gz/refs/tags/v$(ARGPARSE_VERSION)" -o $@

$(ARGPARSE_DIR)/remove:
	@rm -rf $(ARGPARSE_DIR)

$(ARGPARSE_DIR)/install:
	@echo
	@echo '=== install p-ranav/argparse ==='
	@echo
	@mkdir -p ../include
	rm -rf ../include/argparse;mkdir -p ../include/argparse
	cp -rf $(ARGPARSE_DIR)/include/argparse/argparse.hpp ../include/argparse/argparse.hpp
# ============================================= p-ranav/argparse ===================================================

# 下载
download: $(HIREDIS_DIR)/download $(HTTPPARSER_DIR)/download $(LUA_DIR)/download $(PROTOBUF_DIR)/download $(GTEST_DIR)/download $(LIBUV_DIR)/download $(CCRONEXPR_DIR)/download $(BENCHMARK_DIR)/download $(INIPP_DIR)/download $(JSON_DIR)/download $(JSON11_DIR)/download $(CJSON_DIR)/download $(ARGPARSE_DIR)/download

# 编译
default: $(HIREDIS_LIB) $(HTTPPARSER_LIB) $(LUA_LIB) $(PROTOBUF_LIB) $(TOLUA_LIB) $(GTEST_LIB) $(LIBUV_LIB) $(CCRONEXPR_LIB) $(BENCHMARK_LIB) $(CJSON_LIB) $(JSON11_DIR) $(JSON_DIR) $(INIPP_DIR) $(MYSQL_LIB) $(ARGPARSE_DIR)

# 安装
install: $(HIREDIS_DIR)/install $(HTTPPARSER_DIR)/install $(LUA_DIR)/install $(PROTOBUF_DIR)/install $(TOLUA_DIR)/install $(GTEST_DIR)/install $(LIBUV_DIR)/install $(CCRONEXPR_DIR)/install $(BENCHMARK_DIR)/install $(JSON_DIR)/install $(MYSQL_DIR)/install $(INIPP_DIR)/install $(JSON11_DIR)/install $(CJSON_DIR)/install $(ARGPARSE_DIR)/install 

# 清理
clean: $(HIREDIS_DIR)/clean $(HTTPPARSER_DIR)/clean $(LUA_DIR)/clean $(PROTOBUF_DIR)/clean $(TOLUA_DIR)/clean $(GTEST_DIR)/clean $(LIBUV_DIR)/clean $(CCRONEXPR_DIR)/clean $(BENCHMARK_DIR)/clean $(CJSON_DIR)/clean 

# 删除
remove: $(HIREDIS_DIR)/remove $(HTTPPARSER_DIR)/remove $(LUA_DIR)/remove $(PROTOBUF_DIR)/remove $(TOLUA_DIR)/remove $(GTEST_DIR)/remove $(LIBUV_DIR)/remove $(CCRONEXPR_DIR)/remove $(BENCHMARK_DIR)/remove $(CJSON_DIR)/remove $(ARGPARSE_DIR)/remove $(INIPP_DIR)/remove $(JSON_DIR)/remove $(JSON11_DIR)/remove $(MYSQL_DIR)/remove

.PYHON: default download clean remove install

