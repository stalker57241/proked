#ifndef PARSEME_HXX
#define PARSEME_HXX

#include <string>
#include <vector>
#include "lexeme.hxx"
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;


// class ExpressionParseme;

// class StatementsParseme;
// class VariableParseme;
// class NumberParseme;
// class BinaryOperatorParseme;
// class UnaryOperatorParseme;

/* PARSEME_TYPE_IDS
0x00	| NULL
0x01	| STATEMENTS_LIST
0x02	| VARIABLE
0x03	| NUMBER
0x04	| BINARY
0x05	| UNARY
*/

class ExpressionParseme {
	public:
		vector<ExpressionParseme> children;
		bool has_children = false;
		unsigned int parseme_type_id;
		unsigned int type_id;

		string value;

		ExpressionParseme* left_operand;
		ExpressionParseme* right_operand;

		ExpressionParseme() {
			this->parseme_type_id = 0x01;
			children = vector<ExpressionParseme>();
			has_children = true;
		}
		ExpressionParseme(
			string value,
			bool is_varname = false
		) {
			this->value = value;
			this->parseme_type_id = is_varname ? 0x02 : 0x03;
		}
		ExpressionParseme(
			unsigned int type_id,
			ExpressionParseme* left_operand
		) {
			this->parseme_type_id = 0x05;
			this->type_id = type_id;
			this->left_operand = left_operand;
		}
		ExpressionParseme(
			unsigned int type_id,
			ExpressionParseme* left_operand,
			ExpressionParseme* right_operand
		) {
			this->type_id = type_id;
			this->parseme_type_id = 0x04;
			this->left_operand = left_operand;
			this->right_operand = right_operand;
		}
		~ExpressionParseme() {
			delete left_operand;
			delete right_operand;
		}
		void add_child(ExpressionParseme parseme) {
			this->children.push_back(parseme);
		}
		size_t get_child_count() {
			return this->children.size();
		}
		vector<ExpressionParseme> get_children() {
			// vector<Parseme> parsemes;

			return children;
		}
};


// class StatementsParseme : ExpressionParseme {
// 	protected:
// 		vector<ExpressionParseme> children;
// 	public:
// 		StatementsParseme();
// 		void add_child(ExpressionParseme parseme) {
// 			this->children.push_back(parseme);
// 		}
// 		unsigned int get_child_count() {
// 			return this->children.size();
// 		}
// 		vector<ExpressionParseme> get_children() {
// 			// vector<Parseme> parsemes;
//
// 			return children;
// 		}
// };
//
// class VariableParseme : ExpressionParseme {
// 	protected:
// 		string varname;
// 	public:
// 		VariableParseme(string varname) {
// 			this->varname = varname;
// 		};
// };
//
// class NumberParseme : ExpressionParseme {
// 	protected:
// 		string value;
// 	public:
// 		NumberParseme(string value) {
// 			this->value = value;
// 		};
// };
//
// class BinaryOperatorParseme : ExpressionParseme {
// 	protected:
// 		unsigned int oper;
// 		ExpressionParseme left_operand;
// 		ExpressionParseme right_operand;
// 	public:
// 		BinaryOperatorParseme(
// 			unsigned int oper,
// 			ExpressionParseme l_operand,
// 			ExpressionParseme r_operand
// 		) {
// 			this->oper = oper;
// 			this->left_operand = l_operand;
// 			this->right_operand = r_operand;
// 		}
// };
// class UnaryOperatorParseme : ExpressionParseme {
// 	protected:
// 		unsigned int oper;
// 		ExpressionParseme operand;
// 	public:
// 		UnaryOperatorParseme(
// 			unsigned int oper,
// 			ExpressionParseme operand
// 		) {
// 			this->oper = oper;
// 			this->operand = operand;		
// 		}
// };
//
// typedef BinaryOperatorParseme DefineParseme;
// typedef BinaryOperatorParseme SetParseme;
// typedef BinaryOperatorParseme DeleteParseme;
// typedef BinaryOperatorParseme RequireParseme;
// typedef BinaryOperatorParseme TypeParseme;
// typedef BinaryOperatorParseme EqualsParseme;
//
// typedef UnaryOperatorParseme DeleteParseme;

