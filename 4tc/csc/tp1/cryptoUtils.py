##############################################################
# Some parts of this file are writen by Dr. Kerry McKay as part
# of the "Understanding Cryptology: Cryptanalysis" course
# Hosted at OpenSecurityTraining.info under a CC BY-SA license
# http://creativecommons.org/licenses/by-sa/3.0/
# Other parts are writen by Walid Bechkit
##############################################################

import random
import sys

#########################
# find the pgcd and the bézout
# coefficients
#########################

def extendedEuclidean(n, b):
    x0, x1, y0, y1 = 0, 1, 1, 0
    while n != 0:
        q, b, n = b // n, n, b % n
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return  x0, y0, b


#########################
# find multiplicative inverse
# of m mod n
#########################
def inverse(m,n):
    [x0,y0,d] = extendedEuclidean(m, n)
    if d != 1 :
            return None
    else:
            return x0 % n

#########################
# compute greatest common divisor
# of m and n
#########################
def pgcd(m,n):
    return extendedEuclidean(m, n)[2]

#########################
# compute a^b mod n
# using square anf multiply
#########################
def modExp(a,b,n):
    if b<0 or a<0 or n<0:
        print ("modExp error: all arguments must be positive")
        return None

    r = 1
    while b > 0:
        if b%2:
            r *= a
            r = r %n
        a *= a
        b = b//2
    return r

#########################
# test if n is prime using the
# Rabin-Miller probabilistic
#########################

def is_probable_prime(n, k =10):
   if n < 6:  # assuming n >= 0 in all cases... shortcut small cases here
      return [False, False, True, True, False, True][n]
   elif n & 1 == 0:  # should be faster than n % 2
      return False
   else:
      s, d = 0, n - 1
      while d & 1 == 0:
         s, d = s + 1, d >> 1
      # Use random.randint(2, n-2) for very large numbers
      for a in random.sample(range(2, min(n - 2, sys.maxsize)), min(n - 4, k)):
         x = pow(a, d, n)
         if x != 1 and x + 1 != n:
            for r in range(1, s):
               x = pow(x, 2, n)
               if x == 1:
                  return False  # composite for sure
               elif x == n - 1:
                  a = 0  # so we know loop didn't continue to end
                  break  # could be strong liar, try another a
            if a:
               return False  # composite if we reached end of this loop
      return True  # probably prime if reached end of outer loop


#########################
# generate a random prime
# number of size bits
#########################
def generatePrime(bits):
    # Return a random prime number of keysize bits in size.
    while True:
        num = random.randrange(2**(bits-1), 2**(bits))
        if is_probable_prime(num):
            return num
