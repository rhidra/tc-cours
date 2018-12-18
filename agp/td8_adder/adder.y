%{ // Définition
  #include <stdio.h>
  #include <stdlib.h>

  int yywrap() {
    return 1;
  }

  int yyerror() {
    perror("Erreur");
    exit(1);
  }

  int sommeFinale = 0;
%}

// Définition des tokens
%token ENTIER PLUS

%% // Règles

somme : somme PLUS ENTIER {
          $$ = $1 + $3;
          sommeFinale = $$;
        } | ENTIER {
          $$ = $1;
        }

%% // Code

int main() {
  yyparse();
  printf("Somme: %d\n", sommeFinale);

  return 0;
}
