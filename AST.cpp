#include "AST.h"

#include "Function.h"

Stmt::FuncStmt::FuncStmt(Token name, std::vector<Token> params, std::vector<Stmt*> body)
: name(name), func(Function(params, body)) {}
