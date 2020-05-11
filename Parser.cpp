#include "Parser.h"

#include <iostream>
//functions for consuming grammar
std::unique_ptr<Expr> Parser::expression(){
    return equality();
}
std::unique_ptr<Expr> Parser::equality() {
    auto expr = comparison();
    while(match(EQUAL, NOT_EQUAL)){
        Token operation = previous();
        auto right = comparison();
        expr = std::unique_ptr<Expr>(
            new Expr(operation, std::move(expr), std::move(right)));
    }
    return expr;
}
std::unique_ptr<Expr> Parser::comparison(){
    auto expr = addition();
    while(match(GREATER, LESS, GREATER_EQUAL, LESS_EQUAL)){
        Token operation = previous();
        auto right = addition();
        expr = std::unique_ptr<Expr>(
            new Expr(operation, std::move(expr), std::move(right))); 
    }
    return expr;
}
std::unique_ptr<Expr> Parser::addition(){
    auto expr = multiplication();
    while(match(PLUS, MINUS)){
        Token operation = previous();
        auto right = multiplication();
        expr = std::unique_ptr<Expr>(
            new Expr(operation, std::move(expr), std::move(right)));
    }
    return expr;
}
std::unique_ptr<Expr> Parser::multiplication(){
    auto expr = unary();
    while(match(STAR, SLASH)){
        Token operation = previous();
        auto right = unary();
        expr = std::unique_ptr<Expr>(
            new Expr(operation, std::move(expr), std::move(right)));
    }
    return expr; 
}    
std::unique_ptr<Expr> Parser::unary(){
    if(match(MINUS, NOT)){
        Token operation = previous();
        if(operation.type == MINUS) 
            operation.type = NEGATE;
        return std::unique_ptr<Expr>(
		new Expr(operation, std::move(unary()) ));
    }
    return primary();
}
std::unique_ptr<Expr> Parser::primary(){

    if(match(TRUE) || match(FALSE) || match(NUMBER) || match(IDENTIFIER)){
        return std::unique_ptr<Expr>(new Expr(previous()));
    }
    
    if(match(LEFT_PAREN)){
        Token paren = previous();	
        auto expr = std::unique_ptr<Expr>(
            new Expr(Token(paren.line, GROUPING, "group"), 
                     std::move(expression())));
        consume(RIGHT_PAREN, "Expected ')'");
        return expr;
    }

    throw ParseError(peek(), "Expected expression"); 
}


//used in panic error mode    
void Parser::synchronize(){
    advance();

    while(!atEnd()){
        if(previous().type == SEMICOLON) return;
        
        //TODO: add keywords we could sync on

        advance();
    }
}


