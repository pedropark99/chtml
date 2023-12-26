#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tokenizer.h"

#define DEFAULT_TOKENS_ARRAY_SIZE 450


void tokenizer(TokensArray* tokens, char* input_string)
{
    if (strlen(input_string) == 0)
    {
        printf("[WARN]: Input string seems to be empty!");
    }

    char current_char = input_string[0];
    Token current_token = {0, 0};
    int last_index = 0;

    
    if (current_char == '<')
    {
        insert_token(tokens, token(last_index, 0));
        last_index++;
    }

    for (int i = 0; i < strlen(input_string); i++)
    {
        current_char = input_string[i];
        if (current_char == '<')
        {
            insert_token(tokens, token(last_index, i - 1));
            insert_token(tokens, token(i, i));
            last_index++;
        }
    }

}



Token token(int start_index, int end_index)
{
    Token t = {start_index, end_index};
    return t;
}

void print_token(Token *token)
{
    printf("[Token]: start=%d, end=%d\n", token->start_index, token->end_index);
}


void init_tokens_array(TokensArray* array, size_t initial_size)
{
    array->tokens = malloc(initial_size * sizeof(Token));
    array->space_used = 0;
    array->size = initial_size;
}

void insert_token(TokensArray* array, Token token) 
{
  if (array->space_used == array->size) {
    array->size *= 2;
    array->tokens = realloc(array->tokens, array->size * sizeof(Token));
  }
  array->tokens[array->space_used++] = token;
}

void free_tokens_array(TokensArray* array)
{
    free(array->tokens);
    array->tokens = NULL;
    array->space_used = 0;
    array->size = 0;
}





int main()
{
    printf("[Input]:\n%s\n\n", HTML_EXAMPLE);
    TokensArray tokens;
    init_tokens_array(&tokens, DEFAULT_TOKENS_ARRAY_SIZE);

    tokenizer(&tokens, HTML_EXAMPLE);

    for (int i = 0; i < tokens.space_used; i++)
    {
        Token tok = tokens.tokens[i];
        print_token(&tok);
    }

    free_tokens_array(&tokens);
    return 1; 
}
