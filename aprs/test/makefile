CC = gcc
CFLAGS = -g

obj = udpcli.o ../comm/mylog.o ../comm/mysig.o ../comm/myexit.o ../comm/myfun.o

client : $(obj)
	gcc -o client $(obj)

udpcli.o : ../comm/mybase.h
../comm/mylog.o : ../comm/mylog.h ../comm/mybase.h
../comm/mysig.o : ../comm/mysig.h
../comm/myexit.o : ../comm/myexit.h ../comm/mylog.h
../comm/myfun.o : ../comm/myfun.h ../comm/mybase.h ../comm/mylog.h

.PHONY : clean

clean:
	rm $(obj)

