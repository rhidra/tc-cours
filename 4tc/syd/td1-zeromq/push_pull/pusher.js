// Serveur

const socket = require('zeromq').socket('push');

socket.bindSync('tcp://127.0.0.1:3000');

// On pousse un message toutes les 2sec
var counter = 0;
setInterval(function () {
  const message = `Ping #${counter++}`;
  console.log(message);

  socket.send(message);
}, 300);
