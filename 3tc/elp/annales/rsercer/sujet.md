# Examen machine ELP, mai 2017

Les durées et le barème sont donnés à titre indicatif.

# java (20min, 5pts)
Dans le répertoire java, vous devez écrire un listener et modifier le fichier `Counter.java` pour:
1. calculer et afficher à la fermeture de la fenêtre le rapport entre le nombre de clic sur le bouton "rse" et le nombre total de clic,
2. mémoriser l'historique des clics en écrivant dans un fichier le login correspondant au bouton cliqué.

# javascript (20min, 5pts)
Installez node sur votre machine dans /tmp.
``` bash
wget https://nodejs.org/dist/v6.10.0/node-v6.10.0-linux-x64.tar.gz
tar zxvf node-v6.10.0-linux-x64.tar.gz
```
Allez dans le répertoire js et corrigez les codes suivants.
Les codes d'exemples peuvent tous être directement lancés dans l'interpréteur node.
Il faut les modifier pour répondre aux questions.

1) Callbacks
Dans le fichier mesCallbacks.js, commentez les lignes afin d'afficher les fonctions de type callbacks de celles qui ne le sont pas.

2) Fonctionnel
Dans le fichier fonctionnel.js, modifiez le code initial. Ajoutez 2 autres fonctions  qui traitent le tableau en utilisant forEach pour la première fonction et lodash pour la seconde. Pour que lodash fonctionne, pensez à installer le module lodash dans votre interpréteur node.
`npm install lodash`

3) Promesses
installez le module de promesse `fs-extra` dans votre projet
`npm install fs-extra`
31) lancez le script  `promise.js` et corrigez l'erreur du fichier de données.
32) Complétez l'appel à la promesse readJson pour afficher le contenu du fichier de données.

# python (20min, 5pts)
Vous allez écrire vos programmes dans le répertoire python.

1. La méthode "built-in" `max` retourne le plus grand élément d'une séquence. Écrivez une fonction `find_max_len` qui accepte un nombre arbitraire de séquences en paramètre et qui retourne la longueur de la séquence la plus longue. Pour illustrer :

```python
>>> a = ["rsercer", "recresr"]
>>> b = [None, 666, (True, False)]
>>> c = ["jäger", "chartreuse", "armagnac", "carlsberg"]
>>> find_max_len(a, b, c)
4
>>> find_max_len()
0
```

2. Que fait la classe "built-in" `enumerate` ? Illustrez sur les listes définies ci-dessus.

3. Définissez un générateur, `Enumerate`, reproduisant la fonctionnalité de `enumerate`. Illustrez son utilisation.

# clojure (10min, 2.5pts)
Récupérez la dernière version stable de Clojure depuis http://clojure.org. Vous allez écrire votre programme dans le répertoire clojure.

En utilisant les fonctions écrites dans le fichier `helpers.clj`, écrivez une fonction qui prend en entrée 3 listes de mots et retourne une chaine formée par les mots qui contiennent les caractères 'D' ou 'H'. Chaque mot devra être entouré des caractères '['']' et séparé des autres par ','.

# go (10min, 2.5pts)
Dans le répertoire `go`, modifiez le code du fichier `generator.go` en complétant la fonction `nombresImpairs`
qui va renvoyer les nombres de la suite demandée à un interval de 300 milliseconds.
Pour la génération de ces nombres vous pouvez vous inspirer du code du fichier `example.go`.
