## 
## Simple makefile for CS 406 assignments
##

.PHONY: clean strip

# Set the default target. When you make with no arguments,
# this will be the target built.
COMPILER = dcc
PRODUCTS = $(COMPILER) 
default: $(PRODUCTS)

# Set up the list of source and object files
SRCS = ast.cc ast_decl.cc ast_expr.cc ast_stmt.cc ast_type.cc errors.cc utility.cc main.cc

# OBJS can deal with either .cc or .c files listed in SRCS
OBJS = y.tab.o lex.yy.o $(patsubst %.cc, %.o, $(filter %.cc,$(SRCS))) $(patsubst %.c, %.o, $(filter %.c, $(SRCS)))

JUNK =  *.o lex.yy.c dpp.yy.c y.tab.c y.tab.h *.core core *~

# Define the tools we are going to use
CC= g++
LD = g++
LEX = flex
YACC = bison

# Set up the necessary flags for the tools

# We want debugging and most warnings, but lex/yacc generate some
# static symbols we don't use, so turn off unused warnings to avoid clutter
# Also STL has some signed/unsigned comparisons we want to suppress
CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare

# The -d flag tells lex to set up for debugging. Can turn on/off by
# setting value of global yy_flex_debug inside the scanner itself
LEXFLAGS = -d

# The -d flag tells yacc to generate header with token types
# The -v flag writes out a verbose description of the states and conflicts
# The -t flag turns on debugging capability
# The -y flag means imitate yacc's output file naming conventions
YACCFLAGS = -dvty

# Link with standard C library, math library, and lex library
LIBS = -lc -lm -lfl

# Rules for various parts of the target

.yy.o: $*.yy.c
	$(CC) $(CFLAGS) -c -o $@ $*.cc

lex.yy.c: scanner.l  parser.y y.tab.h 
	$(LEX) $(LEXFLAGS) scanner.l

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c -o y.tab.o y.tab.c

y.tab.h y.tab.c: parser.y
	$(YACC) $(YACCFLAGS) parser.y
.cc.o: $*.cc
	$(CC) $(CFLAGS) -c -o $@ $*.cc

# rules to build compiler (dcc)

$(COMPILER) :  $(OBJS)
	$(LD) -o $@ $(OBJS) $(LIBS)


# This target is to build small for testing (no debugging info), removes
# all intermediate products, too
strip : $(PRODUCTS)
	strip $(PRODUCTS)
	rm -rf $(JUNK)


# make depend will set up the header file dependencies for the 
# assignment.  You should make depend whenever you add a new header
# file to the project or move the project between machines
#
depend:
	makedepend -- $(CFLAGS) -- $(SRCS)

clean:
	rm -f $(JUNK) y.output $(PRODUCTS)

# DO NOT DELETE

ast.o: ast.h  
ast.o:  location.h ast_type.h list.h utility.h
ast.o: ast_decl.h 
ast_decl.o: ast_decl.h ast.h  
ast_decl.o:  location.h list.h utility.h
ast_decl.o: ast_type.h ast_stmt.h
ast_expr.o:   ast_expr.h
ast_expr.o: ast.h  
ast_expr.o:   location.h
ast_expr.o: ast_stmt.h list.h utility.h 
ast_expr.o:  ast_type.h ast_decl.h
ast_stmt.o: ast_stmt.h list.h utility.h 
ast_stmt.o: ast.h location.h ast_type.h ast_decl.h ast_expr.h
ast_type.o:   ast_type.h
ast_type.o: ast.h  
ast_type.o:   location.h
ast_type.o: list.h utility.h  
ast_type.o: ast_decl.h
errors.o: errors.h location.h  
errors.o: scanner.h ast_type.h ast.h 
errors.o:   list.h
errors.o: utility.h ast_expr.h ast_stmt.h ast_decl.h
utility.o: utility.h  
main.o: utility.h  
main.o:  errors.h location.h parser.h scanner.h list.h
main.o: ast.h ast_type.h ast_decl.h ast_expr.h ast_stmt.h
