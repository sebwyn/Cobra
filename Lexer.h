#pragma once

#include <string>
#include <vector>
#include <memory>

#include <iostream>

enum TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    SEMICOLON,

    ASSIGN,
    
    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_EQUAL,
    LESS_THAN_EQUAL,

    NOT,
    AND,
    OR,

    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,

    IDENTIFIER,
    FLOAT,

    END
};

std::string type_to_string(TokenType t);

struct Token {
    
    template<typename T>
    Token(int line, TokenType type, T _value)
     : line(line), type(type) {
        value = std::static_pointer_cast<void>(std::make_shared<T>(_value));
    }

    std::string to_string(){
        std::string stringValue = " ";
        switch(type){
            case(IDENTIFIER):
                stringValue += *(std::static_pointer_cast<std::string>(value));
                break;
            case(FLOAT):
                stringValue += std::to_string(*(std::static_pointer_cast<float>(value)));
                break;
            default:
                break;
        }
        return type_to_string(type) + stringValue;
    }

    int line;
    TokenType type;
    std::shared_ptr<void> value;
};

class Lexer {
public:
    Lexer(const std::string& text);
    
    void lex();

    std::vector<Token>& getTokens(){ return tokens; }
private:

    bool atEnd(){
        if(current > text.length()) return true;
        return false;
    }

    char advance(){
        current++;
        if(atEnd()) return '\0';
        return text[current - 1];
    }

    bool match(char c){ 
        if(peek() == c){
            advance(); 
            return true;
        }
        return false;
    }
    
    char peek(){
        if(atEnd()) return '\0'; 
        return text[current];
    }
    
    void addToken(TokenType type){
        tokens.push_back(Token(line, type, 0));
    }
    
    template<typename T>
    void addToken(TokenType type, T value){
        tokens.push_back(Token(line, type, value)); 
    }

    void emitError(const std::string& message);
    
    void getToken();
    
    //matching functions
    bool isAlpha(char c){
        if(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) return true;
        return false;
    }
    bool isDigit(char c){
        if('0' <= c && c <= '9') return true;
        return false;
    }
    bool isAlphaNumeric(char c){
        return isAlpha(c) | isDigit(c);
    }

    //functions for specific language implementations
    void getLineComment();
    void getIdentifier();
    void getFloat();

    int start = 0; //start of the lexeme
    int current = 0; //current character of the lexeme
    int line = 0; //current line used for errors and such
    
    const std::string& text;

    std::vector<Token> tokens;
};
