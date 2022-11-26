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
0x20 NULL:							| null				| KEYWORD
0x21 VOID:							| void				| KEYWORD
0x22 								|					|
0x23 								|					|
0x24 								|					|
0x25 POINT:							| .					| DELIMETER		+
0x26 SEMICOLON:						| ;					| DELIMETER		+
0x27 COLON:							| :					| DELIMETER		+
0x28 COMMA:							| ,					| DELIMETER		+
0x29 LINE_BREAK:					| \n				| DELIMETER		+
0x2A PLUS:							| +					| OPERATOR		+
0x2B MINUS:							| -					| OPERATOR		+
0x2C MULTIPLY:						| *					| OPERATOR		+
0x2D DIVIDE:						| /					| OPERATOR		+
0x2E DIVIDE_WITH_REMAINDER:			| %					| OPERATOR		+
0x2F EQUAL:							| =					| OPERATOR		+
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


int main(int argc, char const *argv[])
{
	string text;
	if (argc < 2) {
		// report version
		std::cout << argv[0] << " v." << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
		std::cout << "Usage: " << argv[0] << " PATH" << std::endl;
		// return 1;
	
		return 1;
	}
	{
		using std::ifstream;

		ifstream mfile(argv[argc - 1]);

		if (mfile.is_open()) {
			char buffer_char;
			while (mfile) {
				buffer_char = mfile.get();
				if (buffer_char == '\n') {
					text.push_back(buffer_char);
				}
				else {
					text.push_back(buffer_char);
				}
				// std::cout << "endline" << std::endl;
				
			}
		}
	}

	vector<Lexeme> lexemes_uncleaned = lexemize(text);

	vector<Lexeme> lexemes;
	
	std::cout << "cleaning" << std::endl;

	for (unsigned int i = 0U; i < lexemes_uncleaned.size(); i ++) {
		// std::cout << "TEXT: " << lexemes_uncleaned[i].text << "\nID: " << lexemes_uncleaned[i].type_id << std::endl;
		if (lexemes_uncleaned[i].type_id != 0x00) {
			lexemes.push_back(lexemes_uncleaned[i]);
		}
	}
	{
		using std::cout;
		using std::endl;
		using std::hex;
		
		cout << "displaying" << endl;
		
		for (unsigned int i = 0U; i < lexemes.size(); i ++) {
			// cout << "TEXT:\t" << lexemes[i].text << "\nID:\t";
			if (lexemes[i].type_id < 0x10) {
				cout << "0x0" << hex << lexemes[i].type_id << " "; 
			}
			else {
				cout << "0x" << hex << lexemes[i].type_id << " "; 
			}
			if (lexemes[i].type_id == 0x29) {
				cout << endl;
			}
		}
		cout << endl;
	}

	return 0;
}

