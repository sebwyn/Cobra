#pragma once

#include <exception>

#include "Cobra.h"

#include "Token.h"
#include "Expr.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens)
     : tokens(tokens) {}
    
    std::string stringify(const std::unique_ptr<Expr>& e){
        std::string text = "";
        if(e->operands.size() > 0) text += "(";
        text += e->root.text;
        for(const auto& operand : e->operands){
            text += " " + stringify(operand);
        }
        if(e->operands.size() > 0) text += ")";
        return text;
    }

    const std::unique_ptr<Expr>& parse(){
        try {
            expr = expression();
            std::cout << stringify(expr) << std::endl;
        } catch(ParseError& e){
            std::cout << e.getStr() << std::endl;
            
            expr = std::unique_ptr<Expr>(new Expr(Token(0, END)));
        }
        return expr;
    }
private:
    
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
        throw ParseError(peek(), message);
    }

    //functions for consuming grammar
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> addition();
    std::unique_ptr<Expr> multiplication();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();
    
    //used in panic error mode    
    void synchronize();

    int current = 0;
    const std::vector<Token>& tokens;
    std::unique_ptr<Expr> expr;
};
