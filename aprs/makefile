obj = server.o

aprs : $(obj)
	gcc -o aprs $(obj)

server.o : comm/mybase.h comm/netcommon.h

.PHONY : clean

clean:
	-rm $(obj)
