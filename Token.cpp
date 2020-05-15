#include "Token.h"

std::string type_to_string(TokenType t){
    switch(t){    
        case(LEFT_PAREN): { return std::string("LEFT_PAREN"); } break;
        case(RIGHT_PAREN): { return std::string("RIGHT_PAREN"); } break;
	    case(LEFT_BRACE): { return "LEFT_BRACE"; } break;
        case(RIGHT_BRACE): { return "RIGHT_BRACE"; } break;
        case(COMMA): { return std::string("COMMA"); } break;
        case(SEMICOLON): { return std::string("SEMICOLON"); } break;

        case(ASSIGN): { return std::string("ASSIGN"); } break;
        
        case(EQUAL): { return std::string("EQUAL"); } break;
        case(NOT_EQUAL): { return std::string("NOT_EQUAL"); } break;
        case(GREATER): { return std::string("GREATER"); } break;
        case(LESS): { return std::string("LESS"); } break;
        case(GREATER_EQUAL): { return std::string("GREATER_EQUAL"); } break;
        case(LESS_EQUAL): { return std::string("LESS_EQUAL"); } break;

        case(NOT): { return std::string("NOT"); } break;
        case(AND): { return std::string("AND"); } break;
        case(OR): { return std::string("OR"); } break;

        case(PLUS): { return std::string("PLUS "); } break;
        case(MINUS): { return std::string("MINUS"); } break;
        case(STAR): { return std::string("STAR"); } break;
        case(SLASH): { return std::string("SLASH"); } break;

        case(IDENTIFIER): { return std::string("IDENTIFIER"); } break;
        case(NUMBER): { return std::string("NUMBER"); } break;
        
        case(END): { return std::string("END"); } break;
        
        case(TRUE): { return std::string("TRUE"); } break;
        case(FALSE): { return std::string("FALSE"); } break;
        case(PRINT): { return std::string("PRINT"); } break;     
	    case(WHILE): { return std::string("WHILE"); } break;
	}
}

