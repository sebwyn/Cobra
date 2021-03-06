#include "Cobra.h"

#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Object.h"

#include <fstream>

int main(int argc, char** argv){
    
    /*
    if(argc > 1){
        std::string line, text;
        std::ifstream myfile (argv[1]);
        if (myfile.is_open()){
            while (getline(myfile,line)){
                std::cout << line << '\n';
                text += line + std::string(1, '\n');
            }
            myfile.close();
        }
        else std::cout << "Unable to open file" << std::endl; 
        
	    std::cout << "Tokens: " << std::endl;
        Lexer lexer(text);
        for(Token token : lexer.getTokens()){
            std::cout << type_to_string(token.type) << " " << token.text << std::endl;
        }
	    std::cout << "Abstract Syntax Tree: " << std::endl;
	    Parser parser(lexer.getTokens());
	
	    Interpreter interpreter;
	    std::cout << interpreter.interpret(parser.parse()) << std::endl;
    }*/
    std::map<std::string, Object> base;
    Interpreter interpreter;
    while(true){
        std::string input;
    
        std::cout << "Cobra#";
        getline(std::cin, input);

        Lexer lexer(input);
        //std::cout << "Tokens: " << std::endl;
        /*for(Token token : lexer.getTokens()){
            std::cout << type_to_string(token.type) 
                      << " " << token.text << std::endl;
        }*/
        //std::cout << "Abstract Syntax Tree: " << std::endl;
        Parser parser(lexer.getTokens());

	    interpreter.interpret(parser.parse(), &base);
        //std::cout << interpreter.interpret(parser.parse()) << std::endl;
    }
    return 0;
}
