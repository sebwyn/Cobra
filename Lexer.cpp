#include "Lexer.h"

#include <iostream>

bool Lexer::first = true;
std::map<std::string, TokenType> Lexer::keywords;

void Lexer::initLex(){
    keywords["true"] = TRUE;
    keywords["false"] = FALSE;
    keywords["print"] = PRINT;        
}

Lexer::Lexer(const std::string& text)
 : text(text) {
    if(first){
        first = false;
        initLex();
    }
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
        
        case('+'): addToken(PLUS); break;
        case('-'): addToken(MINUS); break;
        case('*'): addToken(STAR); break;
        case('/'): match('/') ? getLineComment() : addToken(SLASH); break;
        
	case(':'): 
		if(match('=')) addToken(ASSIGN); 
		else emitError("Unexpected symbol '"+std::string(1, c) +"'"); 
		break;
        case('='): addToken(EQUAL); break;
        
        case('!'): match('=') ? addToken(NOT_EQUAL) : addToken(NOT); break;
        case('>'): match('=') 
                   ? addToken(GREATER_EQUAL) : addToken(GREATER); break;
        case('<'): match('=') 
                   ? addToken(LESS_EQUAL) : addToken(LESS); break;
    
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

void Lexer::getIdentifier(){
    while(isAlphaNumeric(peek())) advance();
    
    std::string str = text.substr(start, current-start);
    TokenType nameType;
    try {
        nameType = keywords.at(str);
    } catch(std::out_of_range& e) {
        nameType = IDENTIFIER;
    }
    
    addToken(nameType);
}

//TODO: add floating point support
void Lexer::getFloat(){
    while(isDigit(peek())) advance();
    addToken(NUMBER);
}