uint32_t next_curvy_bracket(vector<Lexeme> lexemes, uint32_t from) {
	size_t len = lexemes.size();

	if (from > len) {
		throw new std::exception("out of bounds");
	}

	int bracket_level = 0x00;
	std::cout << "finding semicolon" << std::endl;
	for (uint32_t i = from; i < len; i++) {
		std::cout << "id: " << i << "\ttype: " << lexemes[i].type_id << std::endl << "bracket_level:" << bracket_level << std::endl;
		if (lexemes[i].type_id == 0x08 || lexemes[i].type_id == 0x06) {
			std::cout << "move_down";
			bracket_level += 1;
		}
		else if (bracket_level == 0x00 && lexemes[i].type_id == 0x09) {
			std::cout << "exiting" << std::endl;
			return i;
		}
		else if (lexemes[i].type_id == 0x09 || lexemes[i].type_id == 0x07) {
			std::cout << "move_up";
			bracket_level -= 1;
			if (bracket_level < 0) {
				throw new std::exception("unexcepted closed bracket");
			}
		}
	}
	throw new std::exception("operand not found");
} 
uint32_t next_operand(vector<Lexeme> lexemes, uint32_t from, uint32_t what = 0x26) {
	size_t len = lexemes.size();

	if (from > len) {
		throw new std::exception("out of bounds");
	}

	int bracket_level = 0x00;
	std::cout << "finding semicolon" << std::endl;
	for (uint32_t i = from; i < len; i++) {
		std::cout << "id: " << i << "\ttype: " << lexemes[i].type_id << std::endl << "bracket_level:" << bracket_level << std::endl;
		if (lexemes[i].type_id == 0x08 || lexemes[i].type_id == 0x06) {
			std::cout << "move_down";
			bracket_level += 1;
		}
		else if (lexemes[i].type_id == 0x09 || lexemes[i].type_id == 0x07) {
			std::cout << "move_up";
			bracket_level -= 1;
			if (bracket_level < 0) {
				throw new std::exception("unexcepted closed bracket");
			}
		} else if (bracket_level == 0x00 && lexemes[i].type_id == what) {
			std::cout << "exiting" << std::endl;
			return i;
		}
	}
	throw new std::exception("operand not found");
} 
// ExpressionParseme parse(vector<Lexeme> lexemes);

