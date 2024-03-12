struct Node {
    char character;
    int value;
    int numNodes;
    struct Node **nodes;
};

struct Trie {
    int numNodes;
    struct Node **nodes;
};

// returns a new node with a value and item
struct Node *newNode(char character);

// returns a new trie
struct Trie *newTrie();

// finds the next node character
struct Node *nodeFind(struct Node *node, char character);

// inserts and returns a node
struct Node *trieInsert(struct Trie *trie, char *key);

// deletes node character
void trieDelete(struct Trie *trie, char *key);

// finds the value of a key
int trieLookup(struct Trie *trie, char *key);
