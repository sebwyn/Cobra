#include "Interpreter.h"


std::string Interpreter::interpret(const std::unique_ptr<Expr>& e){
    try {
        std::string out = "Interpreter finished with value: " 
			+ eval(e)->string();
        return out;
    } catch(RuntimeException& e) {
        std::cout << "Interpreter failed!" << std::endl;
        return e.getMessage();
    }
}


std::shared_ptr<Object> Interpreter::eval(const std::unique_ptr<Expr>& e){
    //std::cout << "found " << e->operands.size()  << " operands" << std::endl;
    switch(e->root.type){
        //handle literals
        case NUMBER:
        case TRUE:
        case FALSE:
            //ensure they dont have operands
            if(e->operands.size() > 0) 
                throw RuntimeException(e, "Somehow a literal has operands!");
            return e->root.value;
        case GROUPING:
            if(e->operands.size() != 1)
                throw RuntimeException(e, 
                      "Somehow grouping doesn't have an operand!");
            return eval(e->operands[0]);
        case PLUS: {
            float left, right;
    	    evalBinary<FloatObject>(e, &left, &right);
            return std::make_shared<FloatObject>(left + right);   
        }
        case MINUS: {
            float left, right;
            evalBinary<FloatObject>(e, &left, &right);
            return std::make_shared<FloatObject>(left - right);
        }
        case STAR: {
            float left, right;
            evalBinary<FloatObject>(e, &left, &right);
            return std::make_shared<FloatObject>(left * right);
        }
        case SLASH: {
            float left, right;
            evalBinary<FloatObject>(e, &left, &right);
            return std::make_shared<FloatObject>(left / right);
        }
        
    }
}
