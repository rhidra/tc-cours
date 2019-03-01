const Block = require('./Block');
const Blockchain = require('./Blockchain');

const first = new Block(null, "First !");
const second = new Block(first.id, "Second :)")
const constructif = new Block(second.id, "Vous commencez à voir le principe ?")

const blockchain = new Blockchain();

blockchain.add(first);
blockchain.add(second);
blockchain.add(constructif);

console.log("isValid:", blockchain.isValid());

console.log(blockchain);
