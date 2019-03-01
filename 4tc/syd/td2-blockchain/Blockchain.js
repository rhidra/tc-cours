const crypto = require('crypto');
const Block = require('./Block');

module.exports = class Blockchain {
    constructor() {
        this.chain = [];
    }

    add(block) {
        this.chain.push(block);
    }

    last() {
        if (this.chain.length > 0) {
            return this.chain[this.chain.length - 1];
        } else {
            throw new Error("La blockchain est vide");
        }
    }

    isValid() {
        let b = true, previous = null;
        
        this.chain.forEach(function(block, index, array) {
            if (!block.isValid(previous))
                b = false;
            previous = block.id;
        });
        return b;
    }
}
