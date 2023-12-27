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


enum TokenType {
    OPEN_LESS_THAN = 200,
    CLOSE_LESS_THAN = 201,
    EQUAL_SIGN = 202,
    QUOTATION_MARK = 203,
    HTML_TEXT = 204,
    HTML_IDENTIFIER = 205,
    EMPTY_TOKEN = 206
};


typedef struct {
    int start_index;
    int end_index;
    enum TokenType token_type;
} Token;

typedef struct {
    Token* tokens;
    size_t space_used;
    size_t size;
} TokensArray;


int char_is_delimiter(char input_char);

void print_lexeme(Token token);

Token token(int start_index, int end_index, enum TokenType token_type);
void print_token(Token* token);

Token get_last_token(TokensArray* array);
void init_tokens_array(TokensArray* array, size_t initial_size);
void insert_token(TokensArray* array, Token token);
void free_tokens_array(TokensArray* array);
