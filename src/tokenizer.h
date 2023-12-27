#pragma once
#include <stdlib.h>

char* HTML_EXAMPLE = "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "  <meta charset=\"utf-8\">\n" 
    "  <meta name=\"description\" content=\"Neovim user documentation\">\n"
    "<head/>\n"
    "<html/>\n\0"
;

typedef struct {
    int start_index;
    int end_index;
} Token;

typedef struct {
    Token* tokens;
    size_t space_used;
    size_t size;
} TokensArray;


int char_is_delimiter(char input_char);


Token token(int start_index, int end_index);
void print_token(Token* token);

void init_tokens_array(TokensArray* array, size_t initial_size);
void insert_token(TokensArray* array, Token token);
void free_tokens_array(TokensArray* array);
