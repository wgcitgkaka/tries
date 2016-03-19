test : main.o uni_trie.o mul_trie.o
	g++ -g -o test main.o uni_trie.o mul_trie.o
main.o : main.cc uni_trie.h
	g++ -g -c main.cc
uni_trie.o : uni_trie.cc uni_trie.h
	g++ -g -c uni_trie.cc
mul_trie.o : mul_trie.cc mul_trie.h
	g++ -g -c mul_trie.cc
clean :
	rm -f *.o test
