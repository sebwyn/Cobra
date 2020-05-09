#include "Lexer.h"
#include "Parser.h"

#include <iostream>
#include <fstream>

int main(int argc, char** argv){
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
        else std::cout << "Unable to open file"; 
        
        Lexer lexer(text);
        for(Token token : lexer.getTokens()){
            std::cout << token.to_string() << std::endl;
        }

        Parser parser(lexer.getTokens());
    }
    return 0;
}
