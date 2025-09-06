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
        case COMMA:
            return ",";
        case BIGGER:
            return ">";
        case SMALLER:
            return "<";
        case BIGGER_EQUALS:
            return ">=";
        case SMALLER_EQUALS:
            return "<=";
        case NOT_EQUALS:
            return "!=";
        case EQUALS:
            return "==";
        case PRINT_T:
            return "PRINT";
        case FUNCTION:
            return "FUNCTION";
        case RETURN:
            return "RETURN";
        case END:
            return "END";
        case OR:
            return "OR";
        case AND:
            return "AND";
        case NOT:
            return "NOT";
        case DO:
            return "DO";
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
Stok_get_identifier(char *lexeme) {
    if (strcmp(lexeme, LET_S) == 0) {
        return LET;
    } else if (strcmp(lexeme, IF_S) == 0) {
        return IF;
    } else if (strcmp(lexeme, WHILE_S) == 0) {
        return WHILE;
    } else if (strcmp(lexeme, ELSE_S) == 0) {
        return ELSE;
    } else if (strcmp(lexeme, ELIF_S) == 0) {
        return ELIF;
    } else if (strcmp(lexeme, THEN_S) == 0) {
        return THEN;
    } else if (strcmp(lexeme, DO_S) == 0) {
        return DO;
    } else if (strcmp(lexeme, FOR_S) == 0) {
        return FOR;
    } else if (strcmp(lexeme, IN_S) == 0) {
        return IN_T;
    } else if (strcmp(lexeme, NOT_S) == 0) {
        return NOT;
    } else if (strcmp(lexeme, IS_S) == 0) {
        return IS;
    } else if (strcmp(lexeme, AND_S) == 0) {
        return AND;
    } else if (strcmp(lexeme, OR_S) == 0) {
        return OR;
    } else if (strcmp(lexeme, FUNCTION_S) == 0) {
        return FUNCTION;
    } else if (strcmp(lexeme, RETURN_S) == 0) {
        return RETURN;
    } else if (strcmp(lexeme, IMPORT_S) == 0) {
        return IMPORT;
    } else if (strcmp(lexeme, INCLUDE_S) == 0) {
        return INCLUDE;
    } else if (strcmp(lexeme, TRUE_S) == 0 || strcmp(lexeme, "True") == 0) {
        return TRUE_T;
    } else if (strcmp(lexeme, FALSE_S) == 0 || strcmp(lexeme, "False") == 0) {
        return FALSE_T;
    } else if (strcmp(lexeme, END_S) == 0) {
        return END;
    } else if (strcmp(lexeme, BREAK_S) == 0) {
        return BREAK;
    } else if (strcmp(lexeme, CONTINUE_S) == 0) {
        return CONTINUE;
    } else if (strcmp(lexeme, CLASS_S) == 0) {
        return CLASS;
    } else {
        return IDENTIFIER;
    }    
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
        case '>':
            return BIGGER;
        case '<':
            return SMALLER;
        case '!':
            return NOT;
        case ',':
            return COMMA;
        case '.':
            return DOT;
        case ':':
            return COLON;
        case ';':
            return SEMICOLON;
        default:
            return NULL_TOK;
    }

    return NULL_TOK;
}

enum Stok_t 
get_2_char
(char c1, char c2) {
    if (c1 == '=' && c2 == '=') return EQUALS;
    if (c1 == '>' && c2 == '=') return BIGGER_EQUALS;
    if (c1 == '<' && c2 == '=') return SMALLER_EQUALS;
    if (c1 == '!' && c2 == '=') return NOT_EQUALS;
    if (c1 == '+' && c2 == '=') return ADD_ASSIGN;
    if (c1 == '-' && c2 == '=') return SUB_ASSIGN;
    if (c1 == '*' && c2 == '=') return MUL_ASSIGN;
    if (c1 == '/' && c2 == '=') return DIV_ASSIGN;

    enum Stok_t tok = get_1_char(c1);

    return tok;
}

int
is_2_char
(char c1, char c2) {
    if (c1 == '=' && c2 == '=') return 1;
    if (c1 == '>' && c2 == '=') return 1;
    if (c1 == '<' && c2 == '=') return 1;
    if (c1 == '!' && c2 == '=') return 1;
    if (c1 == '+' && c2 == '=') return 1;
    if (c1 == '-' && c2 == '=') return 1;
    if (c1 == '*' && c2 == '=') return 1;
    if (c1 == '/' && c2 == '=') return 1;
    return 0;
}