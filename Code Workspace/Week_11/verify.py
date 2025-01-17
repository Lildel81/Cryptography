import sys

def verify(p, g, gd, x, r, s):
    p, g, gd, x, r, s = int(p), int(g), int(gd), int(x), int(r), int(s)
    
    
    right = pow(g, x, p)
    
    # Compute gd^r * r^s mod p
    left = (pow(gd, r) * pow(r, s)) % p

    print(f"left = {left} and right = {right}")
    
    # Output 1 if valid, otherwise 0
    print(1 if left == right else 0)

if __name__ == "__main__":
    verify(*sys.argv[1:])
