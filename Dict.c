// COMP2521 21T2 Assignment 1
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

// Node of the tree
struct Node {
    char *words;
    int frequency;
    NODE left;
    NODE right;
};

struct DictRep {
    struct Node *root;
    int dict_size;
    // add fields to this struct
    // you can add whatever fields you want
};

// add function prototypes for your helper functions here

//Helper function to add node to a tree
NODE Dict_insert_node(Dict d, NODE t, char *word);

//Helper function to free all the nodes of the tree. 
void Dict_free_nodes(NODE t);

//Helper function to make a new node and initialise all the information.
NODE NodeNew(void);

//Helper function to find new word.
int Dict_find_word(NODE t, char *word);

//Traverses the whole tree and adds word and freq to array of structs.
int tree_traversal(NODE t, WFreq *wfs, int n, int limit);

//Comparing function to sort the wfs array.
int comp_func(const void *a, const void *b) {
    WFreq *p1 = (WFreq *)a;
    WFreq *p2 = (WFreq *)b;
    //If frequency becomes same then compare words.
   if (p1->freq - p2->freq != 0) {
       return p2->freq - p1->freq;
   } else {
       return strcmp(p1->word, p2->word);
   }
}

// Creates a new Dictionary
Dict DictNew(void) {
    Dict d = malloc(sizeof(* d));
    d->dict_size = 0;
    d->root = NULL;
    return d;
}
//Created a new node.
NODE NodeNew(void) {
    NODE new = malloc(sizeof(* new));
    new->words = NULL;
    new->frequency = 1;
    new->left = NULL;
    new->right = NULL;
    return new;
}

//Frees all nodes
void Dict_free_nodes(NODE t) {
    if (t == NULL) {
        return;
    }
    Dict_free_nodes(t->left);
    Dict_free_nodes(t->right);
    free(t->words);
    free(t);
}

// Frees the given Dictionary
void DictFree(Dict d) {
    if (d == NULL) {
        return;
    } else if (d->root == NULL) {
        free(d);
    } else {
        Dict_free_nodes(d->root);
        free(d);
    }
    
}

//Inserts e new node
NODE Dict_insert_node(Dict d, NODE t, char *word) {
    //Makes a new node and link to the tree.
    if (d->root == NULL) {
        NODE t = NodeNew();
        d->dict_size++;
        t->words = malloc(100);
        strcpy(t->words, word);
        return t;
    } else if (strcmp(t->words, word) > 0) {
        t->left = Dict_insert_node(d, t->left, word);
    } else if (strcmp(t->words, word) < 0) {
        t->right = Dict_insert_node(d, t->right, word);
    } else {//if same word found than increase frequncy.
        t->frequency++;
    }
    return t;
}
// Inserts an occurrence of the given word into the Dictionary
void DictInsert(Dict d, char *word) {
    if (d == NULL || word == NULL) {
        return;
    } else if (d->root == NULL) {
        d->root = Dict_insert_node(d, d->root, word);
    } else if (word != NULL && strcmp(d->root->words, word) > 0) {
        d->root->left = Dict_insert_node(d, d->root->left, word);
    } else if (word != NULL && strcmp(d->root->words, word) < 0) {
        d->root->right = Dict_insert_node(d, d->root->right, word);
    } else {//if same word found than increase frequncy.
        d->root->frequency++;
    }
}

//Takes in the left and right node of the root and then traverses whole 
//tree to find the word and returns it frequency.
int Dict_find_word(NODE t, char *word) {
    int y = 0;
    if (strcmp(t->words, word) == 0) {
        y = t->frequency;
    } else if (strcmp(t->words, word) > 0) {
        y = Dict_find_word(t->left, word);
    } else if (strcmp(t->words, word) < 0) {
        y = Dict_find_word(t->right, word);
    } else if (t == NULL) {
        y = 0;
    } else {
        y = 0;
    }
    return y;
}

// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int DictFind(Dict d, char *word) {
    int x = 0;
    if (d == NULL) {
        x = 0;
    } else if (d->root == NULL) {
        x = 0;
    } else if (strcmp(d->root->words, word) > 0) {
        x = Dict_find_word(d->root->left, word);
    } else if (strcmp(d->root->words, word) < 0) {
        x = Dict_find_word(d->root->right, word);
    } else { // (d->root->words == word)
        x = d->root->frequency;
    }
    return x;
}

//Takes in the left and right node of the root and then traverses whole 
//tree to add each node information to the array of struct.
int tree_traversal(NODE t, WFreq *wfs, int n, int limit) {
    if (t == NULL) {
        return n;
    }
    n = n + 1;
    wfs[n].word = t->words;
    wfs[n].freq = t->frequency;
    int remaining_n = tree_traversal(t->left, wfs, n, limit);
    int new_n = tree_traversal(t->right, wfs, remaining_n, limit);
    return new_n;
}


// Finds  the top `n` frequently occurring words in the given Dictionary
// and stores them in the given  `wfs`  array  in  decreasing  order  of
// frequency,  and then in increasing lexicographic order for words with
// the same frequency. Returns the number of WFreq's stored in the given
// array (this will be min(`n`, #words in the Dictionary)) in  case  the
// Dictionary  does  not  contain enough words to fill the entire array.
// Assumes that the `wfs` array has size `n`.
int DictFindTopN(Dict d, WFreq *wfs, int n) {
    if (d->root == NULL) {
        return 0;
    }
    int limit = n;
    wfs[0].word = d->root->words;
    wfs[0].freq = d->root->frequency;
    //Traversing whole tree and adding node information to array.
    int remaining_n = tree_traversal(d->root->left, wfs, 0, limit);
    int total_n = tree_traversal(d->root->right, wfs, remaining_n, limit);
    (void)total_n; 
    //Using qsort to sort the array of struct.
    qsort(wfs, d->dict_size, sizeof(wfs[0]), comp_func);
    if (n < d->dict_size) {

    } else if (n == d->dict_size) {

    } else {
        n = d->dict_size;
    }
    return n;
}

// Displays the given Dictionary. This is purely for debugging purposes,
// so  you  may  display the Dictionary in any format you want.  You may
// choose not to implement this.
void DictShow(Dict d) {
  
}

