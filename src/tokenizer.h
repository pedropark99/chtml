#pragma once
#include <stdlib.h>

char* HTML_EXAMPLE = "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "  <meta charset=\"utf-8\">\n" 
    "  <meta name=\"description\" content=\"Neovim user documentation\">\n"
    "  <title>Welcome to Neovim user documentation!<title/>\n"
    "  <meta author=\"Pedro \\\"Duarte\\\" Faria\">"
    "<head/>\n"
    "<html/>\n\0"
;


enum TokenType {
    GREATER_THAN_SIGN = 200,
    LESSER_THAN_SIGN = 201,
    EQUAL_SIGN = 202,
    QUOTATION_MARK = 203,
    HTML_TEXT = 204,
    HTML_IDENTIFIER = 205,
    HTML_ATTRIBUTE_KEY = 207,
    HTML_ATTRIBUTE_VALUE = 208,
    FORWARD_SLASH = 210,
    NEW_LINE = 211,
    DOC_TYPE = 212,
    EMPTY_TOKEN = 206
};

typedef struct {
    int lexeme_begin;
    int current_index;
    bool inside_string;
} TokenizerCache;

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

void tokenize_first_element(TokensArray* tokens, char* input_string, TokenizerCache* tc);
void advance_to_next_char(TokenizerCache* tc, char chr, char* input_string);


void print_lexeme(Token token);
Token token(int start_index, int end_index, enum TokenType token_type);
void print_token(Token* token);
char* get_token_lexeme(Token* token);
char* token_type_to_str(enum TokenType type);
Token get_last_token(TokensArray* array);


void init_tokens_array(TokensArray* array, size_t initial_size);
void insert_token(TokensArray* array, Token token);
void free_tokens_array(TokensArray* array);
