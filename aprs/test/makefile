obj = udpcli.o

client : $(obj)
	gcc -o client $(obj)

udpcli.o : ../comm/mynet.h ../comm/sigcommon.h ../comm/mybase.h

.PHONY : clean

clean:
	rm $(obj)

