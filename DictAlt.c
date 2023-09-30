// Dict.c ... implementation of the Dictionary ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "WFreq.h"

// you may define your own structs here

struct Node {
    WFreq *data;
    Dict left;
    Dict right;
};

struct DictRep {
    // add fields to this struct
    // you can add whatever fields you want
    struct Node *tree;
};

// add function prototypes for your helper functions here

// Creates a new Dictionary
Dict DictNew(void) {
    Dict d = malloc(sizeof(Dict));
    d->tree = NULL;
    return d;
}

// Frees the given Dictionary
void DictFree(Dict d) {

}

//Inserts e new node
Dict Dict_insert_node(NODE t, char *word) {
    if (t == NULL) {
        NODE new = malloc(sizeof(NODE));
        WFreq *wfs = malloc(sizeof(Wfreq *));
        char *text = malloc(100);
        strcpy(text, word)
        wfs->word = text;
        new-> = NULL;
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
    if (d->tree == NULL) {
        Dict_insert_node(d->tree, word);
    }
}

// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int DictFind(Dict d, char *word) {
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
