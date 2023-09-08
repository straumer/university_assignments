all:
	flex metamorpho.l
	yacc -dv metamorpho.y
	gcc lex.yy.c y.tab.c `pkg-config --cflags --libs glib-2.0` -o metamorpho
