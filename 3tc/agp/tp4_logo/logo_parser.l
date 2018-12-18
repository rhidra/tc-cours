%{
  #include "logo.h"
  #include "logo_svg.h"
  #include "logo_parser.tab.h"
  #include <stdio.h>
  #include <stdlib.h>

  int yywrap();
  int yyerror();
%}

%%
"FORWARD" {return TK_FORWARD;}
"BACKWARD" {return TK_BACKWARD;}
"LEFT" {return TK_LEFT;}
"RIGHT" {return TK_RIGHT;}
"REPEAT" {return TK_REPEAT;}
"SPLIT" {return TK_SPLIT;}
"SIZE" {return TK_SIZE;}
"STOP" {return TK_STOP;}
"START" {return TK_START;}
"TOGGLE" {return TK_TOGGLE;}
"ORIGIN" {return TK_ORIGIN;}
"LOOK_UP" {return TK_LOOK_UP;}
"LOOK_DOWN" {return TK_LOOK_DOWN;}
"LOOK_LEFT" {return TK_LOOK_LEFT;}
"LOOK_RIGHT" {return TK_LOOK_RIGHT;}
"COLOR" {return TK_COLOR;}
"BACKGROUND_COLOR" {return TK_BG_COLOR;}

"RED" {yylval.i=RED; return ENTIER;}
"GREEN" {yylval.i=GREEN; return ENTIER;}
"BLUE" {yylval.i=BLUE; return ENTIER;}
"CYAN" {yylval.i=CYAN; return ENTIER;}
"YELLOW" {yylval.i=YELLOW; return ENTIER;}
"MAGENTA" {yylval.i=MAGENTA; return ENTIER;}
"BLACK" {yylval.i=BLACK; return ENTIER;}
"WHITE" {yylval.i=WHITE; return ENTIER;}
"GRAY" {yylval.i=GRAY; return ENTIER;}

"RANDOM" {return TK_RAND;}

\+ {return TK_ADD;}
- {return TK_SUB;}
\* {return TK_MULT;}
\/ {return TK_DIV;}

"PROC" {return TK_PROC;}
"EXEC" {return TK_EXEC;}

\[ {return TK_BEGIN;}
\] {return TK_END;}
-?[0-9]* {yylval.i = atoi(yytext); return ENTIER;}
([a-zA-Z])([a-zA-Z0-9_])* {yylval.s = strdup(yytext); return TK_NAME;}

#.*\n // Commentaires
\n

\t
%%

int yywrap() {
  return 1;
}

int yyerror(const char *s) {
  fprintf(stderr, "\x1B[31mErreur de parsing\x1B[0m : %s !\n", s);
  exit(1);
}
