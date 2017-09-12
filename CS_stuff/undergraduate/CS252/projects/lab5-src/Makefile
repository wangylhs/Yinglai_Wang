CXX = g++ -fPIC
NETLIBS= -lnsl

all: daytime-server use-dlopen hello.so myhttpd

daytime-server : daytime-server.o
	$(CXX) -o $@ $@.o $(NETLIBS)

use-dlopen: use-dlopen.o
	$(CXX) -o $@ $@.o $(NETLIBS) -ldl

hello.so: hello.o
	ld -G -o hello.so hello.o

%.o: %.cc
	@echo 'Building $@ from $<'
	$(CXX) -o $@ -c -I. $<

myhttpd: myhttpd.cpp
	$(CXX) myhttpd.cpp -o myhttpd $(NETLIBS) -lpthread 

clean:
	rm -f *.o use-dlopen hello.so
	rm -f *.o daytime-server daytime-client
	rm -f *.o myhttpd

