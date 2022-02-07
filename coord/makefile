
HOME = .

INCLUDE_DIRS =-I. -I$(HOME) -I$(HOME)/src -I$(HOME)/include -I$(HOME)/include/lua -I$(HOME)/include/tolua++ 

LIB_DIRS =

LIBS =$(HOME)/lib/libhttp_parser.a $(HOME)/lib/libprotobuf.a $(HOME)/lib/liblua.a $(HOME)/lib/libmysqlclient.a $(HOME)/lib/libhiredis.a $(HOME)/lib/libtolua++.a $(HOME)/lib/libuv.a

DY_LIBS = -lm -ldl -lreadline -lncurses -lpthread -lssl -lcrypto

CFLAGS=-O2 -Wall -std=c++11

SOURCE = $(wildcard \
		src/proto/*.pb.cc\
		src/util/os/*.cc\
		src/util/date/*.cc\
		src/coord/base/*.cc\
		src/coord/log/*.cc\
		src/coord/event/*.cc\
		src/coord/util/*.cc\
		src/coord/bufio/*.cc\
		src/coord/memory/*.cc\
		src/coord/buffer/*.cc\
		src/coord/scene/*.cc\
		src/coord/component/*.cc\
		src/coord/script/*.cc\
		src/coord/object/*.cc\
		src/coord/config/*.cc\
		src/coord/encrypt/*.cc\
	 	src/coord/display/*.cc\
		src/coord/net/*.cc\
		src/coord/gate/*.cc\
		src/coord/http/*.cc\
		src/coord/websocket/*.cc\
		src/coord/proto/*.cc\
		src/coord/timer/*.cc\
		src/coord/sql/*.cc\
		src/coord/sql/mysql/*.cc\
		src/coord/redis/*.cc\
		src/coord/cache/*.cc\
		src/coord/cluster/*.cc\
		src/coord/interface.cc\
		src/coord/coord.cc\
		interface.cc\
		) 

OBJ = $(patsubst %.cc, %.o,$(SOURCE))

COORD = coord
LIB = libcoord.a
lCOORD = lcoord

all:$(COORD) $(LIB) $(lCOORD)

%.o:%.cc
	g++ $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)

${lCOORD}:$(OBJ) lcoord.o
	g++ -o $(lCOORD) $(OBJ) lcoord.o $(LIBS) $(DY_LIBS) $(LIB_DIRS) 

${COORD}:$(OBJ) coord.o
	g++ -o $(COORD) $(OBJ) coord.o $(LIBS) $(DY_LIBS) $(LIB_DIRS) 

$(LIB):$(OBJ)
	ar rcu $@ $(OBJ) 
	ranlib $@

tolua:
	cd src;../dep/tolua++/tolua++ -n coord -o interface.cc interface.pkg

clean:
	rm -rf $(COORD)
	rm -rf $(lCOORD)
	rm -rf $(LIB)
	rm -rf $(OBJ) coord.o lcoord.o

obj:
	echo $(OBJ)

install:
	cp -f lcoord /usr/bin/lcoord
