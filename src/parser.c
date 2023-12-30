#include <stdio.h>
#include <stdbool.h>

#include "tokenizer.h"

typedef struct {
    int current_index;
    TokensArray *tokens;
} ParserCache;

enum ElementName = {
    GREATER_THAN_SIGN,
    LESSER_THAN_SIGN,
    HTML_IDENTIFIER,
    HTML_ATTRIBUTES,
    EQUAL_SIGN, 
    KEY,
    VALUE
};

typedef struct {
    enum ElementName name;
    bool terminal;
} ProductionElement;




ParserCache _HTML_element(ParserCache cache)
{
    Token current_token = cache.tokens->tokens[cache.current_index];

    printf("%d, %d, %d\n", current_token.start_index, current_token.end_index, current_token.token_type);
    return cache;
}


int main() {
    TokensArray tokens;
    init_tokens_array(&tokens, 50);
    insert_token(&tokens, token(1,1, LESSER_THAN_SIGN));
    insert_token(&tokens, token(1,1, HTML_IDENTIFIER));
    insert_token(&tokens, token(1,1, HTML_ATTRIBUTE_KEY));
    insert_token(&tokens, token(1,1, EQUAL_SIGN));
    insert_token(&tokens, token(1,1, QUOTATION_MARK));
    insert_token(&tokens, token(1,1, HTML_TEXT));
    insert_token(&tokens, token(1,1, QUOTATION_MARK));
    

    ParserCache parser_cache = {
        0, &tokens
    };
    _HTML_element(parser_cache);



    free_tokens_array(&tokens);
    return 1;
}
