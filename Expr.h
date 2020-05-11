#pragma once

#include "Token.h"

class Expr {
public:
    Expr(Token root)
     : root(root) {
        //std::cout << "Made expression " << this << std::endl;
    }

    template<typename... Args>
    Expr(Token root, Args... args)
     : root(root) {
        addArgs(std::forward<std::unique_ptr<Expr>>(args)...);
    	//std::cout << "Made expression " << this << " with root '"
	//	  << root.text << "' and " << operands.size() << " operands"
	//	  << std::endl; 
    }

    ~Expr(){
        //std::cout << "deleting: " << this << std::endl;
    }

    Token root;
    std::vector<std::unique_ptr<Expr>> operands;
private:
    void addArgs(std::unique_ptr<Expr> arg){
        operands.push_back(std::forward<std::unique_ptr<Expr>>(arg));
    }

    template<typename... Args>
    void addArgs(std::unique_ptr<Expr> first, Args... rest){
        addArgs(std::forward<std::unique_ptr<Expr>>(first));
        addArgs(std::forward<std::unique_ptr<Expr>>(rest)...);
    }
};
