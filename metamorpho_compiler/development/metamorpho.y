%{
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include "stack.h"

int var_counter = 0; // Currently available variable position in activation record.
int temp_var_counter = -1; // Currently available temporary variable position in AC. 
int address_counter = 0; // Currently available address label.
int past_counter = 0; // Saves an address_counter being used, where needed.
int arg_counter = 0; // Determines number of arguments in a function call.
stack *address_stack; // Saves address_counter instances for usage at later times.
GHashTable* var_table; // Table to store variable names and associated numbers.

void yyerror(const char *str)
{
    fprintf(stderr,"error: %s\n", str);
}
 
int yywrap()
{
    return 1;
} 

//Variable table functions.

void store_var(char *input_var)
{
    if (g_hash_table_contains(var_table, input_var)) return;
    g_hash_table_insert(var_table, input_var, GINT_TO_POINTER(var_counter++));
}

int get_pos(char *input_var)
{
    return GPOINTER_TO_INT(g_hash_table_lookup(var_table, input_var));
}

void renew_environment()
{
    g_hash_table_remove_all(var_table);
    var_counter = 0;
}


//Printing functions.

void pre_op_call()
{
    printf("(StoreArgAcc %d %d)\n", temp_var_counter--, 0);
}

void op_call(char* op, int nary)
{   
    if (nary > 1) temp_var_counter++;
    printf("(StoreArgAcc %d %d)\n", temp_var_counter, nary-1);
    printf("(Call #\"%s[f%d]\" %d)\n", op, nary, temp_var_counter);
}

void make_bool(char* val)
{
    if (strcmp(val, "osatt"))
    {
        if (strcmp(val, "satt")) printf("(MakeVal null)\n");
        else printf("(MakeVal true)\n");
    }
    else printf("(MakeVal false)\n");
}

%}

%union
{
    int ival;
    double dval;
    char* sval;
}

%token IF ELSE WHILE AND OR NOT RETURN
%token STRLIT NUM BOOL NAME VAR DELIM BOOLOP OP_1 OP_2 FUNCTION WRITE
%type<sval> STRLIT NUM BOOL BOOLOP OP_1 OP_2 DELIM NAME '=' expression or_expr
%type<sval> and_expr not_expr NOT bool_val num_expr term factor func_call '('
%type<ival> get_params store_params opt_params
%left OP_2
%left OP_1

%%

/* Program */

start       :   { printf("\"out.mexe\" = megin in\n!\n{{\n"); }
                program
                { printf("}}\n*\nBASIS\n;\n"); }
            ;

program     :   program function
            |   function
            ;


/* Function */

function    :   FUNCTION NAME          { printf("#\"%s", $2); }
                '(' get_params ')' '{' { printf("[f%d]\" =\n[\n", $5); }
                body '}'               { printf("];\n"); renew_environment(); }
            ;

get_params  :   get_params ',' NAME { $$ = $1 + 1; store_var($3); }
            |   NAME                { $$ = 1; store_var($1); }
            |                       { $$ = 0;  }
            ;

body        :   body statement
            |   statement
            ;


/* Statement */

statement   :   NAME '=' expression ';' { store_var($1); printf("(Store %d)\n", get_pos($1)); }
            |   func_call ';'
            |   WRITE expression ';'    { printf("(StoreArgAcc %d 0)\n", temp_var_counter);
                                          printf("(Become #\"writeln[f1]\" %d 0)\n", temp_var_counter); }
            |   while_stm
            |   if_else_stm
            |   return_stm              { printf("(Return)\n"); }
            ;
 
while_stm   :   WHILE           { printf("_%d:\n", address_counter); 
                                  push(address_stack, address_counter++); }
                '(' or_expr ')' { printf("(GoFalse _%d)\n", address_counter);  
                                  push(address_stack, address_counter++); }
                                            
                '{' body '}'    { int temp_val = pop(address_stack);
                                  printf("(Go _%d)\n", pop(address_stack));
                                  printf("_%d:\n", temp_val); }
            ;

if_else_stm :   IF '(' expression ')' { printf("(GoFalse _%d)\n", address_counter); 
                                        push(address_stack, address_counter++); }
                '{' body '}'          { printf("(Go _%d)\n", address_counter);
                                        printf("_%d:\n", pop(address_stack)); 
                                        push(address_stack, address_counter++); }
                ELSE '{' body '}'     { printf("_%d:\n", pop(address_stack)); }
            ;

return_stm  :   RETURN ';'
            |   RETURN expression ';'
            ;


/* Function call */

func_call   :   NAME '(' opt_params ')' { printf("(Call #\"%s[f%d]\" %d)\n", $1, $3, temp_var_counter); 
                                            arg_counter = 0; }
            ;

opt_params  :   store_params    { $$ = $1; }
            |                   { $$ = 0; }

store_params:   store_params ',' expression
                { printf("(StoreArgAcc %d %d)\n", temp_var_counter, arg_counter++);
                  $$ = $1 + 1;  }
            |   expression { printf("(StoreArgAcc %d %d)\n", temp_var_counter, arg_counter++); 
                             $$ = 1; }
            ;


/* Expression */

expression  :   or_expr
            |   STRLIT   { printf("(MakeVal %s)\n", $1); }
            ;

or_expr     :   or_expr  { printf("(GoTrue _%d)\n", address_counter); 
                           push(address_stack, address_counter++);  }
                OR 
                and_expr { printf("_%d:\n", pop(address_stack)); }
            |   and_expr
            ;

and_expr    :   and_expr { printf("(GoFalse _%d)\n", address_counter); }
                AND
                not_expr { printf("_%d:\n", address_counter++); }
            |   not_expr 
            ;

not_expr    :   bool_val
            |   NOT bool_val { printf("(Not)\n"); }
            ;

bool_val    :   BOOL     { make_bool($1);  }
            |   num_expr { pre_op_call();  }
                BOOLOP 
                num_expr { op_call($3, 2); } 
            |   num_expr
            ;

num_expr    :   num_expr { pre_op_call(); }
                OP_2 
                term     { op_call($3, 2); } 
            |   term 
            ;

term        :   term     { pre_op_call(); } 
                OP_1 
                factor   { op_call($3, 2);  }
            |   factor 
            ;

factor      :   NUM                     { printf("(MakeVal %s)\n", $1); }
            |   func_call
            |   '(' expression ')'
            |   OP_2 factor  %prec OP_1 { op_call($1, 1); }
            |   NAME                    { printf("(Fetch %d)\n", get_pos($1)); }
            ;

%%

main()
{
    address_stack = (stack *) malloc(sizeof(stack));
    var_table = g_hash_table_new(g_str_hash, g_str_equal);
    yyparse();
    destroy(address_stack);
    g_hash_table_destroy(var_table);
} 
