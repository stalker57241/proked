#include "config.hxx"
#include "main.hxx"

/*
0x00 NULL:							|					| NULL
0x01 VARNAME:						| [_A-z][_A-z0-9]*	| VARIABLE NAME		+
0x02 VALUE:							| [0-9]*			| CONSTAINT			+
0x03 COMMENT:						| //				| COMMENT_SECTION	+
*///								|					|
// 0x04 OPEN_MULTILINE_COMMENT:		| /*				| COMMENT_SECTION	+
// 0x05 CLOSE_MULTILINE_COMMENT:	| */				| COMMENT_SECTION	+
/*									| 					| 
0x06 OPEN_BRACKET:					| (					| BLOCK_SELECTOR	+
0x07 CLOSE_BRACKET:					| )					| BLOCK_SELECTOR	+
0x08 OPEN_CURVY_BRACKET:			| {					| BLOCK_SELECTOR	+
0x09 CLOSE_CURVY_BRACKET:			| }					| BLOCK_SELECTOR	+
0x0A OPEN_TYPE_SELECT_BRACKET:		| <					| BLOCK_SELECTOR	+
0x0B CLOSE_TYPE_SELECT_BRACKET:		| >					| BLOCK_SELECTOR	+
0x0C OPEN_SQUARE_BRACKET:			| [					| BLOCK_SELECTOR	+
0x0D CLOSE_SQUARE_BRACKET:			| ]					| BLOCK_SELECTOR	+
0x0E QUOTE:							| '					| VALUE_POINTER		+
0x0F DOUBLE_QUOTE:					| "					| VALUE_POINTER		+
0x10 DEFINE:						| def				| KEYWORD
0x11 SET:							| set				| KEYWORD
0x12 DELETE:						| del				| KEYWORD
0x13 REQUIRE:						| req				| KEYWORD
0x14 CALL:							| call				| KEYWORD
0x15 METHOD:						| method			| KEYWORD
0x16 CLASS:							| class				| KEYWORD
0x17 RETURN:						| return			| KEYWORD
0x18 REDIRECT:						| ->				| KEYWORD
0x19 INTEGER:						| int				| KEYWORD
0x1A FLOAT:							| float				| KEYWORD
0x1B STRING:						| string			| KEYWORD
0x1C REFERENCE:						| ref				| KEYWORD
0x1D BOOLEAN:						| bool				| KEYWORD
0x1E ARRAY:							| array				| KEYWORD
0x1F MAP:							| map				| KEYWORD
0x20 AUTO:							| auto				| KEYWORD
0x21 POINT:							| .					| DELIMETER		+
0x22 SEMICOLON:						| ;					| DELIMETER		+
0x23 COLON:							| :					| DELIMETER		+
0x24 COMMA:							| ,					| DELIMETER		+
0x25 LINE_BREAK:					| \n				| DELIMETER		+
0x26 PLUS:							| +					| OPERATOR		+
0x27 MINUS:							| -					| OPERATOR		+
0x28 MULTIPLY:						| *					| OPERATOR		+
0x29 DIVIDE:						| /					| OPERATOR		+
0x2A DIVIDE_WITH_REMAINDER:			| %					| OPERATOR		+
0x2B EQUAL:							| =					| OPERATOR		+
0x2C 
0x2D 
0x2E 
0x2F 
*/

// 0x03 - 0x05: COMMENT_SECTION;
// 0x06 - 0x0D: BLOCK_SELECTOR;
// 0x0E - 0x0F: VALUE_POINTER;
// 0x10 - 0x20: KEYWORD;
// 0x21 - 0x27: DELIMETER;
// 0x28 - 0x2D: OPERATOR;


// THERE ARE NO += operations. We already have SET, so set a, req a + 2;


using std::string;
using std::vector;

vector<Lexeme> lexemize(string text);

int main(int argc, char const *argv[])
{
	if (argc < 1) {
		// report version
		std::cout << argv[0] << " v." << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
		std::cout << "Usage: " << argv[0] << " PATH" << std::endl;
		return 1;
	}
	
	string text = "/*\n\
commentary\n\
*/\n\
def a: int, 12;\n\
def b: int, 20;\n\
def add: ref, method(req a=0, req b=0) {\n\
	return (req a + req b);\n\
};\n\
def res: int;\n\
call add(req a, req b) -> res;\n\
call print(req res);\n\
\0";

	vector<Lexeme> lexemes_uncleaned = lexemize(text);

	vector<Lexeme> lexemes;
	
	for (unsigned int i = 0U; i < lexemes_uncleaned.size(); i ++) {
		if (lexemes_uncleaned[i].type_id != 0x00) {
			lexemes.push_back(lexemes_uncleaned[i]);
		}
	}
	using std::cout;
	using std::endl;
	using std::hex;
	for (unsigned int i = 0U; i < lexemes.size(); i ++) {
		cout << "TEXT:\t" << lexemes[i].text << "\nID:\t";
		if (lexemes[i].type_id < 0x10) {
			cout << "0x0" << hex << lexemes[i].type_id << " "; 
		}
		else {
			cout << "0x" << hex << lexemes[i].type_id << " "; 
		}
		// if (lexemes[i].type_id == 0x25) {
		// 	cout << endl;
		// }
		cout << endl;
	}

	return 0;
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
	else if (word == "auto") 	{ return 0x20; }
	else {
		// 0x01 0x02 here
		int potential_result = 0x00;
		int len = word.length();
		
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

	for (unsigned int i = 1; i < text.length() + 1; i ++) {
		char current_value = text[i];
		is_breaking = true;
		if (i > last_block_offset) {
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
						lex = create_lexeme(0x2B, "/");
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
						lex = create_lexeme(0x2A, "*");
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
						lex = create_lexeme(0x29, "-");
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
					lex = create_lexeme(0x21, ".");
					lexemes.push_back(lex);
					break;
				
				case ';':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x22, ";");
					lexemes.push_back(lex);
					break;
				
				case ':':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x23, ":");
					lexemes.push_back(lex);
					break;
				
				case ',':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x24, ",");
					lexemes.push_back(lex);
					break;
				
				case '+':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x28, "+");
					lexemes.push_back(lex);
					break;
				
				case '%':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x2C, "%");
					lexemes.push_back(lex);
					break;
				
				case '=':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x2D, "=");
					lexemes.push_back(lex);
					break;
				
				case ' ':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					break;
				case '\n':
					lex = collect_lexeme(last_chain);
					lexemes.push_back(lex);
					last_chain = "";
					lex = create_lexeme(0x25, "\n");
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