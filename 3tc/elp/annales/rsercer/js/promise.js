fs = require('fs-extra');
file = './data.json'

fs.ensureFile(file) //On verifie que le fichier existe
.then(() => {
  console.log('success!')
})
.then(() => { //On lit le fichier
  fs.readJson('./data.json', (err, obj) => {
      console.log(obj[0].rsercer);
  });
  //Ici vous affichez le résultat de la lecture
})
