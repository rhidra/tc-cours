// Client

const topic = 'heartbeat'
const socket = require('zeromq').socket('sub');

socket.connect('tcp://127.0.0.1:3001');
socket.subscribe(topic);

// On tire un message sur la mq
socket.on('message', function(topic, msg) {
  console.log(`Message ${msg}`);
});
