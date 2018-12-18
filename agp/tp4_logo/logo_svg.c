#include "logo_svg.h"

PEN createPen() {
  PEN pen = (PEN) malloc(sizeof(STYLO));
  pen->x = 0;
  pen->y = 0;
  pen->angle = 0;
  RGB_COLOR c = {0,0,0};
  pen->color = c;
  pen->strokeWidth = 2;
  pen->bTracing = 1;
  return pen;
}

void makeSVG(PROG prog) {
  IMAGE_INFO *info = getImageInfo(prog);
  printf("\n<svg width=\"%d\" height=\"%d\">\n", (int)info->width, (int)info->height);
  printf("<rect width=\"100%%\" height=\"100%%\" fill=\"rgb(%d,%d,%d)\"/>\n",
    info->background.r, info->background.v, info->background.b);
  PEN pen = createPen();
  pen->x = info->originx;
  pen->y = info->originy;
  svg(prog, prog, pen, info);
  free(pen);
  printf("</svg>\n");
}

void getImageInfo_recursive(PROG prog, PROG proc, PEN pen, IMAGE_INFO *info) {
  int i;
  STYLO oldPen;

  if (prog != NULL) {
    switch (prog->type) {
      case FORWARD:
        moveForward(pen, getExprValue(prog->param));
        break;
      case BACKWARD:
        moveForward(pen, -getExprValue(prog->param));
        break;
      case LEFT:
        rotate(pen, -getExprValue(prog->param));
        break;
      case RIGHT:
        rotate(pen, getExprValue(prog->param));
        break;
      case ORIGIN:
        pen->x = 0;
        pen->y = 0;
        break;
      case LOOK_UP:
        pen->angle = -90;
        break;
      case LOOK_DOWN:
        pen->angle = 90;
        break;
      case LOOK_LEFT:
        pen->angle = 0;
        break;
      case LOOK_RIGHT:
        pen->angle = 180;
        break;
      case REPEAT:
        for (i = 0; i < getExprValue(prog->param); i++) {
          getImageInfo_recursive(prog->prog, proc, pen, info);
        }
        break;
      case SPLIT:
        oldPen = *pen;
        getImageInfo_recursive(prog->prog, proc, pen, info);
        pen = &oldPen;
        break;
      case PROC_DEF:
        break;
      case PROC_CALL:
        getImageInfo_recursive(procedure(proc, getExprValue(prog->param)), proc, pen, info);
        break;
      case BG_COLOR:
        info->background = getColor(getExprValue(prog->param));
        break;
      default:
        break;
    }
    if (pen->x > info->maxx) info->maxx = pen->x;
    if (pen->x < info->minx) info->minx = pen->x;
    if (pen->y > info->maxy) info->maxy = pen->y;
    if (pen->y < info->miny) info->miny = pen->y;

    getImageInfo_recursive(prog->next, proc, pen, info);
  }
}

IMAGE_INFO *getImageInfo(PROG prog) {
  PEN pen = createPen();
  pen->bTracing = 0;
  IMAGE_INFO *info = (IMAGE_INFO*) malloc(sizeof(IMAGE_INFO));
  info->minx = 0;
  info->maxx = 0;
  info->miny = 0;
  info->maxy = 0;
  RGB_COLOR c = {255, 255, 255};
  info->background = c;
  getImageInfo_recursive(prog, prog, pen, info);
  info->originx = -info->minx + MARGE;
  info->originy = -info->miny + MARGE;
  info->width = info->maxx - info->minx + 2*MARGE;
  info->height = info->maxy - info->miny + 2*MARGE;

  return info;
}

void svg(PROG prog, PROG proc, PEN pen, IMAGE_INFO *info) {
  int i = 0;
  STYLO oldPen;

  if (prog != NULL) {
    switch (prog->type) {
      case FORWARD:
        moveForward(pen, getExprValue(prog->param));
        break;
      case BACKWARD:
        moveForward(pen, -getExprValue(prog->param));
        break;
      case LEFT:
        rotate(pen, -getExprValue(prog->param));
        break;
      case RIGHT:
        rotate(pen, getExprValue(prog->param));
        break;
      case REPEAT:
        for (i = 0; i < getExprValue(prog->param); i++) {
          svg(prog->prog, proc, pen, info);
        }
        break;
      case COLOR:
        pen->color = getColor(getExprValue(prog->param));
        break;
      case SIZE:
        pen->strokeWidth = getExprValue(prog->param);
        break;
      case SPLIT:
        oldPen = *pen;
        svg(prog->prog, proc, pen, info);
        pen = &oldPen;
        break;
      case START:
        pen->bTracing = 1;
        break;
      case STOP:
        pen->bTracing = 0;
        break;
      case TOGGLE:
        pen->bTracing = !pen->bTracing;
        break;
      case ORIGIN:
        pen->x = info->originx;
        pen->y = info->originy;
        break;
      case LOOK_UP:
        pen->angle = -90;
        break;
      case LOOK_DOWN:
        pen->angle = 90;
        break;
      case LOOK_LEFT:
        pen->angle = 0;
        break;
      case LOOK_RIGHT:
        pen->angle = 180;
        break;
      case PROC_DEF:
        break;
      case PROC_CALL:
        svg(procedure(proc, getExprValue(prog->param)), proc, pen, info);
        break;
      case BG_COLOR:
        break;
      default:
        fprintf(stderr, "\x1B[31mErreur\x1B[0m : Instruction à transcrire dans le SVG non reconnue (type=%f) !\n", prog->type);
        break;
    }
    svg(prog->next, proc, pen, info);
  }
}

void moveForward(PEN pen, double val) {
  double oldx = pen->x;
  double oldy = pen->y;

  pen->x += val * cos(pen->angle * DEG_TO_RAD);
  pen->y += val * sin(pen->angle * DEG_TO_RAD);

  if (pen->bTracing)
    printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(%d,%d,%d);stroke-width:%d\"/>\n",
          (int)oldx, (int)oldy, (int)pen->x, (int)pen->y, pen->color.r, pen->color.v, pen->color.b, pen->strokeWidth);
}

void rotate(PEN pen, double val) {
  pen->angle += val;
}

RGB_COLOR getColor(int c) {
  RGB_COLOR col;
  col.b = (c>>16)&0xFF;
  col.v = (c>>8)&0xFF;
  col.r = (c>>0)&0xFF;
  return col;
}
