
ROOT_PATH = ../../../coord

INCLUDE_DIRS=-I. -I$(ROOT_PATH)/include -I$(ROOT_PATH)/include/lua -I$(ROOT_PATH)/include/tolua++ -I$(ROOT_PATH)/src

LIBS =$(ROOT_PATH)/libcoord.a $(ROOT_PATH)/lib/libuv.a $(ROOT_PATH)/lib/tolua++.a $(ROOT_PATH)/lib/liblua.a $(ROOT_PATH)/lib/libmysqlclient.a $(ROOT_PATH)/lib//libhiredis.a $(ROOT_PATH)/lib/libprotobuf.a

DY_LIBS = -lm -ldl -lreadline -lncurses -lpthread

CFLAGS=-O2 -Wall -std=c++11

SOURCE = $(wildcard \
		 *.cc\
		 ) 

OBJ = $(patsubst %.cc,%.o,$(SOURCE))

EXE = gamesvr

%.o:%.cc
	g++ $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)

${EXE}:$(OBJ) $(LIBS)
	g++ -o $(EXE) $(OBJ) $(LIBS)  $(DY_LIBS)

tolua:
	$(ROOT_PATH)/3rd/tolua++/tolua++ -n gamesvr -o interface.cc interface.pkg

clean:
	rm -rf $(EXE)
	rm -rf $(OBJ)
