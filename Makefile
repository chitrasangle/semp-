output: main.o trie.o
	gcc -o output main.c trie.c
main.o: main.c
	gcc -c main.c
trie.o: trie.c
	gcc -c trie.c