#include "tokenType.hpp"

// Single-character tokens.
const TokenType TokenType::LEFT_PAREN(0, "LEFT_PAREN");
const TokenType TokenType::RIGHT_PAREN(1, "RIGHT_PAREN");
const TokenType TokenType::LEFT_BRACE(2, "LEFT_BRACE");
const TokenType TokenType::RIGHT_BRACE(3, "RIGHT_BRACE");

const TokenType TokenType::COMMA(4, "COMMA");
const TokenType TokenType::DOT(5, "DOT");
const TokenType TokenType::MINUS(6, "MINUS");
const TokenType TokenType::PLUS(7, "PLUS");
const TokenType TokenType::SEMICOLON(8, "SEMICOLON");
const TokenType TokenType::SLASH(9, "SLASH");
const TokenType TokenType::STAR(10, "STAR");


// One or two character tokens.
const TokenType TokenType::BANG(11, "BANG");
const TokenType TokenType::BANG_EQUAL(12, "BANG_EQUAL");

const TokenType TokenType::EQUAL(13, "EQUAL");
const TokenType TokenType::EQUAL_EQUAL(14, "EQUAL_EQUAL");

const TokenType TokenType::GREATER(15, "GREATER");
const TokenType TokenType::GREATER_EQUAL(16, "GREATER_EQUAL");

const TokenType TokenType::LESS(17, "LESS");
const TokenType TokenType::LESS_EQUAL(18, "LESS_EQUAL");


// Literals.
const TokenType TokenType::IDENTIFIER(19, "IDENTIFIER");
const TokenType TokenType::STRING(20, "STRING");
const TokenType TokenType::NUMBER(21, "NUMBER");


// Keywords.
const TokenType TokenType::AND(22, "AND");
const TokenType TokenType::CLASS(23, "CLASS");
const TokenType TokenType::ELSE(24, "ELSE");
const TokenType TokenType::FALSE(25, "FALSE");
const TokenType TokenType::FUN(26, "FUN");
const TokenType TokenType::FOR(27, "FOR");
const TokenType TokenType::IF(28, "IF");
const TokenType TokenType::NIL(29, "NIL");
const TokenType TokenType::OR(30, "OR");

const TokenType TokenType::PRINT(31, "PRINT");
const TokenType TokenType::RETURN(32, "RETURN");
const TokenType TokenType::SUPER(33, "SUPER");
const TokenType TokenType::THIS(34, "THIS");
const TokenType TokenType::TRUE(35, "TRUE");
const TokenType TokenType::VAR(36, "VAR");
const TokenType TokenType::WHILE(37, "WHILE");

const TokenType TokenType::EOF(38, "EOF");