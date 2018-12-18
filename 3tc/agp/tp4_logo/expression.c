#include "expression.h"

double getExprValue(EXPR expr) {
  double fg, fd, result;

  switch (expr->type) {
    case EXPR_ENTIER:
      return expr->param;
      break;
    case RANDOM:
      return rand()%((int)expr->param-MIN_RAND)+MIN_RAND;
      break;
    default:
      break;
  }

  fg = getExprValue(expr->nextl);
  fd = getExprValue(expr->nextr);

  switch (expr->type) {
    case ADD:
      result = fg + fd;
      break;
    case MULT:
      result = fg * fd;
      break;
    case SUB:
      result = fg - fd;
      break;
    case DIV:
      result = fg / fd;
      break;
    default:
      fprintf(stderr, "\x1B[31mErreur\x1B[0m : Symbole d'opération inconnu (expr_type=%d) !\n", expr->type);
      break;
  }

  return result;
}

EXPR createExpr(EXPR_TYPE type, double param) {
  EXPR temp = (EXPR) malloc(sizeof(expr));
  temp->type = type;
  temp->param = param;
  temp->nextl = NULL;
  temp->nextr = NULL;

  return temp;
}

EXPR addExpr(EXPR parent, EXPR nextl, EXPR nextr) {
  parent->nextl = nextl;
  parent->nextr = nextr;

  return parent;
}

void freeExpr(EXPR expr) {
  if (expr != NULL) {
    freeExpr(expr->nextl);
    freeExpr(expr->nextr);

    free(expr);
  }
}
