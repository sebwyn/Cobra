#pragma once

#include "Cobra.h"
#include "Token.h"

class Lexer {
public:
    Lexer(const std::string& text);
    
    void lex();

    std::vector<Token>& getTokens(){ return tokens; }
private:
    
    static void initLex();

    static bool first;
    static std::map<std::string, TokenType> keywords;
    

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
        std::string lexemeText = text.substr(start, current-start); 
	    tokens.push_back(Token(line, type, lexemeText));
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
