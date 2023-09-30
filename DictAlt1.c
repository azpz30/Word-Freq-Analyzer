// Dict.c ... implementation of the Dictionary ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "WFreq.h"

// you may define your own structs here
typedef struct Node *NODE;

struct Node {
    char *words;
    int frequency;
    NODE left;
    NODE right;
};

struct DictRep {
    struct Node *root;
    // add fields to this struct
    // you can add whatever fields you want
};

// add function prototypes for your helper functions here
NODE Dict_insert_node(NODE t, char *word); 
void Dict_free_nodes(NODE t) ;

// Creates a new Dictionary
Dict DictNew(void) {
    Dict d = malloc(sizeof(Dict));
    d->root = NULL;
    return d;
}

//Frees all nodes
void Dict_free_nodes(NODE t) {
    if (t == NULL) {
        return;
    }
    Dict_free_nodes(t->left);
    Dict_free_nodes(t->right);
    free(t);
}

// Frees the given Dictionary
void DictFree(Dict d) {
    if (d == NULL) {
        return;
    }
    Dict_free_nodes(d->root);
}

//Inserts e new node
NODE Dict_insert_node(NODE t, char *word) {
    if (t == NULL) {
        NODE new = malloc(sizeof(NODE));
		char *text = malloc(100);
		strcpy(text, word);
        new->words = text;
        new->frequency = 1;
        new->left = NULL;
        new->right = NULL;
    } else if (strcmp(t->words, word) > 0) {
        t->left = Dict_insert_node(t->left, word);
    } else if (strcmp(t->words, word) < 0) {
        t->right = Dict_insert_node(t->right, word);
    } else {
        t->frequency++;
    }
    return t;
}
// Inserts an occurrence of the given word into the Dictionary
void DictInsert(Dict d, char *word) {
    if (d->root == NULL) {
        Dict_insert_node(d->root, word);
    } else if (strcmp(d->root->words, word) > 0) {
        d->root->left = Dict_insert_node(d->root->left, word);
    } else if (strcmp(d->root->words, word) < 0) {
        d->root->right = Dict_insert_node(d->root->right, word);
    } else {
        d->root->frequency++;
    }
}

// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int DictFind(Dict d, char *word) {
    /*if (t == NULL) {
        return false;
    } else if (v < t->value) {
        return BSTreeFind(t->left, v);
    } else if (v > t->value) {
        return BSTreeFind(t->right, v);
    } else { // (v == t->value)
        return true;
    }*/
    return 0;
}

// Finds  the top `n` frequently occurring words in the given Dictionary
// and stores them in the given  `wfs`  array  in  decreasing  order  of
// frequency,  and then in increasing lexicographic order for words with
// the same frequency. Returns the number of WFreq's stored in the given
// array (this will be min(`n`, #words in the Dictionary)) in  case  the
// Dictionary  does  not  contain enough words to fill the entire array.
// Assumes that the `wfs` array has size `n`.
int DictFindTopN(Dict d, WFreq *wfs, int n) {
    return 0;
}

// Displays the given Dictionary. This is purely for debugging purposes,
// so  you  may  display the Dictionary in any format you want.  You may
// choose not to implement this.
void DictShow(Dict d) {

}
