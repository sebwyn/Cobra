#pragma once

#include "Cobra.h"

#include "Object.h"
#include "Token.h"

class Expr {
public:
    class Assignment;
    class Binary;
    class Unary;
    class Primary;

    class Visitor {
    public:
        virtual Object visitAssignment(Assignment* assignment){}
        virtual Object visitBinary(Binary* binary){}
        virtual Object visitUnary(Unary* unary){}
        virtual Object visitPrimary(Primary* primary){}
    };
    
    Token root;

    Expr(Token root)
     : root(root) {}
    
    virtual ~Expr(){}
	
    virtual Object accept(Visitor* visitor){} 
    
};

class Expr::Assignment : public Expr {
public:
    Token left;
    Expr* right;

    Assignment(Token root, Token left, Expr* right)
     : Expr(root), left(left), right(right) {}
    
    virtual Object accept(Visitor* visitor) override {
        return visitor->visitAssignment(this);
    }
	
    virtual ~Assignment() override {
        delete right;
    }
};

class Expr::Binary : public Expr {
public:
    Expr *left, *right;
    
    Binary(Token root, Expr* left, Expr* right) 
     : Expr(root), left(left), right(right) {}

    virtual Object accept(Visitor* visitor) override {
        return visitor->visitBinary(this);
    }

    virtual ~Binary() override {
        delete left;
        delete right;
    }  
};

class Expr::Unary : public Expr {
public:
    Expr *right;
    
    Unary(Token root, Expr* right)
     : Expr(root), right(right) {}

    virtual Object accept(Visitor* visitor) override {
        return visitor->visitUnary(this);
    }

    virtual ~Unary() override {
        delete right;
    }
};

class Expr::Primary : public Expr {
public:
    Primary(Token root)
     : Expr(root) {}        

    virtual Object accept(Visitor* visitor) override {
        return visitor->visitPrimary(this); 
    }

    virtual ~Primary() override {} 
};

class Stmt {
public:
    class ExprStmt;
    class PrintStmt;    
    class WhileStmt;    
	
    class Visitor {
    public:
        virtual void visitExprStmt(ExprStmt* stmt){}
        virtual void visitPrintStmt(PrintStmt* stmt){}    
	    virtual void visitWhileStmt(WhileStmt* stmt){}
    };
    
    virtual ~Stmt() {}

    virtual void accept(Visitor* visitor){};    

};


class Stmt::ExprStmt : public Stmt {
public:
    ExprStmt(Expr* e) 
    : e(e) {} 

    Expr* e;
    
    virtual ~ExprStmt() override {
        delete e;
	}

    virtual void accept(Visitor* visitor) override {
        visitor->visitExprStmt(this); 
    }
};

class Stmt::PrintStmt : public Stmt {
public:    
    PrintStmt(Expr* e)
    : e(e) {}
    
    Expr* e;

    virtual ~PrintStmt() override {
        delete e;
    }

    virtual void accept(Visitor* visitor) override {
        visitor->visitPrintStmt(this);
    }
};

class Stmt::WhileStmt : public Stmt {
public: 
    WhileStmt(Expr* cond, std::vector<Stmt*> _body)
    : cond(cond), body(_body) {}
     
    Expr* cond;
    std::vector<Stmt*> body;

    virtual ~WhileStmt() override {
        delete cond;
        for(auto stmt : body){
            delete stmt;
        }
    }

    virtual void accept(Visitor* visitor) override {
        visitor->visitWhileStmt(this);
    }
};
