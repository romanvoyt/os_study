#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

struct token{
    size_t token_length;
    char **tokens;
    size_t buffers_length;
    char *buffers;
}