const crypto = require('crypto');

const NOMBRE_ZERO = 1;

function getHash(data) {
  return crypto.createHash('sha256').update(data, 'utf8').digest('hex');
}

module.exports = class Block {
    constructor(previous, data) {
        this.data = data;
        this.previous = previous;
        this.date = new Date();
        this.nonce = 1;
        this.id = this.miner();
    }

    isValid(previous) {
        //console.log("Vérification de validité entre ".concat(this.id, ' et ', previous))
        return this.id === this.generateId()
            && previous === this.previous
            && parseInt(this.id.substring(0, NOMBRE_ZERO)) === 0;
    }

    generateId() {
        return getHash(this.data.concat(this.previous, this.nonce, this.date));
    }

    miner() {
        do {
            this.id = this.generateId();
            this.nonce++;
            console.log('Test '.concat(this.nonce, ' : ', this.id));
        } while(parseInt(this.id.substring(0, NOMBRE_ZERO)) !== 0);
    }
}
