#pragma once

#include "Cobra.h"
#include "AST.h"

class Function {
public:
    
    Function(std::shared_ptr<Code> body){

    }

    Object call();  
private:
    std::map<std::string, Object> environ;
};
