#pragma once

#include "Cobra.h"

#include "Object.h"

enum TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
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

    TRUE,
    FALSE,

    //purely grammatical types (not from lexer)
    GROUPING,
    NEGATE
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
                value = std::make_shared<FloatObject>(std::stof(text));
                break;
            case(TRUE):
                value = std::make_shared<BoolObject>(true);
                break;
            case(FALSE):
                value = std::make_shared<BoolObject>(false);
            default:
                break;
        } 
    }

    int line;
    TokenType type;
    std::string text;
    
    //some tokens can be mapped directly into objects in our language
    std::shared_ptr<Object> value;
};

