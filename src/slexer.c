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

    lexer->line = 1;
    lexer->column = 1;

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
        Slexer_skip_comment(lexer);
        Slexer_skip_whitespace(lexer);

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
            return EOF_TOKEN;
        }
    }

    return EOF_TOKEN;
}

struct Stok *
Slexer_look_ahead
(struct Slexer *lexer) {
    struct Slexer clone = *lexer;
    return Slexer_get_next_token(&clone);
}

struct Stok *
Slexer_tokenize_string
(struct Slexer *lexer) {
    char lexeme[MAX_IDENTIFIER_SIZE];
    int len = 0;

    current(lexer);

    lexeme[len++] = lexer->cur;

    get_next_c(lexer);
    current(lexer);

    while (lexer->cur != '"' && lexer->cur != '\0') {
        if (lexer->cur == '\n') {
            struct Serror *error = Serror_set("SYNTAX_ERROR", "Invalid string", lexer);
            Serror_syntax_error(error);
            return NULL_TOKEN;
        }

        if (lexer->cur == '\\') {
            get_next_c(lexer);
            current(lexer);

            if (lexer->cur == 'n') {
                lexeme[len++] = '\n';

                get_next_c(lexer);
                current(lexer);
            } else if (lexer->cur == 't') {
                lexeme[len++] = '\t';

                get_next_c(lexer);
                current(lexer);
            } else {
                struct Serror *error = Serror_set("SYNTAX_ERROR", "Invalid escape sequence", lexer);
                Serror_syntax_error(error);
                return NULL_TOKEN;
            }
        } else {
            lexeme[len++] = lexer->cur;

            get_next_c(lexer);
            current(lexer);
        }
    }

    lexeme[len] = '\0';

    current(lexer);

    if (lexer->cur == '"') {
        get_next_c(lexer);
        current(lexer);

        char* new_lexeme = Sto_char(lexeme, len);

        return TOKEN(STRING, 0, new_lexeme);
    } else {
        struct Serror *error = Serror_set("SYNTAX_ERROR", "Invalid string", lexer);
        Serror_syntax_error(error);
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

    enum Stok_t tok = get_1_char(c1);

    if (tok == NULL_TOK) {
        struct Serror *error = Serror_set("SYNTAX_ERROR", "Invalid keyword token", lexer);
        Serror_syntax_error(error);
        return NULL_TOKEN;
    }

    return TOKEN(tok, 0, NULL);
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

    current(lexer);

    lexeme[len] = '\0';

    char* new_lexeme = Sto_char(lexeme, len);

    enum Stok_t identifer = Stok_get_identifier(new_lexeme);

    return TOKEN(identifer, 0, new_lexeme);
}