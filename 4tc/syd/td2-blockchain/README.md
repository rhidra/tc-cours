# Tutoriel Blockchain : de zéro vers ...

Le but de ce tutoriel est de coder une blockchain depuis zéro pour en comprendre les mécanismes. Cette Blockchain sera très loin d'une Blockchain de production mais permettra d'illustrer les différentes mécaniques la constituant. Les notions et les problématiques seront introduites au furent et à mesure de la progression. Certaines seront *un peu* simplifiées.

Le code sera en Javascript pour permettre au plus grand nombre de réaliser ce tutoriel et parce que c'est le langage de programmation que j'utilise toujours les jours :D. L'environnement utilisé est Node.js (https://nodejs.org/fr/) en version 10 avec npm pour gérer les dépendances. Je pars du principe que vous savez coder dans ce langage et utiliser git.

Pour écrire ce tutoriel, je me suis inspiré de la suite d'article de Kass sur Medium réaliser avec le langage Java : https://medium.com/programmers-blockchain/create-simple-blockchain-java-tutorial-from-scratch-6eeed3cb03fa.

## Work in progress

Ce tutoriel est en cours d'écriture. Je prévois une première version relue et corrigée pour septembre 2018.

## Au commencement fut le block

Dans Blockchain, il y a block. Un block est un ensemble d'informations et quand les blocks sont mis bout à bout, ils forment une chaine : la Blockchain !

Commençons avec un block assez simple :

* un identifiant : permet d'identifier le block. Il sera généré aléatoirement.
* un parent : l'identifiant du block qui précède dans la chaine. Cela nous permettra de remonter la chaine jusqu'à sont origine.
* des données : pour le moment, une simple chaine de caractère.
* la date de création du block.

J'ai écris un fichier `index.js` qui ressemble à ça :

```Javascript
const Block = require("./Block");

const first = new Block(null, "First !");
const second = new Block(first.id, "Second :)");
const constructif = new Block(second.id, "Vous commencez à voir le principe ?");

console.log([first, second, constructif]);
```

J'ai aussi commencé à écrire un fichier `Block.js` mais je vais laisser le compléter !

Quand c'est fini, dans un terminal placé dans ce dossier : `npm start`. Vous devriez voir quelque chose comme cela :

```Javascript
[ Block {
    id: 466991139,
    previous: null,
    data: 'First !',
    date: 2018-05-05T14:49:29.152Z },
  Block {
    id: 349521768,
    previous: 466991139,
    data: 'Second :)',
    date: 2018-05-05T14:49:29.152Z },
  Block {
    id: 847041514,
    previous: 349521768,
    data: 'Vous commencez à voir le principe ?',
    date: 2018-05-05T14:49:29.152Z } ]
```

C'est bon ? Magnifique ! Vous avez une première blockchain ! Bon, par contre, elle est sacrément pas fonctionnelle... Normalement, quand un block est ajouté dans la Blockchain, il n'est plus modifiable. Ici, rien ne vous empêche de modifier ce que vous voulez.

## Prenons un peu de hash

Nous voulons vérifier que les blocks n'ont pas été modifié. Pour vérifier que quelque-chose n'a pas été modifié, il est courant en informatique d'utiliser des fonctions de hachage.

Une fonction de hachage est une fonction qui prendre en entrée un ensemble quelconque de données et retourne une empreinte, aussi appelée hash, permettant d'identifier l'entrée. Cette empreinte est de taille fixe quelque-soit l'entrée. Une fonction couramment utilisé est SHA. Voici quelques exemples d'empreinte :

```Bash
> echo "Blockchain" | shasum
# efcf8baf5959ad1ebc7f4950425ef1c2eae9cbd9  -

> echo "Block" | shasum
# d1a6b1157e37bdaad78bec4c3240f0d6c576ad21  -

> echo "Vous commencez à voir le principe ?" | shasum
# 25abec7ced7642b886c1bffbc710cc3439f23ab7  -
```

Une autre propriété intéressante est qu'une petite modification dans l'entrée change totalement l'empreinte :

```Bash
> echo "Blockchain" | shasum
# efcf8baf5959ad1ebc7f4950425ef1c2eae9cbd9  -

> echo "blockchain" | shasum
# ea5f179324c233b002fa8ac4201fa216001515e5  -
```

Si je vous parle de tout ça, c'est qu'on va l'utiliser mais comment cela résout notre problème ?

Une idée ?

Cool !

On va calculer l'empreinte du block avec cette fonction et on va utiliser cette empreinte comme identifiant du block ! Si on modifie le block, son empreinte change donc son id change ! Mais cette id est utilisé dans le block suivant, ce qui modifie son empreinte. Et ainsi de suite jusqu'au dernier block de la chaine.

La fonction suivante prend en entrée une chaine de caractère et retour l'empreinte correspondante.

```Javascript
const crypto = require('crypto');

function getHash(data) {
  return crypto.createHash('sha256').update(data, 'utf8').digest('hex');
}
```

Modifier la class Block pour lui ajouter une fonction getHash qui calcule l'empreinte correspondant au block. Pour calculer cette empreinte, vous devez utiliser l'identifiant du block précédent, la date du block et les données contenu dans le block.

Vous obtenez quelques chose comme ça :

```Javascript
[ Block {
    previous: null,
    date: 2018-05-05T16:32:31.508Z,
    data: 'First !',
    id: '834cde4fafb33b0a4a64470eabef589d3977a38ddaebe8fcdcbe9d9db33a2d8b' },
  Block {
    previous: '834cde4fafb33b0a4a64470eabef589d3977a38ddaebe8fcdcbe9d9db33a2d8b',
    date: 2018-05-05T16:32:31.510Z,
    data: 'Second :)',
    id: '9832f23c49b0f2c4304e667d942b75767d5e8341ee29cb0da37a32a09627d396' },
  Block {
    previous: '9832f23c49b0f2c4304e667d942b75767d5e8341ee29cb0da37a32a09627d396',
    date: 2018-05-05T16:32:31.510Z,
    data: 'Vous commencez à voir le principe ?',
    id: 'b9f3db05d7f7c85a254c246b587dad497fe75c65ba51464061c189c7e06deada' } ]
```

Maintenant, essayez de modifier le premier élément de la chaine, tous les autres sont modifiés !

## Suite

Vous avez survécu ? Cool ! Passons à l'étape suivante : `git checkout etape-2`.
