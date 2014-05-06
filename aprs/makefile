CC = gcc
CFLAGS = -g -std=gnu99

obj = server.o recom.o init.o data.o calcul.o \
	comm/mysql_client.o comm/myfun.o comm/mydaemon.o comm/mylog.o comm/mysig.o comm/myexit.o

start : $(obj)
	$(CC) $(CFLAGS) -o start $(obj) -lmysqlclient -lm

server.o : init.h recom.h comm/mybase.h
recom.o : recom.h data.h comm/mybase.h
init.o : init.h recom.h comm/mybase.h
data.o : data.h comm/mybase.h
calcul.o : calcul.h comm/mybase.h
comm/mysql_client.o : comm/mysql_client.h comm/mybase.h
comm/myfun.o : comm/myfun.h comm/mybase.h comm/mylog.h
comm/mydaemon.o : comm/mydaemon.h
comm/mylog.o : comm/mylog.h comm/mybase.h
comm/mysig.o : comm/mysig.h
comm/myexit.o : comm/myexit.h comm/mylog.h

.PHONY : clean

clean:
	-rm $(obj)
