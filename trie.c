#include "trie.h"
#include "stdlib.h"

// returns a new node with a value and item
struct Node *newNode(char character) {
    struct Node *node = malloc(sizeof(struct Node));
    node->value = 1;
    node->character = character;
    node->numNodes = 0;
    node->nodes = NULL;
    return node;
}

// returns a new trie
struct Trie *newTrie() {
    struct Trie *trie = malloc(sizeof(struct Trie));
    trie->numNodes = 0;
    trie->nodes = NULL;
    return trie;
}

// finds the next node character
struct Node *nodeFind(struct Node *node, char character) {
    for (int i = 0; i < node->numNodes; i++) {
        if (node->nodes[i]->character == character)
            return node->nodes[i];
    }
    return NULL;
}

int nodeFindI(struct Node *node, char character) {
    for (int i = 0; i < node->numNodes; i++) {
        if (node->nodes[i]->character == character)
            return i;
    }
    return -1;
}

struct Node *defragmentNodes(struct Node *node, int hole) {
    // shift nodes over to fill hole
    for (int i = hole; i < node->numNodes - 1; i++) {
        node->nodes[i] = node->nodes[i + 1];
    }
    return realloc(node->nodes, sizeof(struct Node *) * (node->numNodes - 1));
}

// trieInsert helper
struct Node *nodeInsert(struct Node *node, char *key) {
    // increment value and return if at end of string
    if (key[0] == '\0') {
        node->value++;
        return node;
    }
    // get the next node
    struct Node *nextNode = nodeFind(node, key[0]);
    // if next node was found, recurse next node with next char in key
    if (nextNode != NULL)
        return nodeInsert(nextNode, key + sizeof(char));
    // else, increment the size of the nodes array, insert a new node, and
    // recurse on this node with next char in key
    else {
        node->nodes =
            realloc(node->nodes, sizeof(struct Node *) * (node->numNodes + 1));
        struct Node *n = newNode(key[0]);
        node->nodes[node->numNodes] = n;
        node->numNodes++;
        return nodeInsert(n, key + sizeof(char));
    }
}

// inserts and returns a node
struct Node *trieInsert(struct Trie *trie, char *key) {
    if (key[0] == '\0')
        return NULL;
    for (int i = 0; i < trie->numNodes; i++)
        if (trie->nodes[i]->character == key[0])
            return nodeInsert(trie->nodes[i], key + sizeof(char));
    return NULL;
}

// trieDelete helper
void nodeDelete(struct Node *node, char *key) {
    // decrement value and return if at end of string
    if (key[0] == '\0') {
        node->value--;
        return;
    }
    // get the next node
    struct Node *nextNode = nodeFind(node, key[0]);
    // return if at end of trie
    if (nextNode == NULL)
        return;
    // free node if leaf of value 0
    if (nextNode->value == 1 && nextNode->numNodes == 0) {
        defragmentNodes(node, nodeFindI(node, key[0]));
        free(nextNode);
        return;
    }
    // else, recurse next node with next char in key
    nodeDelete(nextNode, key + sizeof(char));
    return;
}

// deletes node character
void trieDelete(struct Trie *trie, char *key) {
    if (key[0] == '\0')
        return;
    for (int i = 0; i < trie->numNodes; i++) {
        if (trie->nodes[i]->character == key[0]) {
            nodeDelete(trie->nodes[i], key + sizeof(char));
            return;
        }
    }
    return;
}

int nodeLookup(struct Node *node, char *key) {
    // return if at end of string
    if (key[0] == '\0')
        return node->value;
    // get the next node
    struct Node *nextNode = nodeFind(node, key[0]);
    // if next node was found, recurse next node with next char in key
    if (nextNode != NULL)
        return nodeLookup(nextNode, key + sizeof(char));
    // return key value
    return node->value;
}

// finds the value of a key
int trieLookup(struct Trie *trie, char *key) {
    if (key[0] == '\0')
        return -1;
    for (int i = 0; i < trie->numNodes; i++) {
        if (trie->nodes[i]->character == key[0]) {
            return nodeLookup(trie->nodes[i], key + sizeof(char));
        }
    }
    return -1;
}
