// Client

const socket = require('zeromq').socket('pull');

socket.connect('tcp://localhost:3000');

// On tire un message sur la mq
socket.on('message', function(msg) {
  console.log(`Message ${msg}`);
});
