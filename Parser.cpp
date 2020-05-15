#include "Parser.h"

#include <iostream>

Stmt* Parser::statement(){
    if(match(PRINT)){
	    //std::cout << "Found print statement" << std::endl;
        Expr* e = expression();
        consume(SEMICOLON, "Expected ;");
        return new Stmt::PrintStmt(e);
    }
    //dont have any other statements right now 
    Expr* e = expression();
    consume(SEMICOLON, "Expected ';'");
    return new Stmt::ExprStmt(e);
}

//functions for consuming grammar
Expr* Parser::expression(){
    return assignment();
}

Expr* Parser::assignment(){
    auto e = logicalAnd();
    if(match(ASSIGN)){
        Token operation = previous();
        auto right = assignment();
        return new Expr::Assignment(operation, e->root, right); 
    }
    return e;
}

Expr* Parser::logicalAnd(){
    auto expr = logicalOr();
    while(match(AND)){
        Token operation = previous();
        auto right = logicalOr();
       	expr = new Expr::Binary(operation, expr, right);
    }
    return expr;
}

Expr* Parser::logicalOr(){
    auto expr = equality();
    while(match(OR)){
        Token operation = previous();
        auto right = equality();
        expr = new Expr::Binary(operation, expr, right);
    }
    return expr;
}

Expr* Parser::equality() {
    auto expr = comparison();
    while(match(EQUAL, NOT_EQUAL)){
        Token operation = previous();
        auto right = comparison();
        expr = new Expr::Binary(operation, expr, right);
    }
    return expr;
}
Expr* Parser::comparison(){
    auto expr = addition();
    while(match(GREATER, LESS, GREATER_EQUAL, LESS_EQUAL)){
        Token operation = previous();
        auto right = addition();
        expr = new Expr::Binary(operation, expr, right); 
    }
    return expr;
}
Expr* Parser::addition(){
    auto expr = multiplication();
    while(match(PLUS, MINUS)){
        Token operation = previous();
        auto right = multiplication();
        expr = new Expr::Binary(operation, expr, right);
    }
    return expr;
}
Expr* Parser::multiplication(){
    auto expr = unary();
    while(match(STAR, SLASH)){
        Token operation = previous();
        auto right = unary();
        expr = new Expr::Binary(operation, expr, right);
    }
    return expr; 
}    
Expr* Parser::unary(){
    if(match(MINUS, NOT)){
        Token operation = previous();
        return new Expr::Unary(operation, unary());
    }
    return primary();
}
Expr* Parser::primary(){

    if(match(TRUE) || match(FALSE) || match(NUMBER) || match(IDENTIFIER)){
        return new Expr::Primary(previous());
    }
    
    if(match(LEFT_PAREN)){
        Token paren = previous();	
        auto expr = new Expr::Unary(
		Token(paren.line, GROUPING, "group"), expression());
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


