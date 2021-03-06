
INC =	-I/usr/local/include/hiredis	\
		-I./ -I../

LIB	= 	-lhiredis -ldl -lpthread
		
CC      = g++
CFLAGS  = -g -Wall -Werror -std=c++11  -Wshadow -Wunreachable-code -Wextra
LDFLAGS = -Wl,--no-as-needed -lprotobuf

.SUFFIXES:  .o .cpp .cc

.PHONY:all install clean

SRC_DIR	= ..
SRC_CPP = $(wildcard $(SRC_DIR)/*.cpp)
INC += -I$(SRC_DIR)

CURRENT_OBJS = .
OBJS += $(CURRENT_OBJS:%.cpp=%.o)


###################################################

OBJS = $(SRC_CPP:%.cpp=%.o)
OBJS += $(SRC_CC:%.cc=%.o)

OUTPUT = tstring tlist tzset tscript tconn tbigdata tpool tperformance treplication

all:$(OBJS) $(OUTPUT)

    
tstring:$(OBJS) TestString.cpp TestTool.cpp
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@

tlist:$(OBJS) TestList.cpp TestTool.cpp
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@

tzset:$(OBJS) TestZset.cpp TestTool.cpp
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@
    
tscript:$(OBJS) TestScript.cpp TestTool.cpp
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@    
	
tconn:$(OBJS) TestConn.cpp TestTool.cpp
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@ 
        
tbigdata:$(OBJS) TestBigData.cpp bigdata.pb.cc
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@    
    
tpool:$(OBJS) TestPool.cpp TestTool.cpp
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@ 
    
tperformance:$(OBJS) TestPerformance.cpp TestTool.cpp
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@ 

treplication:$(OBJS) TestReplication.cpp TestTool.cpp
	$(CC) $(CFLAGS) $(INC) $^ $(LIB) $(LDFLAGS) -o $@ 

.cpp.o:
	@echo [  $(shell expr $(shell echo $(OBJS)|sed 's#$@.*$$#$@#'|wc -w) \* 100 / $(words $(OBJS)))%] $(CC) -c $< -o $@ 
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 
    
.cc.o:
	@echo [  $(shell expr $(shell echo $(OBJS)|sed 's#$@.*$$#$@#'|wc -w) \* 100 / $(words $(OBJS)))%] $(CC) -c $< -o $@ 
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

clean: 
	@echo $(OBJS)
	@rm -f $(OUTPUT)
	@rm -f $(OBJS)
	@find ./ -regex ".*\.o$$" | xargs rm -f
	
