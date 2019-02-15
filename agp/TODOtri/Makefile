#########################################################
# Makefile pour le programme du TD2 AGP
# Tristan Roussillon, 2013
#########################################################

# Variables pour le compilateur et l'editeur de lien 
CC            =gcc 
CFLAGS        += -Wall -g

#ensemble des executables
EXE=test demo benchmark
#ensemble de fhichers objets
OBJ=ioHelpers.o permutation.o triBulle.o triFusion.o triRapide.o

#cible principale 
all: $(OBJ) $(EXE)

#regle generique pour fabriquer les exécutables
%: %.c $(OBJ) 
	$(CC) $(CFLAGS) $< $(OBJ) -o $@

#regle generique pour fabriquer les fichiers objets
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

#regle pour generer la documentation du projet
doc:	doxyfile
	doxygen doxyfile

#regle pour nettoyer le projet
clean:
	rm -rf *~ *.out *.o html *.svg
	rm -f $(EXE)

#regle pour l'enseignant afin d'exporter le projet
#sans la correction
PRE = TODO #prefix
VIDE = 
FILESTOREMOVE = $(wildcard TODO*)
FILESTOUPDATE = $(subst TODO,, $(FILESTOREMOVE))
export: clean
	mkdir ../TODOtri
	cp ./* ../TODOtri
	cd ../TODOtri; for i in $(FILESTOREMOVE); do rm $$i; done	
	cd ../TODOtri; for i in $(FILESTOUPDATE); \
	do sed -i "s/\#include.*TODO.*c./\/\/TODO/" $$i; done
	cd ..; tar cvf TODOtri.tar TODOtri
	rm -R ../TODOtri

