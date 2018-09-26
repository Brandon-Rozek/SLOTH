GPP = g++ -Wall -std=c++17

sloth: src/main.c src/parser/lex.yy.o src/parser/parser.tab.o src/variables/environment.o src/variables/variable.o src/variables/value.o src/operations/node.o src/operations/operators.o src/string.o src/shell.o
	$(GPP) src/main.c src/parser/lex.yy.o src/parser/parser.tab.o src/variables/environment.o src/variables/variable.o src/variables/value.o src/operations/node.o src/operations/operators.o src/string.o src/shell.o -ledit -o sloth
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
src/variables/environment.o: src/variables/environment.h src/variables/environment.c
	$(GPP) -c src/variables/environment.c -o src/variables/environment.o
src/variables/variable.o: src/variables/variable.h src/variables/variable.c
	$(GPP) -c src/variables/variable.c -o src/variables/variable.o
src/variables/value.o: src/variables/value.h src/variables/value.h
	$(GPP) -c src/variables/value.c -o src/variables/value.o
src/operations/operators.o: src/operations/operators.h  src/operations/operators.c
	$(GPP) -c src/operations/operators.c -o src/operations/operators.o
src/operations/node.o: src/operations/node.h src/operations/node.c
	$(GPP) -c src/operations/node.c -o src/operations/node.o
src/shell.o: src/shell.h src/shell.c
	$(GPP) -c src/shell.c -o src/shell.o
src/string.o: src/string.h src/string.c
	$(GPP) -c src/string.c -o src/string.o
clean:
	rm src/parser/lex.yy.c src/parser/parser.tab.c src/parser/parser.tab.h src/parser/lex.yy.o src/parser/parser.tab.o src/variables/environment.o src/variables/variable.o src/variables/value.o src/operations/node.o src/operations/operators.o src/string.o src/shell.o sloth
