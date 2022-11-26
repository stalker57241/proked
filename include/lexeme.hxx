#ifndef LEXEME_HXX
#define LEXEME_HXX

#include <string>

using std::string;

typedef struct {
    int type_id;
    string text;
} Lexeme;

Lexeme create_lexeme(int type_id, string text) {
    Lexeme lex;

    lex.type_id = type_id;
    lex.text = text;

    return lex;
}

#endif