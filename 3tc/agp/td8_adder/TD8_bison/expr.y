/*--------------------------------------------------------
DEFINITIONS
--------------------------------------------------------*/
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "node.h"

  int yywrap(){
    return 1;
  }

  int yyerror()
  {
    printf("\n erreur !\n");
    exit(1);
  }

%}

// symbole terminaux
%token   ENTIER PLUS MOINS MULT DIV


// type de yylval
%union {
  NODE *NODE_TYPE;
  int val;
};

// type des  symboles
%type  <val> ENTIER
%type <NODE_TYPE> expression expr term factor


%%
/*--------------------------------------------------------
GRAMMAIRE ANNOTEE
--------------------------------------------------------*/

expression : expr
{
  root=$1;
}

expr : expr PLUS term
{
  $$=creerNODE(NODE_PLUS,0,$1,$3);
}
|    expr MOINS factor
{
  $$=creerNODE(NODE_MOINS,0,$1,$3);
}
|    term
{
  $$=$1;
}

term : term MULT factor
{
  $$=creerNODE(NODE_MULT,0,$1,$3);
}
|    term DIV factor
{
  $$=creerNODE(NODE_DIV,0,$1,$3);
}
| factor
{
  $$=$1;
}

factor:  ENTIER
{
  $$=creerNODE(NODE_ENTIER,$1,NULL,NULL);;
}
| '(' expr ')'
{
  $$=$2;
}


%%
/*--------------------------------------------------------
FONCTIONS MAIN
--------------------------------------------------------*/

int main(){

  yyparse();

  afficherNode(root);
  printf("\n");
  printf("Qui vaut: %d\n",evalNode(root));
  printf("\n");

  return 0;
}
