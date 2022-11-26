#ifndef LEXEME_HXX
#define LEXEME_HXX

#include <string>
#include <vector>


using std::string;
using std::vector;

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
int get_lexeme_type(string word) {
	if (word == "def") 			{ return 0x10; }
	else if (word == "set") 	{ return 0x11; }
	else if (word == "del") 	{ return 0x12; }
	else if (word == "req") 	{ return 0x13; }
	else if (word == "call") 	{ return 0x14; }
	else if (word == "method") 	{ return 0x15; }
	else if (word == "class") 	{ return 0x16; }
	else if (word == "return") 	{ return 0x17; }
	// else if (word == "->") 		{ return 0x18; }
	else if (word == "int") 	{ return 0x19; }
	else if (word == "float") 	{ return 0x1A; }
	else if (word == "string") 	{ return 0x1B; }
	else if (word == "ref") 	{ return 0x1C; }
	else if (word == "bool") 	{ return 0x1D; }
	else if (word == "array") 	{ return 0x1E; }
	else if (word == "map") 	{ return 0x1F; }
	else if (word == "null") 	{ return 0x20; }
	else if (word == "void") 	{ return 0x21; }
	else {
		// 0x01 0x02 here
		int potential_result = 0x00;
		size_t len = word.length();
		
		for (int i = 0; i < len; i++) {
			char c = word[i];
			if (c >= 0x30 && c <= 0x39 && (potential_result == 0x00 || potential_result == 0x02)) {
				potential_result = 0x02;
			} else if (
				(potential_result == 0x00 || potential_result == 0x01) &&
				(i == 0 && (c == 0x5F ||
					(c >= 0x41 && c <= 0x5A) ||
					(c >= 0x61 && c <= 0x7A)
				)) ||
				(
					i > 0 &&
					c == 0x5F ||
					(c >= 0x41 && c <= 0x5A) ||
					(c >= 0x61 && c <= 0x7A) || 
					(c >= 0x30 && c <= 0x39)
				)
			) {
				potential_result = 0x01;
			}
		}
		return potential_result;
	}
}

Lexeme collect_lexeme(string last_chain) {
	Lexeme lex = create_lexeme(
		get_lexeme_type(last_chain),
		last_chain
	);
	return lex;
}

vector<Lexeme> lexemize(string text) {
	vector<Lexeme> lexemes;

	string last_chain = "";

	char last_value = text[0];
	Lexeme lex;

	bool is_breaking = true;
	unsigned int last_block_offset = 0;

	for (unsigned int i = 1; i < text.length(); i ++) {
		char current_value = text[i];
		is_breaking = true;
		if (i > last_block_offset) {
			// if (last_value == '\n') {
			// 	std::cout << "\\n" << std::endl;
			// }
			switch (last_value) {
				case '/':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					if (current_value == '/') {
						lex = create_lexeme(0x03, "//");
						last_block_offset = i + 1;
					}
					else if (current_value == '*') {
						lex = create_lexeme(0x04, "/*");
						last_block_offset = i + 1;
					}
					else {
						lex = create_lexeme(0x2D, "/");
					}
					lexemes.push_back(lex);
					break;
				
				case '*':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					if (current_value == '/') {
						lex = create_lexeme(0x05, "*/");
						last_block_offset = i + 1;
					}
					else {
						lex = create_lexeme(0x2C, "*");
					}
					lexemes.push_back(lex);
					break;
				
				case '-':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					if (current_value == '>') {
						lex = create_lexeme(0x18, "->");
						last_block_offset = i + 1;
					} else {
						lex = create_lexeme(0x2B, "-");
					}
					lexemes.push_back(lex);
					break;
				
				case '(':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x06, "(");
					lexemes.push_back(lex);
					break;
				
				case ')':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x07, ")");
					lexemes.push_back(lex);
					break;
				
				case '{':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x08, "{");
					lexemes.push_back(lex);
					break;
				
				case '}':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x09, "}");
					lexemes.push_back(lex);
					break;
				
				case '[':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x0C, "[");
					lexemes.push_back(lex);
					break;
				
				case ']':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x0D, "]");
					lexemes.push_back(lex);
					break;
				
				case '<':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x0A, "<");
					lexemes.push_back(lex);
					break;
				
				case '>':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x0B, ">");
					lexemes.push_back(lex);
					break;
				
				case '\'':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x0E, "'");
					lexemes.push_back(lex);
					break;
				
				case '\"':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x0F, "\"");
					lexemes.push_back(lex);
					break;
				
				case '.':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x25, ".");
					lexemes.push_back(lex);
					break;
				
				case ';':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x26, ";");
					lexemes.push_back(lex);
					break;
				
				case ':':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x27, ":");
					lexemes.push_back(lex);
					break;
				
				case ',':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x28, ",");
					lexemes.push_back(lex);
					break;
				
				case '+':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x2A, "+");
					lexemes.push_back(lex);
					break;
				
				case '%':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x2E, "%");
					lexemes.push_back(lex);
					break;
				
				case '=':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x2F, "=");
					lexemes.push_back(lex);
					break;
				
				case ' ':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					break;
				case '\n':
					// std::cout << "endline" << std::endl;
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x29, "\\n");
					lexemes.push_back(lex);
					break;
				case '\t':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					break;
				default:
					is_breaking = false;
					break;
		}
		}

		if (!is_breaking) last_chain += last_value;
		last_value = current_value;
	}

	return lexemes;
}

#endif