ExpressionParseme parse(vector<Lexeme> lexemes) {

	using std::cout;
	using std::endl;
	ExpressionParseme root = ExpressionParseme();
	cout << "parsing" << endl;
	vector<Lexeme> sublexeme;
	// cout << "init sublexeme vector" << endl;
	ExpressionParseme par;
	// cout << "create ExpressionParseme par" << endl;
	
	size_t size = lexemes.size();

	cout << "list lexemes" << endl;
	for (unsigned int i = 0; i < size; i++ ) {
		cout << "0x" << std::hex << lexemes[i].type_id << " ";
		if (lexemes[i].type_id == 0x26) {
			cout << endl;
		}
	}
	cout << endl;

	// cout << "lexemes size: " << size << endl;
	uint32_t par_type = 0x00U;

	// cout << "par_type set to 0x" << std::hex << par_type << endl;

	uint32_t awaited_position = 0x00U;
	// cout << "awaited_position " << std::hex << awaited_position << endl;

	for (uint32_t i = 0U; i < size; i++) {
		Lexeme lex = lexemes[i];
		cout << "id: " << i << endl;

		if (awaited_position == 0x00U) {
			cout << "aw_p: 0x00U, type_id: 0x" << std::hex << lex.type_id << endl;
			if (
				(lex.type_id >= 0x10 && lex.type_id <= 0x14 && lex.type_id != 0x13) ||
				lex.type_id == 0x17
			) {
				try {
					cout << "getting position of next operand" << endl;
					awaited_position = next_operand(lexemes, i);
					cout << "awaited_position: " << awaited_position << endl;
				}
				catch (std::exception exc) {
					cout << "ecxeption at getting position of next operand" << endl;
					cout << "Exception: " << exc.what() << endl;
					throw new std::exception(exc.what());
				}
				// std::cout << "type_id: 0x" << std::hex << lex.type_id << std::endl;
				par_type = lex.type_id;
				cout << "par_type was set: 0x" << std::hex << par_type << endl;
			}
			else if (
				(lex.type_id >= 0x25 && lex.type_id <= 0x28 && lex.type_id != 0x26) ||
				(lex.type_id >= 0x2A && lex.type_id <= 0x2F)
			) {
				cout << std::hex << lex.type_id << endl;
				cout << "got both_sided operator" << endl;
				if (i + 1 != lexemes.size()) {
					cout << "right operand avaible" << endl;
					// std::cout << "BinaryOperator:" << lex.text << std::endl;
					// vector<Lexeme> loperands;
					vector<Lexeme> roperands;
					// for (int j = 0; j < i; j ++) {
					// 	loperands.push_back(lexemes[j]);
					// }
					for (int j = i + 1; j < lexemes.size(); j ++) {
						roperands.push_back(lexemes[j]);
					}
					return ExpressionParseme(lex.type_id, &parse(sublexeme), &parse(roperands));
				}
				else {
					throw new std::exception("No right part");
				}
			}
			else if (
				(lex.type_id == 0x06) ||
				(lex.type_id == 0x08) ||
				(lex.type_id == 0x0A) ||
				(lex.type_id == 0x0C) ||
				(lex.type_id == 0x0E) ||
				(lex.type_id == 0x0F) 
			){

				if (lex.type_id < 0x0E && lex.type_id != 0x08) {
					try {
						cout << "getting position of next operand" << endl;
						awaited_position = next_operand(lexemes, i, lex.type_id + 0x01);
						cout << "awaited_position: " << awaited_position << endl;
					}
					catch (std::exception exc) {
						cout << "ecxeption at getting position of next operand" << endl;
						cout << "Exception: " << exc.what() << endl;
						throw new std::exception(exc.what());
					}
					par_type = lex.type_id;
					cout << "par_type was set: 0x" << std::hex << par_type << endl;
				} else if (lex.type_id == 0x08) {
					try {
						cout << "getting position of next operand" << endl;
						awaited_position = next_curvy_bracket(lexemes, i);
						cout << "awaited_position: " << awaited_position << endl;
					}
					catch (std::exception exc) {
						cout << "ecxeption at getting position of next operand" << endl;
						cout << "Exception: " << exc.what() << endl;
						throw new std::exception(exc.what());
					}
					par_type = lex.type_id;
					cout << "par_type was set: 0x" << std::hex << par_type << endl;
				} else{
					try {
						cout << "getting position of next operand" << endl;
						awaited_position = next_operand(lexemes, i);
						cout << "awaited_position: " << awaited_position << endl;
					}
					catch (std::exception exc) {
						cout << "ecxeption at getting position of next operand" << endl;
						cout << "Exception: " << exc.what() << endl;
						throw new std::exception(exc.what());
					}
					par_type = lex.type_id;
					cout << "par_type was set: 0x" << std::hex << par_type << endl;
				}
			} else if (
				(lex.type_id >= 0x01 && lex.type_id <= 0x02)
			) {
				cout << "value/variable found" << endl;
				// std::cout << "value/var:" << lex.text << std::endl;
				return ExpressionParseme(lex.text, lex.type_id == 0x01);
			}
		}
		else if (awaited_position >= 0x00) {
			// cout << "awaited_position >= 0" << endl;
			if (i == awaited_position) {
				awaited_position = 0x00;;
				par = parse(sublexeme);
				root.add_child(par);
				sublexeme.clear();
				cout << "break: " << i << endl;
			}
			else {
				sublexeme.push_back(lexemes[i]);
			}
		}
	}
	cout << "loop finished" << root.get_child_count() << endl;
	return root;
}

#endif // PARSEME_HXX