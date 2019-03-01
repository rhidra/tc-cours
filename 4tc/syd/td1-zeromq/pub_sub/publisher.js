const socket = require(`zeromq`).socket(`pub`);

socket.bind(`tcp://127.0.0.1:3001`);

const topic = `heartbeat`;

setInterval(function () {
	const timestamp = Date.now().toString();
  console.log(timestamp);
	socket.send([topic, timestamp]);
}, 500);
