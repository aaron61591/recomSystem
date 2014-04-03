obj = server.o

aprs : $(obj)
	gcc -o aprs $(obj)

server.o : comm/mybase.h comm/mynet.h comm/mydaemon.h comm/mylog.h

.PHONY : clean

clean:
	-rm $(obj)
