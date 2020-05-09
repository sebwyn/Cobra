#include "Lexer.h"

#include <iostream>

std::string type_to_string(TokenType t){
    switch(t){    
        case(LEFT_PAREN): { return std::string("LEFT_PAREN"); } break;
        case(RIGHT_PAREN): { return std::string("RIGHT_PAREN"); } break;
        case(COMMA): { return std::string("COMMA"); } break;
        case(SEMICOLON): { return std::string("SEMICOLON"); } break;

        case(ASSIGN): { return std::string("ASSIGN"); } break;
        
        case(EQUAL): { return std::string("EQUAL"); } break;
        case(NOT_EQUAL): { return std::string("NOT_EQUAL"); } break;
        case(GREATER_THAN): { return std::string("GREATER_THAN"); } break;
        case(LESS_THAN): { return std::string("LESS_THAN"); } break;
        case(GREATER_THAN_EQUAL): { return std::string("GREATER_THAN_EQUAL"); } break;
        case(LESS_THAN_EQUAL): { return std::string("LESS_THAN_EQUAL"); } break;

        case(NOT): { return std::string("NOT"); } break;
        case(AND): { return std::string("AND"); } break;
        case(OR): { return std::string("OR"); } break;

        case(ADD): { return std::string("ADD"); } break;
        case(SUBTRACT): { return std::string("SUBTRACT"); } break;
        case(MULTIPLY): { return std::string("MULTIPLY"); } break;
        case(DIVIDE): { return std::string("DIVIDE"); } break;

        case(IDENTIFIER): { return std::string("IDENTIFIER"); } break;
        case(FLOAT): { return std::string("FLOAT"); } break;
        
        case(END): { return std::string("END"); } break;
     }
}

Lexer::Lexer(const std::string& text)
 : text(text) {
    lex(); 
}

void Lexer::lex(){
    while(!atEnd()){
        start = current;
        getToken();
    }
}

void Lexer::emitError(const std::string& message){
    std::cout << "Lexer error on line " << line << ": " << message << std::endl; 
}

void Lexer::getToken(){
    char c = advance();
    switch(c){
        case('('): addToken(LEFT_PAREN); break;
        case(')'): addToken(RIGHT_PAREN); break;
        case(','): addToken(COMMA); break;
        case(';'): addToken(SEMICOLON); break;
        
        case('+'): addToken(ADD); break;
        case('-'): addToken(SUBTRACT); break;
        case('*'): addToken(MULTIPLY); break;
        case('/'): match('/') ? getLineComment() : addToken(DIVIDE); break;
        
        case('='): match('>') ? addToken(ASSIGN) : addToken(EQUAL); break;
        
        case('!'): match('=') ? addToken(NOT_EQUAL) : addToken(NOT); break;
        case('>'): match('=') 
                   ? addToken(GREATER_THAN_EQUAL) : addToken(GREATER_THAN); break;
        case('<'): match('=') 
                   ? addToken(LESS_THAN_EQUAL) : addToken(LESS_THAN); break;
    
        case('&'): addToken(AND); break;
        case('|'): addToken(OR); break;
        
        case('\0'): addToken(END); break;

        //handle whitespace
        case(' '):
        case('\t'):
            break;
        case('\n'): line++; break;

        //needs to match identifiers and numeric literals
        default:
            if(isAlpha(c)){
                getIdentifier();
            } else if(isDigit(c)) {
                getFloat();
            } else {
                emitError("Unexpected symbol '" + std::string(1, c) + "'"); 
            } 
            break; 
    }
}

void Lexer::getLineComment(){
    while(peek() != '\n' && peek() != '\0'){
        advance();
        continue;
    }
    line++;
}

//TODO: add a hash map for keywords
void Lexer::getIdentifier(){
    while(isAlphaNumeric(peek())) advance();

    std::string id = text.substr(start, current-start);
    addToken(IDENTIFIER, id);
}

//TODO: add floating point support
void Lexer::getFloat(){
    while(isDigit(peek())) advance();

    std::string num = text.substr(start, current-start);
    addToken(FLOAT, std::stof(num));
}
