
INC =  	-I./					\
	-I/usr/local/mysql/include

LIB= 	 -L/usr/local/lib/x86_64-linux-gnu \
	-L/usr/local/mysql/lib \
	-lmysqlclient
LD =  -Wl,--no-as-needed,-rpath=/usr/local/lib/x86_64-linux-gnu
		
CC      = g++
CFLAGS  = -g -Wall -Werror -std=c++11 

.SUFFIXES:  .o .cpp .cc

.PHONY:all install clean

DIR_SRC	= .
SRC_CPP = $(wildcard $(DIR_SRC)/*.cpp)
INC += -I$(DIR_SRC)

OBJS = $(SRC_CPP:%.cpp=%.o)
OBJS += $(SRC_CC:%.cc=%.o)

OUTPUT = a.out 

all:$(OBJS)
	$(CC) $(CFLAGS) $(INC) $(LD) $^ -o $(OUTPUT) $(LIB)

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) $(INC) $^ -o $@ $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

.cc.o:
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

install_1:
	cp -f $(OUTPUT) /home/cgy/gameserver/ddzgame1/bin/ddzserver1  

install_2:
	cp -f $(OUTPUT) /home/cgy/gameserver/ddzgame2/bin/ddzserver2
	
clean: 
	rm -f $(OUTPUT)
	find ./ -regex ".*\.o$$" | xargs echo
	find ./ -regex ".*\.o$$" | xargs rm -f
	
