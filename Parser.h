#pragma once

#include "Lexer.h"

#include <iostream>
#include <exception>

class Parser {
public:
    Parser(const std::vector<Token>& tokens)
     : tokens(tokens) {
         parse();
     }

    void parse(){
        try {
            consume(LEFT_PAREN, "Expected Paren");
        } catch(ParseError& e){
            std::cout << e.getStr() << std::endl;
        }
    }
private:

    class ParseError : public std::exception {
    public:
        ParseError(Token t, std::string message){
            str = "Parse Error on line " + std::to_string(t.line) + " at token '" + t.to_string() + "': " + message;
        }

        const std::string& getStr(){ return str; }
    private:
        std::string str;
    };

    Token previous(){
        return tokens[current - 1];
    }
    Token peek(){
        return tokens[current];
    }
    bool atEnd(){
        return (peek().type == END);
    }
    bool check(TokenType type){
        if(atEnd()) return false;
        return (peek().type == type);
    }
    Token advance(){
        if(!atEnd()) current++;
        return previous();
    }
    bool match(TokenType type){
        if(check(type)){
            advance();
            return true;
        }
        return false;
    }
    template<typename First, typename... Args>
    bool match(First first, Args... rest){
        if(!match(first)){
            return match(rest...);
        }
        else return true;
    }
    Token consume(TokenType type, std::string message){
        if(check(type)) return advance();
        
        throw ParseError(peek(), message);
    }

    //functions for consuming grammar
    void expression();

    int current = 0;

    const std::vector<Token>& tokens;
};