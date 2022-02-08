SOURCE =  $(wildcard ccronexpr.c) 

HEADER =  $(wildcard ccronexpr.h) 

OBJ = $(patsubst %.c, %.o,$(SOURCE))

LIB = libccronexpr.a

CFLAGS=-I. -Wall -Wextra -std=c89 

%.o:%.c
	gcc $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)


$(LIB):$(OBJ)
	ar rcu $@ $(OBJ) 
	ranlib $@	

clean:
	rm -rf $(LIB)
	rm -rf $(OBJ) 

obj:
	echo $(OBJ)

install:
	cp -f $(LIB) ../../lib/
	rm -rf ../../include/ccronexpr
	mkdir ../../include/ccronexpr
	cp $(HEADER) ../../include/ccronexpr
