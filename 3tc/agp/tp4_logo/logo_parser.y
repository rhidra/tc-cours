%{ // Définitions
  #include "logo.h"
  #include "expression.h"
  #include <stdio.h>
  #include <stdlib.h>

  #define YYERROR_VERBOSE

  PROG p1 = NULL; // Stocke le programme principal

  PROG getProg() {
    if (p1 == NULL) {
      printf("Erreur : Le fichier TC-LOGO ne doit pas finir par une procédure !");
      exit(1);
    }
    return p1;
  }
%}

// Définition des tokens
%token TK_FORWARD TK_LEFT TK_RIGHT TK_REPEAT ENTIER TK_BEGIN TK_END
%token TK_SIZE TK_SPLIT TK_START TK_STOP TK_COLOR TK_TOGGLE TK_BACKWARD TK_ORIGIN
%token TK_NAME TK_PROC TK_EXEC TK_BG_COLOR TK_RAND
%token TK_LOOK_UP TK_LOOK_DOWN TK_LOOK_LEFT TK_LOOK_RIGHT
%token TK_ADD TK_SUB TK_MULT TK_DIV

%union {
  char *s;
  int i;
  PROG inst;
  EXPR expr;
}
%type <inst> programme instruction
%type <expr> expression
%type <i> ENTIER
%type <s> TK_NAME

%% // Règles

programme : programme instruction {
  $$ = addInstr($1, $2);
  p1 = $$;
} | instruction {
  $$ = $1;
  p1 = $$;
}

instruction : TK_FORWARD expression {
  $$ = createInstr(FORWARD, $2, NULL);
} | TK_BACKWARD expression {
  $$ = createInstr(BACKWARD, $2, NULL);
} | TK_LEFT expression {
  $$ = createInstr(LEFT, $2, NULL);
} | TK_RIGHT expression {
  $$ = createInstr(RIGHT, $2, NULL);
} | TK_SIZE expression {
  $$ = createInstr(SIZE, $2, NULL);
} | TK_COLOR expression {
  $$ = createInstr(COLOR, $2, NULL);
} | TK_BG_COLOR expression {
  $$ = createInstr(BG_COLOR, $2, NULL);
} | TK_REPEAT expression TK_BEGIN programme TK_END {
  $$ = createInstr(REPEAT, $2, $4);
} | TK_SPLIT TK_BEGIN programme TK_END {
  $$ = createInstr(SPLIT, createExpr(EXPR_ENTIER, 0), $3);
} | TK_START {
  $$ = createInstr(START, createExpr(EXPR_ENTIER, 0), NULL);
} | TK_STOP {
  $$ = createInstr(STOP, createExpr(EXPR_ENTIER, 0), NULL);
} | TK_TOGGLE {
  $$ = createInstr(TOGGLE, createExpr(EXPR_ENTIER, 0), NULL);
} | TK_ORIGIN {
  $$ = createInstr(ORIGIN, createExpr(EXPR_ENTIER, 0), NULL);
} | TK_LOOK_UP {
  $$ = createInstr(LOOK_UP, createExpr(EXPR_ENTIER, 0), NULL);
} | TK_LOOK_DOWN {
  $$ = createInstr(LOOK_DOWN, createExpr(EXPR_ENTIER, 0), NULL);
} | TK_LOOK_LEFT {
  $$ = createInstr(LOOK_LEFT, createExpr(EXPR_ENTIER, 0), NULL);
} | TK_LOOK_RIGHT {
  $$ = createInstr(LOOK_RIGHT, createExpr(EXPR_ENTIER, 0), NULL);
} | TK_PROC TK_NAME TK_BEGIN programme TK_END {
  p1 = NULL;
  $$ = createInstr(PROC_DEF, createExpr(EXPR_ENTIER, getStringHash($2)), $4);
} | TK_NAME {
  $$ = createInstr(PROC_CALL, createExpr(EXPR_ENTIER, getStringHash($1)), NULL);
}

expression : expression TK_ADD expression {
  $$ = addExpr(createExpr(ADD, 0), $1, $3);
} | expression TK_SUB expression {
  $$ = addExpr(createExpr(SUB, 0), $1, $3);
} | expression TK_MULT expression {
  $$ = addExpr(createExpr(MULT, 0), $1, $3);
} | expression TK_DIV expression {
  $$ = addExpr(createExpr(DIV, 0), $1, $3);
} | TK_RAND {
  $$ = createExpr(RANDOM, MAX_RAND);
} | TK_RAND TK_BEGIN ENTIER TK_END {
  $$ = createExpr(RANDOM, $3);
} | ENTIER {
  $$ = createExpr(EXPR_ENTIER, $1);
}

%%
