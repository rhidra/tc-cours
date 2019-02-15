let zmq = require('zeromq');
let socket = zmq.socket('rep');

socket.on('message', function(request) {
  console.log(request.toString());
  socket.send(request);
})

socket.bindSync('tcp://*:6666');
socket.bindSync('tcp://*:6667');
socket.bindSync('tcp://*:6668');
