%{
  #include <stdlib.h>
  #include <stdio.h>
  #include "adder.tab.h"
%}

%%
(-?[1-9][0-9]*)|0   yylval = atoi(yytext); return ENTIER;
\+                return PLUS;
%%
