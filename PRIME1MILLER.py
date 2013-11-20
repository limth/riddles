#Prime Generator max = 1000000000 - TLE
from random import randint

psyco.full()

def _bits_of_n(n):
    bits = []

    while n:
        bits.append(n % 2)
        n /= 2

    return bits

def _MR_composite_witness(a, n):
    rem = 1

    for b in reversed(_bits_of_n(n - 1)):
        x = rem
        rem = (rem * rem) % n

        if rem == 1 and x != 1 and x != n - 1:
            return True

        if b == 1:
            rem = (rem * a) % n

    if rem != 1:
        return True

    return False

def isprime_MR(n, trials=1):
    if n < 2:
        return False

    for ntrial in xrange(trials):
        if _MR_composite_witness(randint(1, n - 1), n):
            return False

    return True

def main():
    testsNum = int(raw_input())

    while testsNum:
        testsNum -= 1
        start, end = [long(x) for x in raw_input().split()]
        
        for n in xrange(start, end):
            if isprime_MR(n): 
                print n

        if testsNum: 
            print '\n'

if __name__ == '__main__':
    main()
