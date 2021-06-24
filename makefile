
compressor: fhandle.cpp cpress.hpp node.cpp hufftree.cpp compress.cpp
	clang -c fhandle.cpp node.cpp hufftree.cpp compress.cpp 
	clang  -o compressor fhandle.o node.o hufftree.o compress.o
	




