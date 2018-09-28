GPP = g++ -Wall -std=c++17 -O3 

sloth: src/main.cpp src/parser/lex.yy.o src/parser/parser.tab.o src/variables/environment.o src/variables/variable.o src/variables/value.o src/operations/node.o src/operations/operators.o src/string.o src/shell.o
	$(GPP) src/main.cpp src/parser/lex.yy.o src/parser/parser.tab.o src/variables/environment.o src/variables/variable.o src/variables/value.o src/operations/node.o src/operations/operators.o src/string.o src/shell.o -ledit -o sloth
src/parser/lex.yy.o: src/parser/lex.yy.c src/parser/parser.tab.h 
	$(GPP) -c src/parser/lex.yy.c -o src/parser/lex.yy.o
src/parser/parser.tab.o: src/parser/parser.tab.c
	$(GPP) -c src/parser/parser.tab.c -o src/parser/parser.tab.o
src/parser/parser.tab.h: src/parser/parser.y
	bison -d -o src/parser/parser.tab.c src/parser/parser.y
src/parser/parser.tab.c: src/parser/parser.y
	bison -d -o src/parser/parser.tab.c src/parser/parser.y
src/parser/lex.yy.c: src/parser/lexer.l
	flex -o src/parser/lex.yy.c src/parser/lexer.l
src/variables/environment.o: src/variables/environment.hpp src/variables/environment.cpp
	$(GPP) -c src/variables/environment.cpp -o src/variables/environment.o
src/variables/variable.o: src/variables/variable.hpp src/variables/variable.cpp
	$(GPP) -c src/variables/variable.cpp -o src/variables/variable.o
src/variables/value.o: src/variables/value.hpp src/variables/value.cpp
	$(GPP) -c src/variables/value.cpp -o src/variables/value.o
src/operations/operators.o: src/operations/operators.hpp  src/operations/operators.cpp
	$(GPP) -c src/operations/operators.cpp -o src/operations/operators.o
src/operations/node.o: src/operations/node.hpp src/operations/node.cpp
	$(GPP) -c src/operations/node.cpp -o src/operations/node.o
src/shell.o: src/shell.hpp src/shell.cpp
	$(GPP) -c src/shell.cpp -o src/shell.o
src/string.o: src/string.h src/string.c
	$(GPP) -c src/string.c -o src/string.o
clean:
	rm src/parser/lex.yy.c src/parser/parser.tab.c src/parser/parser.tab.h src/parser/lex.yy.o src/parser/parser.tab.o src/variables/environment.o src/variables/variable.o src/variables/value.o src/operations/node.o src/operations/operators.o src/string.o src/shell.o sloth
