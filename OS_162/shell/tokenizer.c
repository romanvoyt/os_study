#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

struct tokens{
    size_t tokens_length;
    char **tokens;
    size_t buffers_length;
    char *buffers;
};

static void *vector_push(char ***pointer, size_t *size, void *elem){
    *pointer = (char**) realloc(*pointer, sizeof(char *) * (*size + 1));
    (*pointer)[*size] = elem;
    *size += 1;
    return elem;
}

static void *copy_word(char *source, size_t n){
    source[n] = '\0';
    char *word = (char *) malloc(n+1);
    strncpy(word, source, n+1);

    strncpy(word, source, n+1);
    return word;
}

struct tokens *tokenize(const char *line){
    if(line == NULL) return NULL;

    static char token[4096];
    size_t n = 0, n_max = 4096;
    struct tokens *tokens;
    size_t line_length = strlen(line);

    tokens = (struct tokens *) malloc(sizeof(struct tokens));
    tokens->tokens_length = 0;
    tokens->tokens = NULL;
    tokens->buffers_length = 0;
    tokens->buffers = NULL;

    const int MODE_NORMAL = 0, MODE_SQUOTE = 1, MODE_DSQUOTE = 2;
    int mode = MODE_NORMAL;

    for(unsigned int i = 0; i < line_length; i++){
        //processing loop body
    }
}

size_t tokens_get_length(struct tokens *tokens){

}

char *tokens_get_token(struct tokens *tokens, size_t n){

}

void tokens_destroy(struct tokens *tokens){
    
}


