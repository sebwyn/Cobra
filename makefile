all:
	g++ -g -o Cobra -std=c++11 main.cpp Token.cpp Object.cpp AST.cpp Lexer.cpp Parser.cpp Interpreter.cpp 
