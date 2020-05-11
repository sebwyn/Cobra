#pragma once

#include "Cobra.h"

#include "Object.h"
#include "Expr.h"

class Interpreter {
private:
    class RuntimeException : public std::exception {
    public: 
        RuntimeException(const std::unique_ptr<Expr>& e, const std::string& _message){
            message = "Runtime Error on line " + std::to_string(e->root.line) +
                      " at token `" + e->root.text + "`: " + _message; 
        }

        const std::string& getMessage(){ return message; }
private:
    std::string message;
};
public:
    std::string interpret(const std::unique_ptr<Expr>& e);
private:
    
    std::shared_ptr<Object> eval(const std::unique_ptr<Expr>& e);
    
    template<typename O, typename T>
    void evalBinary(const std::unique_ptr<Expr>& e, T* left, T* right){
        if(e->operands.size() != 2)
            throw RuntimeException(e, 
                "Binary operator expects 2 operands found " 
              + std::to_string(e->operands.size()));
        auto op1 = eval(e->operands[0]);
        auto op2 = eval(e->operands[1]);
        //std::cout << "op1: " << op1.get() << " op2: " << op2.get() << std::endl; 
        auto tOp1 = std::dynamic_pointer_cast<O>(op1);
        auto tOp2 = std::dynamic_pointer_cast<O>(op2);
        if(tOp1.get() && tOp2.get()){
            *left = tOp1->get();
            *right = tOp2->get();
            return;	
        }
        std::string message = "No viable overload for operator '" 
                            + e->root.text + "' and operand types: "
                            + to_string(op1->type) + " "
                + to_string(op2->type);
        throw RuntimeException(e, message);
}
};
