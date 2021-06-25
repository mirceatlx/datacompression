
compressor: fhandle.cpp cpress.hpp node.cpp hufftree.cpp compress.cpp
	g++ -c fhandle.cpp node.cpp hufftree.cpp compress.cpp 
	g++  -o compressor fhandle.o node.o hufftree.o compress.o
	




