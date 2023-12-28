#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokenizer.h"

#define DEFAULT_TOKENS_ARRAY_SIZE 450



void tokenizer(TokensArray* tokens, char* input_string)
{
    if (strlen(input_string) == 0)
    {
        printf("[WARN]: Input string seems to be empty!");
    }

    TokenizerCache tc = {
        0, // tc.lexeme_begin
        0, // tc.current_index
        false // tc.inside_string
    };

    // Tokenize the components of the first HTML element, which is usually <!DOCTYPE html>.
    tokenize_first_element(tokens, input_string, &tc);

    while (tc.current_index < strlen(input_string))
    {
        if (input_string[tc.current_index] == '<') {
            insert_token(tokens, token(tc.current_index, tc.current_index, LESSER_THAN_SIGN));
            tc.lexeme_begin = tc.current_index + 1;
            // Advance to the next space, to get the HTML element identifier
            while (tc.current_index < strlen(input_string))
            {
                if (input_string[tc.current_index] == ' '
                    || input_string[tc.current_index] == '>'
                    || input_string[tc.current_index] == '/') {

                    break;
                }
                tc.current_index++;
            }
            insert_token(tokens, token(tc.lexeme_begin, tc.current_index - 1, HTML_IDENTIFIER));
            tc.lexeme_begin = tc.current_index + 1;

            if (input_string[tc.current_index] == '>')
            {
                insert_token(tokens, token(tc.current_index, tc.current_index, GREATER_THAN_SIGN));
                tc.lexeme_begin = tc.current_index + 1;
                continue;
            }

            // Tokenize the remainder of the current HTML element
            while (tc.current_index < strlen(input_string))
            {
                if (!tc.inside_string && input_string[tc.current_index] == '>') {
                    insert_token(tokens, token(tc.current_index, tc.current_index, GREATER_THAN_SIGN));
                    tc.lexeme_begin = tc.current_index + 1;
                    break;
                }

                if (tc.inside_string) {
                    if (input_string[tc.current_index] == '"') {
                        insert_token(tokens, token(tc.lexeme_begin, tc.current_index - 1, HTML_TEXT));
                        insert_token(tokens, token(tc.current_index, tc.current_index, QUOTATION_MARK));
                        tc.lexeme_begin = tc.current_index + 1;
                        tc.inside_string = false;
                    }

                    tc.current_index++; continue;
                }



                if (!tc.inside_string && input_string[tc.current_index] == '=') {
                    insert_token(tokens, token(tc.current_index, tc.current_index, EQUAL_SIGN));
                    tc.lexeme_begin = tc.current_index + 1;
                    tc.current_index++; continue;
                }
                if (!tc.inside_string && input_string[tc.current_index] == '/') {
                    insert_token(tokens, token(tc.current_index, tc.current_index, FORWARD_SLASH));
                    tc.lexeme_begin = tc.current_index + 1;
                    tc.current_index++; continue;                  
                }
                if (!tc.inside_string && input_string[tc.current_index] == '"') {
                    tc.inside_string = true;
                    insert_token(tokens, token(tc.lexeme_begin, tc.current_index, QUOTATION_MARK));
                    tc.lexeme_begin = tc.current_index + 1;
                    tc.current_index++; continue;
                }

                if (!tc.inside_string 
                    && (tc.current_index + 1) < strlen(input_string)
                    && input_string[tc.current_index + 1] == '=') {

                    insert_token(tokens, token(tc.lexeme_begin, tc.current_index, HTML_ATTRIBUTE_KEY));
                    tc.lexeme_begin = tc.current_index + 1;
                    tc.current_index++; continue;
                }

                tc.current_index++;
            }
        }




        if (!tc.inside_string && input_string[tc.current_index] == '\n') {
            insert_token(tokens, token(tc.current_index, tc.current_index, NEW_LINE));
            tc.lexeme_begin = tc.current_index + 1;
            tc.current_index++; continue;
        }


        if (!tc.inside_string 
            && (tc.current_index + 1) < strlen(input_string)
            && input_string[tc.current_index + 1] == '<') {

            // Text content of a HTML element
            insert_token(tokens, token(tc.lexeme_begin, tc.current_index, HTML_TEXT));
            tc.lexeme_begin = tc.current_index + 1;
        }


        tc.current_index++;
    }

}





void tokenize_first_element(TokensArray* tokens, char* input_string, TokenizerCache* tc)
{
    advance_to_next_char(tc, '<', input_string);
    insert_token(tokens, token(tc->current_index, tc->current_index, LESSER_THAN_SIGN));
    tc->lexeme_begin = tc->current_index + 1;
    tc->current_index++; 

    advance_to_next_char(tc, ' ', input_string);
    insert_token(tokens, token(tc->lexeme_begin, tc->current_index, HTML_IDENTIFIER));
    tc->lexeme_begin = tc->current_index + 1;
    tc->current_index++; 

    advance_to_next_char(tc, '>', input_string);
    insert_token(tokens, token(tc->lexeme_begin, tc->current_index - 1, DOC_TYPE));
    insert_token(tokens, token(tc->current_index, tc->current_index, GREATER_THAN_SIGN));
    tc->lexeme_begin = tc->current_index + 1;
    tc->current_index++;
}




void advance_to_next_char(TokenizerCache* tc, char chr, char* input_string)
{
    while (tc->current_index < strlen(input_string))
    {
        if (input_string[tc->current_index] == chr) {
            break;
        }
        tc->current_index++;
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
        case NEW_LINE:
            strcpy(str, "NEL");
            break;
        case DOC_TYPE:
            strcpy(str, "DOT");
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
