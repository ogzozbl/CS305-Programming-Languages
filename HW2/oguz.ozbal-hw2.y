%{
#include <stdio.h>

void yyerror( const char * s)
{
    return; /* basically returning nothing */
}

int yylex(); /* flex tanımlıyor */
%}



%token tPLUS tMINUS tMUL tEXP
%token tLPR tRPR tASSIGN tCOMMA tSEMICOLON
%token tCALCULATE tDERIVATION tINTEGRATION
%token tIDENTIFIER tINTEGER


%left tPLUS tMINUS
%left tMUL
%right tEXP


%%


program
  : def_block calc_block
  ;

def_block
  : 
  | def_block function_def
  ;

function_def
  : tIDENTIFIER tLPR opt_var_list tRPR tASSIGN o_expr tSEMICOLON
  ;

opt_var_list
  : 
  | var_list
  ;

var_list
  : tIDENTIFIER
  | var_list tCOMMA tIDENTIFIER
  ;

calc_block
  : 
  | calc_block calc_stmt
  ;

calc_stmt
  : tCALCULATE e_expr tSEMICOLON
  ;

o_expr
  : o_expr tPLUS o_term
  | o_expr tMINUS o_term
  | o_term
  ;

o_term
  : o_term tMUL o_factor
  | o_term o_factor
  | o_factor
  ;

o_factor
  : tINTEGER
  | tIDENTIFIER
  | tINTEGER tEXP tINTEGER
  | tIDENTIFIER tEXP tINTEGER
  | tLPR o_expr tRPR
  ;

e_expr
  : e_expr tPLUS e_term
  | e_expr tMINUS e_term
  | e_term
  ;

e_term
  : e_term tMUL e_factor
  | e_term e_factor
  | e_factor
  ;

e_factor
  : tINTEGER
  | tIDENTIFIER
  | tINTEGER tEXP tINTEGER
  | tIDENTIFIER tEXP tINTEGER
  | tLPR e_expr tRPR
  | tLPR e_expr tCOMMA e_list_tail tRPR   /* yalnızca virgül varsa geçerli */
  | tLPR tRPR                             /* boş liste () */
  | tINTEGRATION tLPR tIDENTIFIER tCOMMA tIDENTIFIER tCOMMA tINTEGER tRPR
  | tDERIVATION   tLPR tIDENTIFIER tCOMMA tIDENTIFIER tCOMMA tINTEGER tRPR
  | tIDENTIFIER tLPR opt_e_args tRPR
  ;

e_list_tail
  : e_expr
  | e_list_tail tCOMMA e_expr
  ;

opt_e_args
  : /* empty */
  | e_arg_list
  ;

e_arg_list
  : e_expr
  | e_arg_list tCOMMA e_expr
  ;

%%

int main(void)
{
  if (yyparse())
    printf("ERROR\n");
  else
    printf("OK\n");
  return 0;
}