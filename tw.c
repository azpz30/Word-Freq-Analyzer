// tw.c ... compute top N most frequent words in file F
// Usage: ./tw [Nwords] File

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "stemmer.h"
#include "WFreq.h"

#define MAXLINE 1000
#define MAXWORD 100

#define isWordChar(c) (isalnum(c) || (c) == '\'' || (c) == '-')

// add function prototypes for your own functions here
int startnend(char c);

//Tokenises, Normalises, Removes Stopword and inserts words into the BST.
//Also returns the number of words inserted using the DictFind function.
int preprocessing(char *a, char *b, Dict d, char stopwords[][20]);

//Takes in a word and does a binary search on the array of stopwords.
//If its is a stopword, then it returns 1 or else 0.
int isStopword(char *a, char stopwords[][20]);

int main(int argc, char *argv[]) {
	int   nWords;    // number of top frequency words to show
	char *fileName;  // name of file containing book text

	// process command-line args
	switch (argc) {
		case 2:
			nWords = 10;
			fileName = argv[1];
			break;
		case 3:
			nWords = atoi(argv[1]);
			if (nWords < 10) nWords = 10;
			fileName = argv[2];
			break;
		default:
			fprintf(stderr,"Usage: %s [Nwords] File\n", argv[0]);
			exit(EXIT_FAILURE);
	}
	
	FILE *stopwords_r = fopen("stopwords", "r");
	if (stopwords_r == NULL) {
		fprintf(stderr, "Can't open stopwords\n");
		exit(EXIT_FAILURE);
	}
	char Buffer_stopwords[MAXWORD + 1];
	char stopwords[654][20] = {};
	int i = 0;

	//Storing stopwords into a 2D-array.
	while (fgets(Buffer_stopwords, ' ', stopwords_r) != NULL) {
		int len = strlen(Buffer_stopwords);
		int j = 0;
		while (j < len && Buffer_stopwords[j] != '\n') {
			stopwords[i][j] = Buffer_stopwords[j];
			j++;
		}
		i++;
	}
	fclose(stopwords_r);
	
	char *output;
	output = "testing.txt";
	//New dictionary tree is made.
	Dict d = DictNew();
	int dict_size = 0;
	dict_size = preprocessing(fileName, output, d, stopwords);

	//Declaring the array with size as the maximum number of words inserted. 
	struct WFreq wfs[dict_size];
	int n = DictFindTopN(d, wfs, nWords);
	(void)n;

	//Adjusting the nWord depending on the number of words in BST.
	if (nWords < dict_size) {

	} else if (nWords == dict_size) {

	} else {
		nWords = dict_size;
	}
	for (int i = 0; i < nWords; i++) {
		printf("%d %s\n", wfs[i].freq, wfs[i].word);
	}
	DictFree(d);
}

// add your own functions here

// Tokenises,normalises, removes stopword from the whole text and inserts into BST.
int preprocessing(char *a, char *b, Dict d, char stopwords[][20]) {
    FILE *book_read;
    book_read = fopen(a, "r");
    int size = 0;
	if (book_read == NULL) {
		fprintf(stderr, "Can't open %s\n", a);
		exit(EXIT_FAILURE);
	}
    
    //Removing punctuations from the text.
    char text_lines[MAXLINE + 1];
    int x = 0;

    while (fgets(text_lines, MAXLINE + 1, book_read) != NULL) {
        char Buffer[200] = {};
		//Variables used to read lines only when "*** START OF" is detected.
        if (strstr(text_lines, "*** START OF") != NULL) {
            x = 1;
        } else if (strstr(text_lines, "*** END OF") != NULL) {
            x = 0;
        }
        if (x > 1 && text_lines != NULL) {
            int line_len = strlen(text_lines);
			int t = 0;
			//Traverse through each character and replace invalid char with space.
			for (int i = 0; i < line_len; i++) {
				text_lines[i] = tolower(text_lines[i]);
				if (isWordChar(text_lines[i])) {
					Buffer[t] = text_lines[i];
					//Null terminate the word.
				} else if (text_lines[i] == '\n') {
					Buffer[t] = '\0';
				} else {
					Buffer[t] = ' ';
				}
				t++;
			}
			//Using strtok to break the lines into word. 
			//Now each word as a sequence of valid characters.
            char *final_word = strtok(Buffer, " ");
            while (final_word != NULL) {
			
				int word_len = strlen(final_word);
				//Atempt to insert word into BST only when it is not a stopword
				//single character.
                if (isStopword(final_word , stopwords) == 0 && 
					final_word != NULL && word_len > 1) {
                    stem(final_word, 0, word_len - 1);
                    DictInsert(d, final_word);
                    if (DictFind(d, final_word) == 1) {
                        size++;
                    }
                }
                final_word = strtok(NULL, " ");
            }
            
        } else {
        }
        if (x == 1) {
            x++;
        }
    }
	if (x == 1) {
		fprintf(stderr, "Not a Project Gutenberg book\n");
		exit(EXIT_FAILURE);
	}
    fclose(book_read);
    return size;
}

//Returns 1 if a word is a stopword or else returns 0.
int isStopword(char *a, char stopwords[][20]) {
	//Binary search algorithm taken from lecture pseudocode.
	int x = 0;
	int left_bound = 0;
	int right_bound = 654 - 1;
	int guess_index = (left_bound + right_bound) / 2;
	while (left_bound <= right_bound) {
	    guess_index = (left_bound + right_bound) / 2;
	    if (strcmp(stopwords[guess_index], a) > 0) {
	        right_bound = guess_index - 1;
	    } else if (strcmp(stopwords[guess_index], a) < 0) {
	        left_bound = guess_index + 1;
	    } else if (strcmp(stopwords[guess_index], a) == 0) {
	        x = 1;
	        return 1;
	    }
	}
	return x;
		
}