#pragma once

#include "Cobra.h"

#include "Object.h"
#include "AST.h"

#include "Function.h"

class Interpreter : public Expr::Visitor, public Stmt::Visitor {
private:
    class RuntimeException;

    std::vector<std::map<std::string, Object>*> environments;
public:
    void interpret(const std::vector<Stmt*>& statements, std::map<std::string, Object>* environ){
	for(auto stmt : statements){
            try {
                environments.push_back(environ);
                std::cout << "Begun executing" << std::endl;
                execute(stmt);
	            std::cout << "Done executing" << std::endl;	
                environments.pop_back();
            } catch(RuntimeException& e){
                std::cout << e.message << std::endl;
            }
        }
    }

    virtual void visitExprStmt(Stmt::ExprStmt* stmt) override {
        std::cout << "Visiting ExprStmt" << std::endl;
        Object o;
	    o = eval(stmt->e);
        std::cout << "Done evaling ExprStmt" << std::endl;  
	}
    
    virtual void visitPrintStmt(Stmt::PrintStmt* stmt) override {
        std::cout << eval(stmt->e).string() << std::endl; 
    }

    virtual void visitFuncStmt(Stmt::FuncStmt* stmt) override {
        (*(environments.back()))[stmt->name.text] = stmt->func;
    }

    virtual void visitWhileStmt(Stmt::WhileStmt* stmt) override {
        while(true){
            bool b;
            Object cond = eval(stmt->cond);
            if(!cond.get(b))
                throw RuntimeException(stmt->cond->root,
                    "Expected BOOL expression");
            if(!b) return;
            interpret(stmt->body, environments.back());
        }
    }
    
    //the parser ensures that the left hand side token is an identifier
    virtual Object visitAssignment(Expr::Assignment* assignment) override {
        Object right = eval(assignment->right);
        
        (*(environments.back()))[assignment->left.text] = right; 
        
        return right;
    }

    virtual Object visitBinary(Expr::Binary* binary) override {
        Object left = eval(binary->left);
        Object right = eval(binary->right);
	
        //std::cout << "Left is at " << left.value << 
		//     " right is at " << right.value << std::endl; 
        switch(binary->root.type){
            case PLUS: {
                float l, r;
                if(!left.get(l))
                    throw RuntimeException(binary->left->root,"Expected float");
                if(!right.get(r))
                    throw RuntimeException(binary->right->root,"Expected float");
                return l+r;
            }
            case MINUS: {
                float l, r;
                if(!left.get(l))
                    throw RuntimeException(binary->left->root,"Expected float");
                if(!right.get(r))
                    throw RuntimeException(binary->right->root,"Expected float");
                return l-r;
            }
            case STAR: {
                float l, r;
                if(!left.get(l))
                    throw RuntimeException(binary->left->root,"Expected float");
                if(!right.get(r))
                    throw RuntimeException(binary->right->root,"Expected float");
                return l*r;
            }
            case SLASH: {
                float l, r;
                if(!left.get(l))
                    throw RuntimeException(binary->left->root,"Expected float");
                if(!right.get(r))
                    throw RuntimeException(binary->right->root,"Expected float");
                return l/r;
            }
            case EQUAL: {
                bool bl, br;
                float fl, fr;
                if(!left.compareType(right)){
                    return false;
                } else if(left.get(bl) && right.get(br)){
                    return bl == br;
                } else if(left.get(fl) && right.get(fr)){
                    return fl == fr;
                } else throw(binary->root, "Broken implementation!");
            }
            case NOT_EQUAL: {
                bool bl, br;
                float fl, fr;
                if(!left.compareType(right)){
                    return true;
                } else if(left.get(bl) && right.get(br)){
                    return bl != br;
                } else if(left.get(fl) && right.get(fr)){
                    return fl != fr;
                } else throw(binary->root, "Broken implementation");
            }
            case GREATER: {
                float l, r;
                if(!left.get(l))
                    throw RuntimeException(binary->left->root,"Expected float");
                if(!right.get(r))
                    throw RuntimeException(binary->right->root,"Expected float");
                return l>r;
            }
            case LESS: {
                float l, r;
                if(!left.get(l))
                    throw RuntimeException(binary->left->root,"Expected float");
                if(!right.get(r))
                    throw RuntimeException(binary->right->root,"Expected float");
                return l<r;
            }
            case GREATER_EQUAL: {
                float l, r;
                if(!left.get(l))
                    throw RuntimeException(binary->left->root,"Expected float");
                if(!right.get(r))
                    throw RuntimeException(binary->right->root,"Expected float");
                return l>=r;
            }
            case LESS_EQUAL: {
                float l, r;
                if(!left.get(l))
                    throw RuntimeException(binary->left->root,"Expected float");
                if(!right.get(r))
                    throw RuntimeException(binary->right->root,"Expected float");
                return l<=r;
            }
        	default:
                throw RuntimeException(binary->root,"Unimplemented operation");
        }
    }

    virtual Object visitUnary(Expr::Unary* unary) override {
        Object right = eval(unary->right);
        
        switch(unary->root.type){
            case MINUS: {
                float r;
                if(!right.get(r))
                    throw RuntimeException(unary->right->root,"Expected float");
                return -r; 
            }
            case NOT: {
                bool r;
                if(!right.get(r))
                    throw RuntimeException(unary->right->root,"Expected bool");
                return !r;
            }
            case GROUPING: {
                return right;
            }
            default: {
		        throw RuntimeException(unary->root,"Unimplemented operation");
            }
        }
    }
    
    virtual Object visitFunction(Expr::Function* function) override {
        Function f;
        Object func = eval(function->e);
        if(!func.get(f))
            throw RuntimeException(function->e->root,"Expected function Expr"); 
        //bind args to param names
        int argNum = 0;
        for(auto arg : function->args){
            if(argNum >= f.params->size())
                throw RuntimeException(function->root, "Too many args given to function");
            f.environ[(*f.params)[argNum].text] = eval(arg);
            argNum++;
        }
        if(argNum < f.params->size())
            throw RuntimeException(function->root, "Too few args passed to function");
        std::cout << "Interpreting with environment " << &f.environ<<std::endl;
        std::cout << "Interpreting body " << f.body<<std::endl;
        interpret(f.body->body, &(f.environ));
        std::cout << "Done interpreting function call" << std::endl; 
   	}

    virtual Object visitPrimary(Expr::Primary* primary) override {
        switch(primary->root.type){
            case IDENTIFIER:
                try {
                    return environments.back()->at(primary->root.text); 
                } catch(std::out_of_range& e) {
                    throw RuntimeException(primary->root, "Undefined symbol");
                }
            default:
                return primary->root.value;
        }
    }
private:

    class RuntimeException : std::exception {
    public:
        RuntimeException(const Token& t, std::string _message){
            message = "Runtime Error on line " + std::to_string(t.line) +
                      " at token '" + t.text + "': " + _message; 
        }

        std::string message;
    };

    //execute statements
    void execute(Stmt* s){
    	s->accept(this);
    }
    
    //evaluate expressions
    Object eval(Expr* e){
        //std::cout << "evaling " << e->root.text << std::endl;
        Object o = e->accept(this);
        std::cout << "Done evaling" << std::endl;
	    //std::cout << "Done evaling with " << o.string() << std::endl; 
        return o;
    }
};
