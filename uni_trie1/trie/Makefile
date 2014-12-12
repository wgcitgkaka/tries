test : main.o uni_trie.o
	g++ -o test main.o uni_trie.o
main.o : main.cc uni_trie.h
	g++ -c main.cc
uni_trie.o : uni_trie.cc uni_trie.h
	g++ -c uni_trie.cc

clean :
	rm -f *.o test
