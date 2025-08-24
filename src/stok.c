#include "stok.h"

char* 
Stok_t_print
(enum Stok_t type) {
    switch (type) {
        case ADD:
            return "+"; 
        case SUB:
            return "-"; 
        case MUL:
            return "*"; 
        case DIV:
            return "/"; 
        case LPAREN:
            return "("; 
        case RPAREN:
            return ")"; 
        case LBRACKET:
            return "["; 
        case RBRACKET:
            return "]"; 
        case NUMBER:
            return "NUMBER"; 
        case STRING:
            return "STRING"; 
        case IDENTIFIER:
            return "IDENTIFIER";
        case NULL_TOK:
            return "NULL_TOK";
        case EOF_TOK:
            return "EOF_TOK";
        case LET:
            return "LET";
        case ASSIGN:
            return "=";
        case IF:
            return "IF";
        case WHILE:
            return "WHILE";
        case DO:
            return "DO";
        case FOR:
            return "FOR";
        default:
            return "UNKNOWN"; 
    }
}

struct Stok *
Stok_new(void) {
    struct Stok *token = malloc(sizeof(struct Stok));

    token->type = NULL_TOK;
    token->value = 0;
    token->lexeme = NULL;
    return token;
}

struct Stok *
Stok_init
(enum Stok_t type, float value, char *lexeme) {
    struct Stok *token = Stok_new();
    
    token->type = type;
    token->value = value;
    token->lexeme = lexeme;

    // printf("Token: %s, value: %f, lexeme: %s\n", Stok_t_print(token->type), token->value, token->lexeme);

    return token;
}

int 
Stok_free
(struct Stok *token) {
    free(token);
    token = NULL;
    return 0;
}

enum Stok_t
get_1_char
(char c) {
    switch (c) {
        case '+':
            return ADD;
        case '(':
            return LPAREN;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '/':
            return DIV;
        case ')':
            return RPAREN;
        case '[':
            return LBRACKET;
        case ']':
            return RBRACKET;
        case '=':
            return ASSIGN;
        default:
            return NULL_TOK;
    }

    return NULL_TOK;
}