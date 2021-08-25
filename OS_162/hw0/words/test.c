#include <assert.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node
    {
        int val;
        struct node * next;
    }simple_node;

typedef struct word_count {
    char word[64];
    int count;
    struct word_count *next;
} WordCount;

WordCount *wordList = NULL;

/*int words_count(FILE * file){
    
}*/


void add_word(simple_node **head, char *word){
    /*WordCount *cur = head;
    while (cur->next != NULL)
    {
        if(strcmp(cur->word, word) == 0){
            cur->count++;
        }
        cur = cur->next;
    }

    cur->next = (WordCount *) malloc(sizeof(WordCount));
    cur->next->word = word;*/
    
}

bool isInList(WordCount *list, char *word){
    WordCount *cur = list;
    while (cur->next != NULL)
    {
        if(strcmp(cur->word, word)==0){
            return 1;
            break;
        }
    }
    
    return 0;
}

void appendWord(char *s, char c){
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

void parseWord(FILE *file, WordCount *list){
    char wordBuffer[64];
    WordCount *cur = list;
    char c;
    while (1)
    {
        c = fgetc(file);
        if(c != ' ' && c != '\n' && c!= '\t' && strlen(wordBuffer) < 65){
            appendWord(wordBuffer, c);
        }else
        {
            printf("%s is a word\n its size = %ld\n", wordBuffer, sizeof(wordBuffer));

            //bool inList = isInList(list, wordBuffer);
			
			if(cur->word == NULL){
				strcpy(list->word, wordBuffer);
				wordBuffer[0] = 0;
				cur->next = NULL;
			}
			
            while(cur->next != NULL){
                if(strcmp(cur->word, wordBuffer) == 0){
                    cur->count++;
                    break;
                }
                cur = cur->next;
            }
            cur->next = (WordCount*) malloc(sizeof(WordCount));
            strcpy(cur->next->word,wordBuffer);
            cur->next->count = 0;
            cur->next->next = NULL;

            wordBuffer[0] = 0;
        }
        

        if(c == EOF) {
           printf("%s is a final word", wordBuffer);
           break;
        }
    }
}

int main(int argc, char const *argv[])
{
    FILE *file = fopen("words.txt", "r");
    
    parseWord(file, wordList);

    return 0;
}


