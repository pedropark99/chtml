#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokenizer.h"

#define DEFAULT_TOKENS_ARRAY_SIZE 450


char CHARACTER_DELIMITERS[] = {
    '<', '>', '=', '"', ',',
    '\n'
};



void tokenizer(TokensArray* tokens, char* input_string)
{
    if (strlen(input_string) == 0)
    {
        printf("[WARN]: Input string seems to be empty!");
    }

    Token previous_token = {0, 0, EMPTY_TOKEN};
    bool inside_string = false;
    int current_state = 0;
    int lexeme_begin = 0;
    
    for (int current_index = 0; current_index < strlen(input_string); current_index++)
    {
        if (input_string[current_index] == '<') {
            insert_token(tokens, token(current_index, current_index, LESSER_THAN_SIGN));
            lexeme_begin = current_index + 1;
            // Advance to the next space, to get the HTML element identifier
            while (current_index < strlen(input_string))
            {
                if (input_string[current_index] == ' '
                    || input_string[current_index] == '>'
                    || input_string[current_index] == '/') {

                    break;
                }
                current_index++;
            }
            insert_token(tokens, token(lexeme_begin, current_index - 1, HTML_IDENTIFIER));
            lexeme_begin = current_index + 1;

            if (input_string[current_index] == '>')
            {
                insert_token(tokens, token(current_index, current_index, GREATER_THAN_SIGN));
                lexeme_begin = current_index + 1;
                continue;
            }

            // Tokenize the remainder of the current HTML element
            while (current_index < strlen(input_string))
            {
                if (!inside_string && input_string[current_index] == '>') {
                    insert_token(tokens, token(current_index, current_index, GREATER_THAN_SIGN));
                    lexeme_begin = current_index + 1;
                    break;
                }

                if (inside_string) {
                    if (input_string[current_index] == '"') {
                        insert_token(tokens, token(lexeme_begin, current_index - 1, HTML_TEXT));
                        insert_token(tokens, token(current_index, current_index, QUOTATION_MARK));
                        lexeme_begin = current_index + 1;
                        inside_string = false;
                    }

                    current_index++; continue;
                }



                if (!inside_string && input_string[current_index] == '=') {
                    insert_token(tokens, token(current_index, current_index, EQUAL_SIGN));
                    lexeme_begin = current_index + 1;
                    current_index++; continue;
                }
                if (!inside_string && input_string[current_index] == '/') {
                    insert_token(tokens, token(current_index, current_index, FORWARD_SLASH));
                    lexeme_begin = current_index + 1;
                    current_index++; continue;                  
                }
                if (!inside_string && input_string[current_index] == '"') {
                    inside_string = true;
                    insert_token(tokens, token(lexeme_begin, current_index, QUOTATION_MARK));
                    lexeme_begin = current_index + 1;
                    current_index++; continue;
                }

                if (!inside_string &&
                    (current_index + 1) < strlen(input_string) &&
                    input_string[current_index + 1] == '=') {
                    
                    insert_token(tokens, token(lexeme_begin, current_index, HTML_ATTRIBUTE_KEY));
                    lexeme_begin = current_index + 1;
                    current_index++; continue;
                }
                    
                current_index++;
            }
        }
   }

}







Token token(int start_index, int end_index, enum TokenType token_type)
{
    Token t = {start_index, end_index, token_type};
    return t;
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

Token get_last_token(TokensArray* array)
{
    if (array->space_used == 0) {
        Token tok = {0, 0, EMPTY_TOKEN};
        return tok;
    }

    return array->tokens[array->space_used - 1];
}


void print_token(Token *token)
{
    char* text = get_token_lexeme(token);
    printf(
        "[Token]: start=%d, end=%d, type=%s, content=%s\n", 
        token->start_index, 
        token->end_index, 
        token_type_to_str(token->token_type), 
        text
    );
    free(text);
}

char* get_token_lexeme(Token* token)
{
    int length = token->end_index - token->start_index + 2;
    char* text = malloc(length);
    text[length - 1] = '\0';
    for (int i = 0; i < (length - 1); i++)
    {
        text[i] = HTML_EXAMPLE[token->start_index + i];
    }
    return text;
}

void print_lexeme(Token token)
{
    char* text = get_token_lexeme(&token);
    printf("Token content: %s\n", text);
    free(text);
}

char* token_type_to_str(enum TokenType type)
{
    static char str[4];
    switch (type) {
        case EQUAL_SIGN:
            strcpy(str, "EQS");
            break;
        case LESSER_THAN_SIGN:
            strcpy(str, "LTS");
            break;
        case GREATER_THAN_SIGN:
            strcpy(str, "GTS");
            break;
        case QUOTATION_MARK:
            strcpy(str, "QUM");
            break;
        case HTML_IDENTIFIER:
            strcpy(str, "HTI");
            break;
        case HTML_TEXT:
            strcpy(str, "HTT");
            break;
        case EMPTY_TOKEN:
            strcpy(str, "EPT");
            break;
        case HTML_ATTRIBUTE_VALUE:
            strcpy(str, "HAV");
            break;
        case HTML_ATTRIBUTE_KEY:
            strcpy(str, "HAK");
            break;
        case FORWARD_SLASH:
            strcpy(str, "FOS");
            break;
    }

    return str;
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
