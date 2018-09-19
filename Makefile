run: src/lex.yy.c src/parser.tab.c
	gcc src/lex.yy.c src/parser.tab.c -o sloth
src/parser.tab.c: src/parser.y
	bison -d -o src/parser.tab.c src/parser.y
src/lex.yy.c: src/lexer.l
	flex -o src/lex.yy.c src/lexer.l
clean:
	rm src/lex.yy.c src/parser.tab.c src/parser.tab.h sloth
