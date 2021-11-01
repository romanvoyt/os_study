// "pragma once" is used to control the file which is connected to the executable image only once during the compilation. 
#pragma once

struct tokens;

//turn a sting into a list of words
struct tokens *tokenize(const char *line);

size_t tokens_get_length(struct tokens *tokens);

char *tokens_get_token(struct tokens *tokens, size_t n);

void tokens_destroy(struct tokens *tokens);

