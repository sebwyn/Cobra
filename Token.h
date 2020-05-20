#pragma once

#include "Cobra.h"

#include "Object.h"

enum TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    SEMICOLON,

    ASSIGN,
    
    EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL,

    NOT,
    AND,
    OR,

    PLUS,
    MINUS,
    STAR,
    SLASH,

    IDENTIFIER,
    NUMBER,

    END,
    
    //keywords
    TRUE,
    FALSE,
    PRINT,
    WHILE,
    FUNC, 
	
    //purely grammatical types (not from lexer)
    GROUPING,
    CALL
};

std::string type_to_string(TokenType t);

struct Token {
   
    Token(int line, TokenType type)
     : line(line), type(type), text("") {}
 
    Token(int line, TokenType type, std::string text)
     : line(line), type(type), text(text) {
        //floats and identifier tokens need to store their values
        switch(type){
            case(NUMBER):
                value = Object(std::stof(text));
                break;
            case(TRUE):
                value = Object(true);
                break;
            case(FALSE):
                value = Object(false);
            default:
                break;
        } 
    }

    int line;
    TokenType type;
    std::string text;
    
    //some tokens can be mapped directly into objects in our language
    Object value;
};

