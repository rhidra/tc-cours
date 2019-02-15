##############################################################
# Some parts of this file are writen by Dr. Kerry McKay as part
# Hosted at OpenSecurityTraining.info under a CC BY-SA license
# http://creativecommons.org/licenses/by-sa/3.0/
# Other parts are writen by Walid Bechkit
##############################################################

import cryptoUtils as cu
import math
import random
import time
import matplotlib.pyplot as plt
from functools import reduce

class privKey:
    p = 0
    q = 0
    d = 0
    N = 0

    def set(self, p, q, d):
        self.p = p
        self.q = q
        self.d = d
        self.N = p*q

    def display(self):
        print ("p: {0}".format(self.p))
        print ("q: {0}".format(self.q))
        print ("d: {0}".format(self.d))

class pubKey:
    e = 0
    N = 0

    def set(self, p, q, e):
        self.e = e
        self.N = p*q

    def display(self):
        print ("N: {0}".format(self.N))
        print ("e: {0}".format(self.e))


def genD(p,q,e):
    N = p*q
    phiN = (p-1)*(q-1)

    d = cu.inverse(e, phiN)
    return d


def encrypt(m, pub):
    return pow(m, pub.e, pub.N)

def decrypt(m, priv):
    return pow(m, priv.d, priv.N)

##################################
def rsa_generate_key(bits):
    p = cu.generatePrime(bits / 2)
    q = cu.generatePrime(bits / 2)
    e = cu.generatePrime(bits)

    while (q == p or cu.pgcd(e, (p - 1) * (q - 1) ) !=1 ):
        q = cu.generatePrime(bits / 2)

    return (p, q, e)

##################################
def f(x,n):
    return (x*x + 1) % n


def pollardRho(N):
    x, y, d = 2, 2, 1
    while d == 1:
        x = f(x, N)
        y = f(f(y, N), N)
        d = cu.pgcd(abs(x - y), N)
    return None if d == N else d


def pollard_pm1(N, B=10):
    a=2
    while pow(B,2)<=N:
        ak=a
        for i in range(2,B+1):
            ak = pow(ak,i,N)
        d = cu.pgcd(ak-1,N)
        if (d!=1 and d!=N):
            return d
        if (d==N):
            a=a+1
        if (d==1 or a>=N**0.5):
            B*=10
            a=2
    return None

##################################
def fermat(N):
    # to be completed Q4.3 #
    return

if __name__ == "__main__":
    print ("===== Q3.2======")
    print(cu.inverse(5, 51504))
    print(cu.inverse(7, 51504))
    print(cu.inverse(239, 51504))

    """
    print ("===== Q3.4======")
    e = 5

    pu = pubKey()
    pu.set(p, q, e)
    pr = privKey()
    pr.set(p, q, genD(p,q,e))


    msg = 27063
    cryp = encrypt(msg, pu)
    decryp = decrypt(cryp, pr)
    print("Message = {}".format(msg))
    print("Clé publique")
    pu.display()
    print("Chiffré = {}".format(cryp))
    print("Clé privée")
    pr.display()
    print("Déchiffré = {}".format(decryp))
    """

    print ("===== Q3.5======")

    sizes = list(range(16, 87, 2))
    times_decrypt = []
    times_crypt = []
    times_fact = []
    for size_key in sizes:
        print("Pour la taille {}".format(size_key))
        values_decrypt = []
        values_crypt = []
        values_fact = []
        for _ in range(2):
            p, q, e = rsa_generate_key(size_key)

            pu = pubKey()
            pu.set(p, q, e)
            pr = privKey()
            pr.set(p, q, genD(p,q,e))

            msg = random.randint(500, 100000)

            t1 = time.time()
            cryp = encrypt(msg, pu)
            t2 = time.time()
            decryp = decrypt(cryp, pr)
            t3 = time.time()
            pollardRho(pu.N)
            t4 = time.time()

            values_crypt.append((t2 - t1)*1000)
            values_decrypt.append((t3 - t2)*1000)
            values_fact.append((t4 - t3)*1000)
        times_decrypt.append(reduce(lambda x, y: x + y, values_decrypt)/len(values_decrypt))
        times_crypt.append(reduce(lambda x, y: x + y, values_crypt)/len(values_crypt))
        times_fact.append(reduce(lambda x, y: x + y, values_fact)/len(values_fact))

    plt.plot(sizes, times_crypt, 'r-', label='Encryption Time')
    plt.plot(sizes, times_decrypt, 'b-', label='Decryption Time')
    plt.plot(sizes, times_fact, 'g-', label='Factorisation Time')
    plt.legend(loc='upper left')
    plt.xlabel('Key Size (bits)')
    plt.ylabel('Time (ms)')
    plt.savefig(str(random.randint(50,20000)))

#Bonus

Test_Values=[12232919657510742227,12358402617957224473, 11985737742464541623,14307699519361765577]

        #to be completed Q4.5
