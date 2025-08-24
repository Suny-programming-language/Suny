#include "slexer.h"

struct Slexer *
Slexer_new(void) {
    struct Slexer *lexer = malloc(sizeof(struct Slexer));

    lexer->input = NULL;
    lexer->token = Stok_new();
    
    lexer->index = 0;

    lexer->cur = 0;
    lexer->next = 0;
    lexer->prev = 0;

    lexer->line = 0;
    lexer->column = 0;

    return lexer;
}

struct Slexer *
Slexer_init
(char *input) {
    struct Slexer *lexer = Slexer_new();

    lexer->input = input;

    return lexer;
}

int 
Slexer_free
(struct Slexer *lexer) {
    free(lexer);
    lexer = NULL;
    return 0;
}

char 
Slexer_get_next_c
(struct Slexer *lexer) {
    lexer->cur = lexer->input[lexer->index++];
    lexer->column++;

    if (lexer->cur == '\n') {
        newline(lexer);
    }

    return lexer->cur;
}

int 
Slexer_skip_whitespace
(struct Slexer *lexer) {
    while (whitespace(lexer)) {
        Slexer_get_next_c(lexer);
        current(lexer);
    }

    return 0;
}

int 
Slexer_skip_comment
(struct Slexer *lexer) {
    if (lexer->cur == '#') {
        while (lexer->cur != '\n') {
            Slexer_get_next_c(lexer);
        }
    }

    return 0;
}

struct Stok *
Slexer_get_next_token
(struct Slexer *lexer) {
    for (;;) {
        Slexer_skip_whitespace(lexer);
        Slexer_skip_comment(lexer);

        char c = Slexer_get_next_c(lexer);

        if (isdigit(lexer)) {
            return Slexer_tokenize_number(lexer);
        } 
        
        if (isalpha(lexer)) {
            return Slexer_tokenize_identifier(lexer);
        }

        if (is_lexer_key(lexer)) {
            return Slexer_tokenize_keyword(lexer);
        }

        if (c == '\n') {
            current(lexer);
            newline(lexer);
        }

        if (c == '"') {
            return Slexer_tokenize_string(lexer);
        }

        if (c == '\0') {
            break;
        }
    }

    return EOF_TOKEN;
}

struct Stok *
Slexer_tokenize_string
(struct Slexer *lexer) {
    get_next_c(lexer);
    current(lexer);

    char lexeme[MAX_IDENTIFIER_SIZE];
    int len = 0;

    while (lexer->cur != '"' && lexer->cur != '\0') {
        if (lexer->cur == '\n') {
            struct Serror *error = Serror_set("SYNTAX_ERROR", "Invalid string", lexer);
            Serror_syntax_error(error);
            return NULL_TOKEN;
        }

        lexeme[len++] = lexer->cur;

        get_next_c(lexer);
        current(lexer);
    }

    lexeme[len] = '\0';

    current(lexer);

    if (lexer->cur == '"') {
        get_next_c(lexer);
        current(lexer);

        char* new_lexeme = Sto_char(lexeme, len);

        return TOKEN(STRING, 0, new_lexeme);
    }

    return NULL_TOKEN;
}

struct Stok *
Slexer_tokenize_number
(struct Slexer *lexer) {
    char number[MAX_NUMBER_LEN];
    
    int len = 0;

    int has_dot = 0;

    number[len++] = lexer->cur;
    current(lexer);

    while (is_potential_digit_char(lexer)) {
        if (lexer->cur == '.') {
            if (has_dot) {
                struct Serror *error = Serror_set("SYNTAX_ERROR", "Invalid number", lexer);
                Serror_syntax_error(error);
                return NULL_TOKEN;
            }

            has_dot = 1;
        }

        number[len++] = lexer->cur;

        get_next_c(lexer);
        current(lexer);

        if (!isdigit(lexer) && lexer->cur != '.' && !whitespace(lexer)) {
            struct Serror *error = Serror_set("SYNTAX_ERROR", "Invalid number", lexer);
            Serror_syntax_error(error);
            return NULL_TOKEN;
        }
    }

    current(lexer);
    
    number[len] = '\0';

    char* new_number = Sto_char(number, len);

    float value = (float) Satof(new_number);

    return TOKEN(NUMBER, value, new_number);
}

struct Stok *
Slexer_tokenize_keyword
(struct Slexer *lexer) {
    char c1 = lexer->cur;
    current(lexer);
    return TOKEN(get_1_char(c1), 0, NULL);
}

struct Stok *
Slexer_tokenize_identifier
(struct Slexer *lexer) {
    char lexeme[MAX_IDENTIFIER_SIZE];

    int len = 0;

    lexeme[len++] = lexer->cur;

    current(lexer);

    while (is_potential_identifier_char(lexer) || isdigit(lexer)) {
        lexeme[len++] = lexer->cur;

        get_next_c(lexer);
        current(lexer);
    }

    lexeme[len] = '\0';

    char* new_lexeme = Sto_char(lexeme, len);

    if (strcmp(new_lexeme, "let") == 0) {
        return TOKEN(LET, 0, new_lexeme);
    } else if (strcmp(new_lexeme, "print") == 0) {
        return TOKEN(PRINT_T, 0, new_lexeme);  
    } else {
        return TOKEN(IDENTIFIER, 0, new_lexeme);
    }

    return NULL_TOKEN;
}