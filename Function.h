#pragma once

#include "Cobra.h"
#include "Token.h"

#include "AST.h"

struct Code {
    std::vector<Stmt*> body;

    Code(const std::vector<Stmt*>& _body)
    : body(_body) {}

    ~Code(){
        for(Stmt* stmt : body){
            delete stmt;
        }
    }
    
};	

class Stmt;

struct Function {
public:
    Function(){}

    Function(const std::vector<Token>& _params,const std::vector<Stmt*>& _body){
	    params = std::make_shared<std::vector<Token>>(_params);
        body = std::make_shared<Code>(_body); 
        //std::cout << "Making new function: params = " << params << " body = " << body << std::endl;
    }

    ~Function(){
        //std::cout << this << ": deleting params " << params << " " << params.use_count() << " body " << body << " " << body.use_count() << std::endl;
    }    

    //shared amongst all functions with the same declaration
    std::shared_ptr<std::vector<Token>> params;
    std::shared_ptr<Code> body;
    
    std::map<std::string, Object> environ;
};

