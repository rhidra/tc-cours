# Makefile
# Définit les cibles utiles pour la compilation complète du programme.
# Certaines cibles ne sont présentes qu'à des fins de test.

FLAGS = -g -Wall -DDEBUG

all: tc-logo

# Structure de données

logo.o: logo.c logo.h
	gcc ${FLAGS} -c $< -o $@

expression.o: expression.c expression.h
	gcc ${FLAGS} -c $< -o $@

main.o:	main.c logo.h
	gcc ${FLAGS} -c $< -o $@

# Parseur

logo_parser.tab.c: logo_parser.y logo.h
	# bison -t -d $< # Option de débuggage
	bison -d $<

logo_parser.tab.o: logo_parser.tab.c
	gcc ${FLAGS} -c $< -o $@

logo_parser2.tab.o: logo_parser2.tab.c
	gcc ${FLAGS} -c $< -o $@

lex.yy.c: logo_parser.l logo.h
	# flex -d $< # Option de débuggage
	flex $<

lex.yy.o: lex.yy.c
	gcc ${FLAGS} -c $< -o $@

# SVG

logo_svg.o: logo_svg.c logo_svg.h
	gcc ${FLAGS} -c $< -o $@

# Cibles principales

test: logo_parser.tab.o lex.yy.o main.o logo_svg.o logo.o expression.o
	gcc ${FLAGS} $^ -o $@ -lm

exec: test # Cible de test combinant compilation et exécution, non fonctionnelle
	./test < example.logo > tmp.svg
	# display tmp.svg
	feh --magick-timeout 10 tmp.svg
	rm tmp.svg
	make clear

tc-logo: logo_parser.tab.o lex.yy.o main.o logo_svg.o logo.o expression.o
	gcc ${FLAGS} $^ -o $@ -lm
	make clean

# Nettoie le répertoire en supprimant les fichiers créés par
# bison, flex, ainsi que les fichiers objets du compilateur C
clean:
	rm -rf *.o *~
	rm -rf *.tab.* lex.yy.* test

# Supprime tous les fichiers sauf le code source
clear: clean
	rm -rf tc-logo
