import sys
import random
from math import gcd



def find_e(p):
    while True:
        bit_length = p.bit_length()
        e = random.randint(1, p-1)

        if gcd(e, (p-1)) == 1:
            #print(f"{e} and {p-1} have 1 as a gcd")
            return e


def find_inverse(e,p):
    def egcd(a, b):
        """Extended Euclidean Algorithm to find gcd and coefficients x, y."""
        if b == 0:
            return a, 1, 0
        gcd, x1, y1 = egcd(b, a % b)
        x = y1
        y = x1 - (a // b) * y1
        return gcd, x, y

    def inverse_of_e(a, p):
        """Find the multiplicative inverse of a mod p."""
        gcd, x, _ = egcd(a, p)
        if gcd != 1:
            raise ValueError(f"No multiplicative inverse for {a} mod {p} (not coprime)")
        # Ensure x is positive
        return x % p


    try:
        inverse = inverse_of_e(e, p-1)
        #print(f"The multiplicative inverse of {e} mod {p} is {inverse}")
        
    except ValueError as e:
        print(e)

    return inverse


def sign(p, g, gd, d, x):
    p, g, d, x = int(p), int(g), int(d), int(x)

    e = find_e(p)
    e_inverse = find_inverse(e, p)

    r = pow(g, e, p)
    q = p - 1
    s = (e_inverse * (x - d * r)) % q
          

    """print(f"p = {p}")
    print(f"g = {g}")
    print(f"gd = {gd}")
    print(f"d = {d}")
    print(f"x = {x}")
    print(f"e = {e}")
    print(f"e^-1 = {e_inverse}")"""
    print(f"r = {r}")
    print(f"s = {s}")

if __name__ == "__main__":
    sign(*sys.argv[1:])



    
    
