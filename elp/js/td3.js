/** Callbacks **/

/*
Un callback est une fonction appelée à la fin d'une autre fonction
*/

function test(f) {
  setTimeout(function () {
    for (var i = 0; i < 20; i++) {
      console.log("coucou", i);
    }
    f();
  })
}

function main() {
  console.log("Debut");

  test(function(message) {
    console.log("-> Terminé");
    main()
  });

  console.log("Fin")
}
main()

/*
Callstack = pile d'appels de fonction lors de récursivité
Eventstack = pile de fonction à exécuter lors d'un évènement déclenché par l'OS
*/
/* Lecture d'un fichier */
fs = require('fs');

fs.readFile("file.txt", 'utf8', (err, data) => {
  if (err) throw err;

  console.log(data);
});

/* Lecture d'une page web */
request = require('request');
fs = require('fs');
fs.readFile('url.txt', 'utf8', (err, data) => {
  request(data, (err, ))
})

/* Promesses */
Promise = require('bluebird');

wait = function(time) {
  a = new Promise(function(resolve, reject) {
    if (time > 3000) {
      reject('erreur');
    } else {
      setTimeout(() => resolve('coucou'), time);
    }
  });
  return a;
}

wait(2000).then(function(res) {
  console.log('Bonjour', res);
}).then(function(res) {
  console.log('Bonjour', res);
})
.catch(function(res) {
  console.log('Erreur :', res);
})
