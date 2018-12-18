/* Javascript */
/*
github /sfreno
       /javascript

V8 = Machine virtuelle qui fait tourner javascript
=> Interpréteur de commande Js

NodeJs/Navigateur = OS qui fait tourner V8
=> Gère les entrées/sorties, etc ...

C'est un langage fonctionnel : tout algo peut être conçu de manière fonctionnelle (récursive) ou de manière impérative (avec des for/while).
Langage impératif = proche de la machine => voient la mémoire, efficace mais avec des "problèmes" mathématiques
Langage fonctionnel = mathématique => Comportement prévisible, objet de base = fonction
Js = empilement de fonctions

// Types :
- numérique
- booléen
- string
- fonction
- regex : d = /a/
- undefined : let x

// Structures de contrôle
for
while
do while
sont à bannir car c'est un langage de prog fonctionnel

// Fonctions
Méthode classique impérative
function somme(a, b) {
  return a+b;
}

Méthode fonctionnelle
let a = function (x) {
  console.log("=>", x);
}
let a = (x) => {
  console.log("=>", x)
}

// Transtypage
null == undefined
=> Cherche un ancêtre commun dans l'héritage et les compare
Pour éviter le transtypage => ===

Linter = Permet de signaler au programmeur les situations désagréables
Ou utiliser un langage de plus au niveau (Typescript ou Coffeescript)


// Exercice prog fonctionnelle
//Q1
let multiplie = (a, b) => {
  return a*b;
}

//Q2
let multiplieur = (a) => {
  return function (b) {return a*b;};
}

// Closure
function create() {
  let response = 23;
  return function (x) { return x + response; }
}
La variable existe alors en dehors de la fonction => Une closure est créée

// Objet
Un objet est un dictionnaire (comme en Python)
let chose = {"hello":"coucou", 3:10}
Equivalence clé:valeur
la valeur peut être une fonction.
Donc cela correspond bien à un objet classique.

// Tableau
a = [1,2,3]
a.reduce(r)
r est une fonction r(cumul, valeur) qui parcours le tableau et exécute la fonction
a.forEach((val, index) => {console.log(val);})

//Q5.1 Calcul moyenne
reducer = (acc, current) => acc + current/array.length
array.reduce(reducer)

//Q5.2 To Upper Case
map1 = x => x.toUpperCase();
array = array.map(x => x.toUpperCase())

//Q5.3 Retrait de 2 pts + moyenne
array = array.map(x => x-2).reduce( (val, cumul) => {return(val+cumul)/array.length;})

// Variables automatiques
arguments.length // Donne le nombre paramètres donnés à la fonction réellement

// NPM (Node Packet Manager)
npm install lodash
_ = require('lodash') // Chargement du module lodash dans la variable _
_.sortBy([1,4,3]) // Appel à la fonction sortBy() du module lodash
