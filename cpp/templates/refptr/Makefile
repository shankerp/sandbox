all: RefPtrUsage

RefPtrUsage: Assertions.o FastMalloc.o RefPtrUsage.o
	g++ -I./ -I./wtf/ Assertions.o FastMalloc.o RefPtrUsage.o -o RefPtrUsage

Assertions.o: Assertions.cpp
	g++ -I./ -I./wtf/ -c Assertions.cpp

FastMalloc.o: FastMalloc.cpp
	g++ -I./ -I./wtf/ -c FastMalloc.cpp

RefPtrUsage.o: RefPtrUsage.cpp
	g++ -I./ -I./wtf/ -c RefPtrUsage.cpp

clean:
	rm -rf *o RefPtrUsage
