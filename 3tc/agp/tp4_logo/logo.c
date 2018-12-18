#include <stdlib.h>
#include <stdio.h>
#include "logo.h"

void affiche(PROG prog, PROG proc) {
	if(prog != NULL) {
		switch(prog->type) {
			case REPEAT:
				printf("REPEAT %f [\n", getExprValue(prog->param));
				affiche(prog->prog, proc);
				printf("]\n");
				break;
			case SPLIT:
				printf("SPLIT [\n");
				affiche(prog->prog, proc);
				printf("]\n");
				break;
			case PROC_DEF:
				printf("// Définition de la procédure %f ...\n", getExprValue(prog->param));
				break;
			case PROC_CALL:
				printf("// Appel à la procédure %f ...\n", getExprValue(prog->param));
				affiche(procedure(proc, getExprValue(prog->param)), proc);
				printf("// Fin de l'appel à la procédure %f.\n", getExprValue(prog->param));
				break;
			case LEFT:
				printf("LEFT %f\n", getExprValue(prog->param));
				break;
			case RIGHT:
				printf("RIGHT %f\n", getExprValue(prog->param));
				break;
			case FORWARD:
				printf("FORWARD %f\n", getExprValue(prog->param));
				break;
			case BACKWARD:
				printf("BACKWARD %f\n", getExprValue(prog->param));
				break;
			case SIZE:
				printf("SIZE %f\n", getExprValue(prog->param));
				break;
			case COLOR:
				printf("COLOR %f\n", getExprValue(prog->param));
				break;
			case BG_COLOR:
				printf("BACKGROUND_COLOR %f\n", getExprValue(prog->param));
				break;
			case ORIGIN:
				printf("ORIGIN\n");
				break;
			case LOOK_UP:
				printf("LOOK_UP\n");
				break;
			case LOOK_DOWN:
				printf("LOOK_DOWN\n");
				break;
			case LOOK_LEFT:
				printf("LOOK_LEFT\n");
				break;
			case LOOK_RIGHT:
				printf("LOOK_RIGHT\n");
			case STOP:
				printf("STOP\n");
				break;
			case START:
				printf("START\n");
				break;
			case TOGGLE:
				printf("TOGGLE\n");
				break;
			default:
				fprintf(stderr, "\x1B[31mErreur\x1B[0m : Token non reconnu (%f) !", prog->type);
				break;
		}

		affiche(prog->next, proc);
	}
}

PROG addInstrParam(PROG prog, NODE_TYPE type, EXPR param, PROG prog_repeat) {
	return addInstr(prog, createInstr(type, param, prog_repeat));
}

PROG addInstr(PROG prog, NODE* inst) {
	PROG temp;
	temp = prog;

	if (prog == NULL) {
		prog = inst;
	} else {
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = inst;
	}

	return prog;
}

NODE *createInstr(NODE_TYPE type, EXPR param, PROG prog) {
	NODE *temp = (NODE*) malloc(sizeof(NODE));
	temp->type = type;
	temp->param = param;
	temp->next = NULL;
	temp->prog = prog;

	return temp;
}

void freeProg(PROG prog) {
	if (prog != NULL) {
		if (prog->prog != NULL) {
			freeProg(prog->prog);
		}
		freeProg(prog->next);

		freeExpr(prog->param);
		free(prog);
	}
}

PROG procedure(PROG proc, double id) {
	PROG tmp = proc;

	if (tmp == NULL) {
		fprintf(stderr, "\x1B[31mErreur\x1B[0m : Nom de procédure introuvable !\n");
		exit(1);
	}

	while (tmp->type != PROC_DEF || getExprValue(tmp->param) != id) {
		tmp = tmp->next;
		if (tmp == NULL) {
			fprintf(stderr, "\x1B[31mErreur\x1B[0m : Nom de procédure introuvable !\n");
			exit(1);
		}
	}
	return tmp->prog;
}

int getStringHash(char* s) {
	int sum = 0, i;
	for (i = 0; s[i] != '\0'; i++) {
		sum += s[i];
	}

	return sum;
}
