#pragma once

#include <exception>

#include "Cobra.h"

#include "Token.h"
#include "AST.h"

class Parser {
public:
    class ParseError : public std::exception {
    public:
        ParseError(Token t, std::string message){
            str = 
                "Parse Error on line " + std::to_string(t.line)
                + " at lexeme '" + t.text + "': " + message;
        }

        const std::string& getStr(){ return str; }
    private:
        std::string str;
    };

    Parser(const std::vector<Token>& tokens)
     : tokens(tokens) {}

    const std::vector<Stmt*>& parse(){
        try {
            while(!atEnd())    
        	    statements.push_back(statement());
        } catch(ParseError& e){
            std::cout << e.getStr() << std::endl;
        }
        return statements;
    }

    ~Parser(){
        for(auto stmt : statements){
            delete stmt;
        }
    }  
    
private:

    const Token& previous(){
        return tokens[current - 1];
    }
    const Token& peek(){
        return tokens[current];
    }
    bool atEnd(){
        return (peek().type == END);
    }
    bool check(TokenType type){
        if(atEnd()) return false;
        return (peek().type == type);
    }
    const Token& advance(){
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
        } else return true;
    }
    const Token& consume(TokenType type, std::string message){
        if(check(type)) return advance();
        std::cout << "Throwing Parse Error" << std::endl;	
        throw ParseError(peek(), message);
    }

    //functions for consuming grammar
    // parsing statements
    Stmt* statement();
    
    //parsing expressions
    Expr* expression();
    Expr* assignment();
    Expr* logicalAnd();
    Expr* logicalOr();
    Expr* equality();
    Expr* comparison();
    Expr* addition();
    Expr* multiplication();
    Expr* unary();
    Expr* primary();
    
    //used in panic error mode    
    void synchronize();

    int current = 0;
    const std::vector<Token>& tokens;
    std::vector<Stmt*> statements;
};
