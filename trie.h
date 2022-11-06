#include<stdbool.h>

#define NUM_CHAR 26

typedef struct node
{
    struct node *child[NUM_CHAR];
    char *mean;
    bool terminal;
}node;                             

typedef node* trie; 

void init(trie*t);
trie createnode();
void insert(trie* root);
int search(trie root,char *key);
int deletion(trie *curr,char*str);
void print_meaning(trie t,char*key);
void unload(trie *dict_rem);
void view();
void load(trie *root);
int haveChildren(trie curr);
void del_from_dict(char*key);
char* search_for(trie root, char* key);
